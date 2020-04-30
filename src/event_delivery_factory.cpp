#include <vector>
#include <utility> // std::make_pair()
#include <cstddef> // size_t

#include "event_delivery_factory.hpp"
#include "common_utils.hpp"
#include "i_push_distribution_channel.hpp"
#include "i_pull_distribution_channel.hpp"
#include "thread_group_mt.hpp"
#include "event_courier.hpp"
#include "toxic_agent.hpp"

namespace smart_home
{

void EventDeliveryFactory::AddCourier (SharedPtr<IPullDistributionChannel> const& a_pullChannel,
                                       SharedPtr<IPushDistributionChannel> const& a_pushChannel)
{
    SharedPtr<EventCourier> newCourier(new EventCourier(a_pullChannel));
    m_deliveryCrew.Add(newCourier);
    m_distributionChannels.push_back(std::make_pair(a_pullChannel, a_pushChannel));
}

void EventDeliveryFactory::StopAll ()
{
    intoxicateAll();
    m_deliveryCrew.JoinAll();
}

void EventDeliveryFactory::intoxicateAll ()
{
    SharedPtr<Event> dummyEvent;
    for (std::vector<ChannelPair>::size_type i = 0;
         i < m_distributionChannels.size();
         ++i)
    {
        SharedPtr<ToxicAgent> toxicAgent(new ToxicAgent());
        SharedPtr<DeliveryBox> toxicDeliveryBox(new DeliveryBox(dummyEvent, toxicAgent));
        m_distributionChannels[i].second->Push(toxicDeliveryBox);
    }
}

} // smart_home