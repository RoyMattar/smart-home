#ifndef I_CONSUMER_REGISTRAR_HPP
#define I_CONSUMER_REGISTRAR_HPP

#include "common_utils.hpp"
#include "event.hpp"
#include "i_event_consumer.hpp"

namespace smart_home
{

class IConsumerRegistrar
{
public:
    virtual ~IConsumerRegistrar ();

    virtual void Register (Event::Type a_eventType, SharedPtr<IEventConsumer> const& a_newConsumer);
    virtual void Deregister (Event::Type a_eventType, SharedPtr<IEventConsumer> const& a_oldConsumer);
};

inline IConsumerRegistrar::~IConsumerRegistrar ()
{ }

} // smart_home

#endif // I_CONSUMER_REGISTRAR_HPP