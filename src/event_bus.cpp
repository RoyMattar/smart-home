#include <cstddef> //size_t

#include "event_bus.hpp"
#include "common_utils.hpp"
#include "waitable_bounded_queue.hpp"
#include "event.hpp"

namespace smart_home
{

EventBus::EventBus (size_t a_capacity)
    : m_bus(a_capacity)
{ }

void EventBus::Push (SharedPtr<Event> const& a_pEvent)
{
    try
    {
        m_bus.Enqueue(a_pEvent);
    }
    catch (advcpp::WaitableBoundedQueueShutdownExc const&)
    {
        throw EventBusShutdownExc();
    }
}

void EventBus::Pull (SharedPtr<Event>& a_pEvent)
{
    try
    {
        m_bus.Dequeue(a_pEvent);
    }
    catch (advcpp::WaitableBoundedQueueShutdownExc const&)
    {
        throw EventBusShutdownExc();
    }
}

std::vector<SharedPtr<Event> > EventBus::Shutdown ()
{
    return m_bus.Shutdown();
}

} // smart_home