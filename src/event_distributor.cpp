#include <vector>
#include <tr1/unordered_map>

#include "event_distributor.hpp"
#include "common_utils.hpp"
#include "i_push_tagged_distribution_channel.hpp"
#include "event.hpp"
#include "distribution_list_tagged.hpp"

namespace smart_home
{

EventDistributor::EventDistributor (std::vector<SharedPtr<IPushTaggedDistributionChannel> > const& a_taggedChannels)
    : m_channelMap()
{
    mapTaggedChannels(a_taggedChannels);
}

void EventDistributor::Distribute (SharedPtr<Event> const& a_pEvent,
                             SharedPtr<DistributionListTagged> const& a_distributionListTagged)
{
    for (DistributionListTagged::size_type i = 0;
         i < a_distributionListTagged->size();
         ++i)
    {
        GroupTag tag = (*a_distributionListTagged)[i].first;
        SharedPtr<IEventConsumer> consumer = (*a_distributionListTagged)[i].second;

        SharedPtr<DeliveryBox> deliveryBox = makeDeliveryBox(a_pEvent, consumer);
        pushBoxToChannel(tag, deliveryBox);
    }
}

SharedPtr<DeliveryBox> EventDistributor::makeDeliveryBox (SharedPtr<Event> const& a_pEvent, SharedPtr<IEventConsumer> const& a_pConsumer)
{
    return SharedPtr<DeliveryBox>(new DeliveryBox(a_pEvent, a_pConsumer));
}

void EventDistributor::mapTaggedChannels (std::vector<SharedPtr<IPushTaggedDistributionChannel> > const& a_taggedChannels)
{
    for (std::vector<SharedPtr<IPushTaggedDistributionChannel> >::size_type i = 0;
         i < a_taggedChannels.size();
         ++i)
    {
        SharedPtr<IPushTaggedDistributionChannel> currentChannel = a_taggedChannels[i];
        m_channelMap[currentChannel->GetTag()] = currentChannel;
    }
}

void EventDistributor::pushBoxToChannel (GroupTag a_channelTag, SharedPtr<DeliveryBox> const& a_deliveryBox)
{
    m_channelMap[a_channelTag]->Push(a_deliveryBox);
}

} // smart_home