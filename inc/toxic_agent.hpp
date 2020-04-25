#ifndef TOXIC_AGENT_HPP
#define TOXIC_AGENT_HPP

#include <stdexcept> // std::exception

#include "i_event_consumer.hpp"
#include "common_utils.hpp"
#include "event.hpp"

namespace smart_home
{

class ToxicAgent : public IEventConsumer, private advcpp::Uncopyable
{
    friend class EventDeliveryFactory;
    friend class EventCourier;

public:
    //~ToxicAgent () = default;

private:
    struct ToxicAgentExc;

private:
    ToxicAgent () NOEXCEPTIONS;

    //@exception: throws ToxicAgentExc 
    virtual void Consume (SharedPtr<Event> const& a_pEvent);
};

struct ToxicAgent::ToxicAgentExc : public std::exception
{
    const char* what () const NOEXCEPTIONS;
};

inline ToxicAgent::ToxicAgent () NOEXCEPTIONS { }

inline const char* ToxicAgent::ToxicAgentExc::what () const NOEXCEPTIONS
{
    return "Toxic agent exception";
}

} // smart_home

#endif // TOXIC_AGENT_HPP