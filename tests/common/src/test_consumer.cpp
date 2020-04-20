#include "test_consumer.hpp"
#include "common_utils.hpp"
#include "i_event_subscriber.hpp"
#include "i_event_consumer.hpp"
#include "event.hpp"
#include "i_consumer_registrar.hpp"

namespace smart_home
{

TestConsumer::TestConsumer (Event::Type const& a_eventType, Event::Location const& a_eventLocation)
    : m_eventType(a_eventType)
    , m_eventLocation(a_eventLocation)
    , m_countDelivered(0)
{ }

void TestConsumer::Subscribe (SharedPtr<IConsumerRegistrar> const& a_consumerRegistrar)
{
    a_consumerRegistrar->Register(shared_from_this(), m_eventType, m_eventLocation);
}

void TestConsumer::Consume (SharedPtr<Event> const& a_pEvent)
{
    ++m_countDelivered;
}

} // smart_home