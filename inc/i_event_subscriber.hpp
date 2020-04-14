#ifndef I_EVENT_SUBSCRIBER_HPP
#define I_EVENT_SUBSCRIBER_HPP

#include "common_utils.hpp"
#include "i_handlers_registrar.hpp"

namespace smart_home
{

class IEventSubscriber
{
public:
    virtual ~IEventSubscriber ();

    virtual void Subscribe (SharedPtr<IHandlersRegistrar> const& a_handlersRegistrar);
};

inline IEventSubscriber::~IEventSubscriber ()
{ }

} // smart_home

#endif // I_EVENT_SUBSCRIBER_HPP