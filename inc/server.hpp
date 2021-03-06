#ifndef SMART_HOME_SERVER_HPP
#define SMART_HOME_SERVER_HPP

#include <vector>
#include <string>
#include <utility> // std::pair
#include <fstream> // std::ifstream
#include <cstddef> // size_t

#include "common_utils.hpp"
#include "so_lib_handler.hpp"
#include "group_tag.hpp"
#include "event_bus.hpp"
#include "consumer_map_tagged.hpp"
#include "event_distributor.hpp"
#include "tagged_distribution_channel.hpp"
#include "event_middleware.hpp"
#include "event_delivery_factory.hpp"
#include "i_agent.hpp"
#include "agent_info.hpp"
#include "thread.hpp"

namespace smart_home
{

class Server : private advcpp::Uncopyable
{
public:
    Server (std::string const& a_configFile, unsigned char a_parallelFactor,
            size_t a_publicationBandwidth, size_t a_distributionBandwidth);
    //~Server () = default;

    void Start ();
    void Stop ();

private:
    typedef SharedPtr<IAgent> (*AgentMaker)(AgentInfo::DeviceID const& a_id,
                                            AgentInfo::DeviceLocation const& a_location,
                                            AgentInfo::AgentLog const& a_log,
                                            AgentInfo::AgentConfig const& a_config);
private:
    struct ConfigFileLines;

private:
    static int hardwareCores () NOEXCEPTIONS; // move to separate file
    static GroupTag numOfTags (unsigned char a_tagFactor) NOEXCEPTIONS;

    void startFactory () NOEXCEPTIONS;
    void startMiddleware () NOEXCEPTIONS;
    ConfigFileLines parseLines (std::ifstream& a_fs) const NOEXCEPTIONS;
    std::pair<SharedPtr<advcpp::SOLibHandler>, bool> tryMakeSOHandler (std::string const& a_libName) const NOEXCEPTIONS;
    std::pair<AgentMaker, bool> tryMakeAgentMaker (SharedPtr<advcpp::SOLibHandler> const& a_libHandler) NOEXCEPTIONS;
    bool tryConnectAgent (SharedPtr<IAgent> const& a_agent) NOEXCEPTIONS;
    void disconnectAgents ();

private:
    typedef std::vector<SharedPtr<advcpp::SOLibHandler> > SOHandlers;
    typedef std::vector<SharedPtr<TaggedDistributionChannel> > TaggedChannels;
    typedef std::vector<SharedPtr<IAgent> > Agents;

private:
    std::string m_configFile;
<<<<<<< HEAD
    SOHandlers m_soHandlers;
    CyclicTag::TagType m_numOfTags;
=======
    std::vector<SharedPtr<advcpp::SOLibHandler> > m_soHandlers;
    GroupTag m_numOfTags;
>>>>>>> 3795e634d7389dc1a3a5292fc6c5f02154d15a8f
    SharedPtr<EventBus> m_eventBus;
    SharedPtr<ConsumerMapTagged<> > m_consumerMapTagged;
    SharedPtr<EventDistributor> m_distributor;
    EventDeliveryFactory m_deliveryFactory;
    TaggedChannels m_taggedChannels;
    std::pair<SharedPtr<EventMiddleware>, SharedPtr<advcpp::Thread> > m_middlewarePair;
    Agents m_agents;
};

} // smart_home

#endif // SMART_HOME_SERVER_HPP