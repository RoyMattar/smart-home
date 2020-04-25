#ifndef I_EVENT_PUBLISHER_HPP
#define I_EVENT_PUBLISHER_HPP

#include "event.hpp"

namespace smart_home
{

class IEventPublisher
{
public:
    virtual ~IEventPublisher ();

    virtual void Publish (Event const& a_event) = 0;
};

inline IEventPublisher::~IEventPublisher () { }

} // smart_home

#endif // I_EVENT_PUBLISHER_HPP