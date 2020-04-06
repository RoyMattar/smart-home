#include <cstddef> //size_t

#include "event_bus.hpp"
#include "common_utils.hpp"
#include "event.hpp"

namespace smart_home
{

EventBus::EventBus (size_t a_capacity)
    : m_eventWBQ(a_capacity)
{ }

void EventBus::Push (const SharedPtr<Event>& a_event)
{
    m_eventWBQ.Enqueue(a_event);
}

void EventBus::Pull (SharedPtr<Event>& a_event)
{
    m_eventWBQ.Dequeue(a_event);
}

} // smart_home