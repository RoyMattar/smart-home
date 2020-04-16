#ifndef I_EVENT_CONSUMER_HPP
#define I_EVENT_CONSUMER_HPP

#include "event.hpp"

namespace smart_home
{

class IEventConsumer
{
public:
    virtual ~IEventConsumer ();

    virtual void Consume (SharedPtr<Event> const& a_pEvent) = 0;
};

inline IEventConsumer::~IEventConsumer ()
{ }

} // smart_home

#endif // I_EVENT_CONSUMER_HPP