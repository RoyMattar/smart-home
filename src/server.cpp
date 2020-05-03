#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <utility> // std::pair

#include <cstddef> // size_t
#include <cassert>
#include <sys/sysinfo.h> // get_nprocs()

#include "server.hpp"
#include "common_utils.hpp"
#include "group_tag.hpp"
#include "event.hpp"
#include "event_bus.hpp"
#include "consumer_map_tagged.hpp"
#include "event_distributor.hpp"
#include "event_delivery_factory.hpp"
#include "tagged_distribution_channel.hpp"

struct ConfigFileErrorExc : public std::exception
{
    const char* what () const NOEXCEPTIONS
    {
        return "Error opening config file";
    }
};

namespace smart_home
{

struct Server::ConfigFileLines
{
    std::string m_id;
    std::string m_type;
    std::string m_room;
    std::string m_floor;
    std::string m_log;
    std::string m_config;
};

Server::Server (std::string const& a_configFile, unsigned char a_parallelFactor,
                                  size_t a_publicationBandwidth, size_t a_distributionBandwidth)
    : m_configFile(a_configFile)
    , m_soHandlers()
    , m_numOfTags(numOfTags(a_parallelFactor))
    , m_eventBus(new EventBus(a_publicationBandwidth))
    , m_consumerMapTagged(new ConsumerMapTagged<>(m_numOfTags))
    , m_distributor(new EventDistributor())
    , m_deliveryFactory()
    , m_taggedChannels()
    , m_middlewarePair(std::make_pair(new EventMiddleware(m_eventBus, m_consumerMapTagged, m_distributor),
                                      SharedPtr<advcpp::Thread>()))
    , m_agents()
{
    for (GroupTag tag = 0; tag < m_numOfTags; ++tag)
    {
        SharedPtr<TaggedDistributionChannel> chan(new TaggedDistributionChannel(a_distributionBandwidth, tag));
        m_taggedChannels.push_back(chan);
        m_distributor->AddChannel(m_taggedChannels[tag], m_taggedChannels[tag]);
    }
}

void Server::Start ()
{
    std::ifstream fs(m_configFile.c_str());
    if (!fs.is_open())
    {
        throw ConfigFileErrorExc();
    }

    startFactory();
    startMiddleware();

    while (!fs.eof())
    {
        ConfigFileLines lines = parseLines(fs);
        
        std::pair<SharedPtr<advcpp::SOLibHandler>, bool> pairMakeHandler
            = tryMakeSOHandler("lib" + lines.m_type + ".so");
        if (!pairMakeHandler.second)
        {
            continue;
        }
        m_soHandlers.push_back(pairMakeHandler.first);

        std::pair<Server::AgentMaker, bool> pairMakeAgentMaker
            = tryMakeAgentMaker(pairMakeHandler.first);
        if (!pairMakeAgentMaker.second)
        {
            continue;
        }
        
        SharedPtr<IAgent> agent(pairMakeAgentMaker.first(
                                    lines.m_id, AgentInfo::DeviceLocation(lines.m_floor, lines.m_room),
                                    lines.m_log, lines.m_config));

        bool connectStatus = tryConnectAgent(agent);
        if (!connectStatus)
        {
            continue;
        }
        m_agents.push_back(agent);
    }

    fs.close();
}

void Server::Stop ()
{
    m_deliveryFactory.StopAll();
    std::vector<SharedPtr<Event> >(m_eventBus->Shutdown()); // TODO: log these events
    m_middlewarePair.second->Join();
}

int Server::hardwareCores () NOEXCEPTIONS
{
    return get_nprocs();
}

GroupTag Server::numOfTags (unsigned char a_tagFactor) NOEXCEPTIONS
{
    return hardwareCores() * a_tagFactor;
}

void Server::startFactory () NOEXCEPTIONS
{
    for (std::vector<SharedPtr<TaggedDistributionChannel> >::size_type i = 0;
         i < m_taggedChannels.size();
         ++i)
    {
        m_deliveryFactory.AddCourier(m_taggedChannels[i], m_taggedChannels[i]);
    }
}

void Server::startMiddleware () NOEXCEPTIONS
{
    m_middlewarePair.second = SharedPtr<advcpp::Thread>(new advcpp::Thread(m_middlewarePair.first));
}

Server::ConfigFileLines Server::parseLines (std::ifstream& a_fs) const NOEXCEPTIONS
{
    std::string endl;
    ConfigFileLines lines;
    getline(a_fs, lines.m_id);
    getline(a_fs, lines.m_type);
    getline(a_fs, lines.m_room);
    getline(a_fs, lines.m_floor);
    getline(a_fs, lines.m_log);
    getline(a_fs, lines.m_config);
    getline(a_fs, endl);
    return lines;
}

std::pair<SharedPtr<advcpp::SOLibHandler>, bool> Server::tryMakeSOHandler
    (std::string const& a_libName) const NOEXCEPTIONS
{
    SharedPtr<advcpp::SOLibHandler> soHandler;
    try
    {
        soHandler = SharedPtr<advcpp::SOLibHandler>(new advcpp::SOLibHandler(a_libName.c_str()));
    }
    catch (std::exception const& e)
    {
        std::cerr << e.what() << std::endl; // TODO: log
        return std::make_pair(soHandler, false);
    }
    return std::make_pair(soHandler, true);
}

std::pair<Server::AgentMaker, bool> Server::tryMakeAgentMaker
    (SharedPtr<advcpp::SOLibHandler> const& a_libHandler) NOEXCEPTIONS
{
    AgentMaker makeAgent = 0;
    try
    {
        makeAgent = a_libHandler->GetSymbolPtr<AgentMaker>("MakeAgent");
    }
    catch (std::exception const& e)
    {
        std::cerr << e.what() << std::endl; // TODO: log
        return std::make_pair(makeAgent, false);
    }
    return std::make_pair(makeAgent, true);
}

bool Server::tryConnectAgent (SharedPtr<IAgent> const& a_agent) NOEXCEPTIONS
{
    try
    {
        a_agent->Connect(m_eventBus, m_consumerMapTagged);
    }
    catch (std::exception const& e)
    {
        assert(!"Unsafe agent Connect()");
        std::cerr << e.what() << std::endl; // TODO: log
        return false;
    }
    catch (...)
    {
        assert(!"Non documented agent Connect() exception");
        return false;
    }
    return true;
}

} // smart_home