#include <vector>
#include <cstddef> // size_t

#include "test_distribution_bundle.hpp"
#include "common_utils.hpp"
#include "group_tag.hpp"
#include "tagged_distribution_channel.hpp"
#include "event_distributor.hpp"
#include "event_delivery_factory.hpp"

namespace smart_home
{

TestDistributionBundle::TestDistributionBundle (GroupTag a_numOfTags, size_t a_channelCapacity)
    : numOfTags(a_numOfTags)
    , channelCapacity(a_channelCapacity)
    , channels(MakeDistributionChannels(a_channelCapacity, a_numOfTags))
    , distributor(MakeDistributor(channels))
    , factory(MakeDeliveryFactory(channels))
{ }

std::vector<SharedPtr<TaggedDistributionChannel> > MakeDistributionChannels 
    (size_t a_channelCapacity, GroupTag a_numOfTags)
{
    std::vector<SharedPtr<TaggedDistributionChannel> > channels(a_numOfTags);
    for (std::vector<SharedPtr<TaggedDistributionChannel> >::size_type i = 0;
         i < channels.size();
         ++i)
    {
        channels[i] = SharedPtr<TaggedDistributionChannel>
                        (new TaggedDistributionChannel(a_channelCapacity, i));
    }
    return channels;
}

SharedPtr<EventDistributor> MakeDistributor (std::vector<SharedPtr<TaggedDistributionChannel> > a_channels)
{
    SharedPtr<EventDistributor> distributor(new EventDistributor());
    for (std::vector<SharedPtr<TaggedDistributionChannel> >::size_type i = 0;
         i < a_channels.size();
         ++i)
    {
        distributor->AddChannel(a_channels[i]);
    }
    return distributor;
}

SharedPtr<EventDeliveryFactory> MakeDeliveryFactory (std::vector<SharedPtr<TaggedDistributionChannel> > a_channels)
{
    SharedPtr<EventDeliveryFactory> factory(new EventDeliveryFactory());
    for (std::vector<SharedPtr<TaggedDistributionChannel> >::size_type i = 0;
         i < a_channels.size();
         ++i)
    {
        factory->AddCourier(a_channels[i]);
    }
    return factory;
}

} // smart_home