#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sys/sysinfo.h> // get_nprocs()

#include "smart_home_server.hpp"
#include "common_utils.hpp"
#include "cyclic_tag.hpp"
#include "event_bus.hpp"
#include "consumer_map_tagged.hpp"
#include "event_distributor.hpp"
#include "event_delivery_factory.hpp"
#include "tagged_distribution_channel.hpp"

namespace smart_home
{

SmartHomeServer::SmartHomeServer (std::string const& a_configFile, unsigned char a_parallelFactor,
                                  size_t a_publicationBandwidth, size_t a_distributionBandwidth)
    : m_configFile(a_configFile)
    , m_numOfTags(numOfTags(a_parallelFactor))
    , m_publicationBandwidth(a_publicationBandwidth)
    , m_distributionBandwidth(a_distributionBandwidth)
{ }

void SmartHomeServer::Go ()
{
    std::ifstream fs(m_configFile);
    if (!fs.is_open())
    {
        std::cerr << "Error opening config file" << std::endl;
        return;
    }

    SharedPtr<EventBus> eventBus(new EventBus(m_publicationBandwidth));
    SharedPtr<ConsumerMapTagged<> > consumerMapTagged(new ConsumerMapTagged<>(m_numOfTags));
    SharedPtr<EventDistributor> eventDistributor(new EventDistributor());
    EventDeliveryFactory eventDeliveryFactory;

    std::vector<SharedPtr<TaggedDistributionChannel> > taggedDistributionChannels;
    for (CyclicTag::TagType i = 0; i < m_numOfTags; ++i)
    {
        SharedPtr<Tag
        taggedDistributionChannels.push_back()
    }

    std::string line;
    while (getline(fs, line))
    {

    }
}

int SmartHomeServer::hardwareCores () NOEXCEPTIONS
{
    return get_nprocs();
}

CyclicTag::TagType SmartHomeServer::numOfTags (unsigned char a_tagFactor) NOEXCEPTIONS
{
    return hardwareCores() * a_tagFactor;
}

} // smart_home