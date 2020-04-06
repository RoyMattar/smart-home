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

class EventBus : private advcpp::Uncopyable, public IPushEventBus, public IPullEventBus
{
public:
    EventBus (size_t a_capacity);
    //~EventBus () = default;

    virtual void Push (const SharedPtr<Event>& a_event);
    virtual void Pull (SharedPtr<Event>& a_event);
    size_t NumOfElems () const NOEXCEPTIONS;

private:
    typedef advcpp::WaitableBoundedQueue<SharedPtr<Event> > EventWBQ;

    EventWBQ m_eventWBQ;
};

inline size_t EventBus::NumOfElems () const NOEXCEPTIONS{
    return m_eventWBQ.NumOfElems();
}

} // smart_home

#endif // EVENT_BUS_HPP