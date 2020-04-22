#ifndef I_CONSUMER_REGISTRAR_HPP
#define I_CONSUMER_REGISTRAR_HPP

#include "common_utils.hpp"
#include "event_topic.hpp"
#include "i_event_consumer.hpp"

namespace smart_home
{

class IConsumerRegistrar
{
public:
    virtual ~IConsumerRegistrar ();

    virtual bool Register (EventTopic const& a_eventTopic, SharedPtr<IEventConsumer> const& a_newConsumer) = 0;
    virtual bool Deregister (EventTopic const& a_eventTopic, SharedPtr<IEventConsumer> const& a_consumer) = 0;
};

inline IConsumerRegistrar::~IConsumerRegistrar () { }

} // smart_home

#endif // I_CONSUMER_REGISTRAR_HPP