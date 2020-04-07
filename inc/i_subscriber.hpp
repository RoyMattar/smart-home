#ifndef I_SUBSCRIBER_HPP
#define I_SUBSCRIBER_HPP

#include "common_utils.hpp"
#include "event.hpp"

namespace smart_home
{
class IRegistrar;

class ISubscriber
{
public:
    virtual ~ISubscriber ();

    virtual void Subscribe (SharedPtr<IRegistrar> const& a_registrar);
    virtual void Deliver (SharedPtr<Event> const& a_pEvent);
};

inline ISubscriber::~ISubscriber ()
{ }

} // smart_home

#endif // I_SUBSCRIBER_HPP