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

    virtual void Register (SharedPtr<IEventConsumer> const& a_newConsumer, Event::Type const& a_eventType, Event::Location const& a_eventLocation) = 0;
    virtual void Deregister (SharedPtr<IEventConsumer> const& a_consumer, Event::Type const& a_eventType, Event::Location const& a_eventLocation) = 0;
};

inline IConsumerRegistrar::~IConsumerRegistrar ()
{ }

} // smart_home

#endif // I_CONSUMER_REGISTRAR_HPP