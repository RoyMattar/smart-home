#include "mu_test.h"

#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h> // sleep() - simulate

#include "i_agent.hpp"
#include "so_lib_handler.hpp"
#include "cyclic_tag.hpp"
#include "common_utils.hpp"
#include "event_bus.hpp"
#include "consumer_map_tagged.hpp"
#include "event_distributor.hpp"
#include "event_delivery_factory.hpp"
#include "tagged_distribution_channel.hpp"
#include "event_middleware.hpp"
#include "agent_info.hpp"

using namespace advcpp;
using namespace smart_home;

const std::string configFile("config.ini");
const CyclicTag::TagType numOfTags = 6;
const size_t publicationBandwidth = 32;
const size_t distributionBandwidth = 32;

UNIT(complete)
    std::ifstream fs(configFile.c_str());
    if (!fs.is_open())
    {
        std::cerr << "Error opening config file" << std::endl;
        exit(1);
    }

    std::vector<SharedPtr<SOLibHandler> > libHandlers;

    SharedPtr<EventBus> eventBus(new EventBus(publicationBandwidth));
    SharedPtr<ConsumerMapTagged<> > consumerMapTagged(new ConsumerMapTagged<>(numOfTags));
    SharedPtr<EventDistributor> eventDistributor(new EventDistributor());
    EventDeliveryFactory eventDeliveryFactory;

    std::vector<SharedPtr<TaggedDistributionChannel> > taggedDistributionChannels;
    for (CyclicTag::TagType tag = 0; tag < numOfTags; ++tag)
    {
        SharedPtr<TaggedDistributionChannel> chan(new TaggedDistributionChannel(distributionBandwidth, tag));
        taggedDistributionChannels.push_back(chan);
        eventDistributor->AddChannel(chan);
        eventDeliveryFactory.AddCourier(chan);
    }

    SharedPtr<EventMiddleware> middleware(new EventMiddleware(eventBus, consumerMapTagged, eventDistributor));
    SharedPtr<Thread> tMid(new Thread(middleware));

    std::vector<SharedPtr<IAgent> > agents;
    while (!fs.eof())
    {
        std::string id;
        getline(fs, id);
        std::string type;
        getline(fs, type);
        std::string room;
        getline(fs, room);
        std::string floor;
        getline(fs, floor);
        std::string log;
        getline(fs, log);
        std::string config;
        getline(fs, config);

        std::string lib = "lib" + type + ".so";
        SharedPtr<SOLibHandler> soHandler(new SOLibHandler(lib.c_str()));
        libHandlers.push_back(soHandler);
        typedef SharedPtr<IAgent> (*AgentMaker)(AgentInfo::DeviceID const& a_id,
                                                AgentInfo::DeviceLocation const& a_location,
                                                AgentInfo::AgentLog const& a_log,
                                                AgentInfo::AgentConfig const& a_config);
        AgentMaker makeAgent = soHandler->GetSymbolPtr<AgentMaker>("MakeAgent");
        SharedPtr<IAgent> agent(makeAgent(id, AgentInfo::DeviceLocation(floor, room), log, config));
        agent->Connect(eventBus, consumerMapTagged);
        agents.push_back(agent);
    }
    sleep(5);
END_UNIT


TEST_SUITE(complete)
    TEST(complete)
END_SUITE