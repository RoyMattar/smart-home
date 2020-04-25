#include <vector>
#include <cstddef> // size_t

#include "event_delivery_factory.hpp"
#include "common_utils.hpp"
#include "i_distribution_channel.hpp"
#include "thread_group_mt.hpp"
#include "event_courier.hpp"
#include "toxic_agent.hpp"

namespace smart_home
{

void EventDeliveryFactory::AddCourier (SharedPtr<IDistributionChannel> const& a_distributionChannel)
{
    SharedPtr<EventCourier> newCourier(new EventCourier(a_distributionChannel));
    m_deliveryCrew.Add(newCourier);
    m_distributionChannels.push_back(a_distributionChannel);
}

void EventDeliveryFactory::StopAll ()
{
    intoxicateAll();
    joinAll();
}

void EventDeliveryFactory::intoxicateAll ()
{
    SharedPtr<Event> dummyEvent;
    for (std::vector<SharedPtr<IDistributionChannel> >::size_type i = 0;
         i < m_distributionChannels.size();
         ++i)
    {
        SharedPtr<ToxicAgent> toxicAgent(new ToxicAgent());
        SharedPtr<DeliveryBox> toxicDeliveryBox(new DeliveryBox(dummyEvent, toxicAgent));
        m_distributionChannels[i]->Push(toxicDeliveryBox);
    }
}

void EventDeliveryFactory::joinAll ()
{
    // since join() also erases, must be one of the following

    // option 1:
    size_t numOfIterations = m_deliveryCrew.NumOfThreads();
    for (size_t i = 0; i < numOfIterations; ++i)
    {
        m_deliveryCrew.Join(0);
    }

    // option 2:
    // for (size_t i = m_deliveryCrew.NumOfThreads() - 1; i >= 0; --i)
    // {
    //     m_deliveryCrew.Join(i);
    // }
}

} // smart_home