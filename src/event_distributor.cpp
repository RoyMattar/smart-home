#include <vector>
#include <tr1/unordered_map>
#include <stdexcept> // std::exception, std::out_of_range

#include "event_distributor.hpp"
#include "common_utils.hpp"
#include "i_push_tagged_distribution_channel.hpp"
#include "event.hpp"
#include "distribution_list_tagged.hpp"

namespace smart_home
{

// struct ChannelNotFoundByTagExc : public std::exception
// {
//     const char* what () const NOEXCEPTIONS
//     {
//         return "No channel by this tag";
//     }
// };

void EventDistributor::AddChannel (SharedPtr<IPushTaggedDistributionChannel> a_taggedChannel)
{
    m_channelMap[a_taggedChannel->GetTag()] = a_taggedChannel;
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

void EventDistributor::pushBoxToChannel (GroupTag a_channelTag, SharedPtr<DeliveryBox> const& a_deliveryBox)
{   
    typename ChannelMap::const_iterator channelPairItr = m_channelMap.find(a_channelTag);
    if (channelPairItr == m_channelMap.end())
    {
        throw std::out_of_range("No channel by this tag");
    }

    m_channelMap[a_channelTag]->Push(a_deliveryBox);
}

} // smart_home