#ifndef I_EVENT_SUBSCRIBER_HPP
#define I_EVENT_SUBSCRIBER_HPP

#include "common_utils.hpp"
#include "i_consumer_registrar.hpp"

namespace smart_home
{

class IEventSubscriber
{
public:
    virtual ~IEventSubscriber ();

    virtual void Subscribe (SharedPtr<IConsumerRegistrar> const& a_consumerRegistrar) = 0;
};

inline IEventSubscriber::~IEventSubscriber () { }

} // smart_home

#endif // I_EVENT_SUBSCRIBER_HPP