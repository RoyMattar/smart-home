#include <iostream> // std::cerr
#include <stdexcept> // std::exception
#include <cassert>

#include "event_middleware.hpp"
#include "common_utils.hpp"
#include "i_pull_event_bus.hpp"
#include "i_consumer_lister.hpp"
#include "i_event_distributor.hpp"
#include "event.hpp"
#include "event_topic.hpp"
#include "distribution_list_tagged.hpp"

#include "event_bus.hpp"

namespace smart_home
{

EventMiddleware::EventMiddleware (SharedPtr<IPullEventBus> const& a_pullBus,
        SharedPtr<IConsumerLister> const& a_consumerLister,
        SharedPtr<IEventDistributor> const& a_eventDistributor)
    : m_pullBus(a_pullBus)
    , m_consumerLister(a_consumerLister)
    , m_eventDistributor(a_eventDistributor)
{ }

void EventMiddleware::Run ()
{
    while (true)
    {
        SharedPtr<Event> pEvent;
        if (!tryPull(pEvent))
        {
            break;
        }
        
        SharedPtr<DistributionListTagged> distributionListTagged = tryList(EventTopic(*pEvent));
        tryDistribute(pEvent, distributionListTagged);
    }
}

bool EventMiddleware::tryPull (SharedPtr<Event>& a_pEventRef)
{
    try
    {
        m_pullBus->Pull(a_pEventRef);
    }
    catch (IPullEventBusShutdownExc const&)
    {
        return false;
    }
    return true;
}

SharedPtr<DistributionListTagged> EventMiddleware::tryList (EventTopic const& a_eventTopic)
{
    SharedPtr<DistributionListTagged> distributionListTagged;
    try
    {
        distributionListTagged = m_consumerLister->List(a_eventTopic);
    }
    catch (std::exception const& a_e)
    {
        std::cerr << a_e.what() << std::endl;
        assert(!"Unsafe IConsumerLister");
    }
    catch (...)
    {
        assert(!"Non documented exception thrown by IConsumerLister");
    }
    return distributionListTagged;
}

void EventMiddleware::tryDistribute (SharedPtr<Event> const& a_pEvent,
                                     SharedPtr<DistributionListTagged> const& a_distributionListTagged)
{
    try
    {
        m_eventDistributor->Distribute(a_pEvent, a_distributionListTagged);
    }
    catch (std::exception const& a_e)
    {
        std::cerr << a_e.what() << std::endl;
        assert(!"Unsafe IEventDistributor");
    }
    catch (...)
    {
        assert(!"Non documented exception thrown by IEventDistributor");
    }
}

} // smart_home