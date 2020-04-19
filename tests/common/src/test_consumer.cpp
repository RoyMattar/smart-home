#include "test_consumer.hpp"
#include "common_utils.hpp"
#include "i_event_subscriber.hpp"
#include "i_event_consumer.hpp"
#include "event.hpp"
#include "i_consumer_registrar.hpp"

namespace smart_home
{

TestConsumer::TestConsumer (Event::Type const& a_eventType)
    : m_eventType(a_eventType)
    , m_countDelivered(0)
{ }

void TestConsumer::Subscribe (SharedPtr<IConsumerRegistrar> const& a_consumerRegistrar)
{
    a_consumerRegistrar->Register(m_eventType, shared_from_this());
}

void TestConsumer::Consume (SharedPtr<Event> const& a_pEvent)
{
    ++m_countDelivered;
}

Event::Type const& TestConsumer::GetType () const
{
    return m_eventType;
}

size_t TestConsumer::CountDelivered () const
{
    return m_countDelivered;
}

} // smart_home