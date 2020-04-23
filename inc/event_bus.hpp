#ifndef EVENT_BUS_HPP
#define EVENT_BUS_HPP

#include <cstddef> //size_t

#include "common_utils.hpp"
#include "i_push_event_bus.hpp"
#include "i_pull_event_bus.hpp"
#include "waitable_bounded_queue.hpp"
#include "event.hpp"

namespace smart_home
{

class EventBus : public IPushEventBus, public IPullEventBus, private advcpp::Uncopyable
{
public:
    EventBus (size_t a_capacity);
    //~EventBus () = default;

    virtual void Push (SharedPtr<Event> const& a_pEvent);
    virtual void Pull (SharedPtr<Event>& a_pEvent);
    size_t NumOfElems () const NOEXCEPTIONS;

private:
    typedef advcpp::WaitableBoundedQueue<SharedPtr<Event> > BusType;

private:
    BusType m_bus;
};

class EventBusShutdownExc : public IPushEventBusShutdownExc, public IPullEventBusShutdownExc
{
    const char* what () const NOEXCEPTIONS;
};

inline size_t EventBus::NumOfElems () const NOEXCEPTIONS
{
    return m_bus.NumOfElems();
}

inline const char* EventBusShutdownExc::what() const NOEXCEPTIONS
{
    return "Event bus is shutting down";
}

} // smart_home

#endif // EVENT_BUS_HPP