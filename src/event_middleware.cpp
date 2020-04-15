#include <iostream> // std::cerr
#include <cassert>

#include "event_middleware.hpp"
#include "common_utils.hpp"
#include "event.hpp"
#include "i_pull_event_bus.hpp"
#include "i_consumer_lister.hpp"
#include "i_event_distributor.hpp"

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
        
        SharedPtr<ConsumerListing> consumerListing = tryList(pEvent);
        tryDistribute(pEvent, consumerListing);
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

SharedPtr<EventMiddleware::ConsumerListing> EventMiddleware::tryList (SharedPtr<Event> const& a_pEvent)
{
    SharedPtr<ConsumerListing> consumerListing;
    try
    {
        consumerListing = m_consumerLister->List(a_pEvent);
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
    return consumerListing;
}

void EventMiddleware::tryDistribute (SharedPtr<Event> const& a_pEvent, SharedPtr<ConsumerListing> const& a_consumerListing)
{
    try
    {
        m_eventDistributor->Distribute(a_pEvent, a_consumerListing);
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