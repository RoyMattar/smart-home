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

    virtual void Register (Event::Type const& a_eventType, SharedPtr<IEventConsumer> const& a_newConsumer) = 0;
    virtual void Deregister (Event::Type const& a_eventType, SharedPtr<IEventConsumer> const& a_oldConsumer) = 0;
};

inline IConsumerRegistrar::~IConsumerRegistrar ()
{ }

} // smart_home

#endif // I_CONSUMER_REGISTRAR_HPP