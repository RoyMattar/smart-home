#ifndef TEST_DISTRIBUTION_BUNDLE
#define TEST_DISTRIBUTION_BUNDLE

#include <vector>
#include <cstddef> // size_t

#include "common_utils.hpp"
#include "group_tag.hpp"
#include "tagged_distribution_channel.hpp"
#include "event_distributor.hpp"
#include "event_delivery_factory.hpp"

namespace smart_home
{

struct TestDistributionBundle
{
    TestDistributionBundle (GroupTag a_numOfTags, size_t a_channelCapacity);

    GroupTag numOfTags;
    size_t channelCapacity;
    std::vector<SharedPtr<TaggedDistributionChannel> > channels;
    SharedPtr<EventDistributor> distributor;
    SharedPtr<EventDeliveryFactory> factory;
};

std::vector<SharedPtr<TaggedDistributionChannel> > MakeDistributionChannels (size_t a_channelCapacity, GroupTag a_numOfTags);
SharedPtr<EventDistributor> MakeDistributor (std::vector<SharedPtr<TaggedDistributionChannel> > a_channels);
SharedPtr<EventDeliveryFactory> MakeDeliveryFactory (std::vector<SharedPtr<TaggedDistributionChannel> > a_channels);

} // smart_home

#endif // TEST_DISTRIBUTION_BUNDLE