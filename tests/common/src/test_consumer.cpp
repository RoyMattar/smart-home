#include "test_consumer.hpp"
#include "common_utils.hpp"
#include "i_event_subscriber.hpp"
#include "i_event_consumer.hpp"
#include "event.hpp"
#include "i_consumer_registrar.hpp"

namespace smart_home
{

int TestConsumer::s_id = 0;

TestConsumer::TestConsumer (Event::Type const& a_eventType)
    : m_eventType(a_eventType)
    , m_id(++s_id)
    , m_isEventDelivered(false)
{ }

void TestConsumer::Subscribe (SharedPtr<IConsumerRegistrar> const& a_consumerRegistrar)
{
    a_consumerRegistrar->Register(m_eventType, shared_from_this());
}

void TestConsumer::Consume (SharedPtr<Event> const& a_pEvent)
{
    m_isEventDelivered = true;
}

int TestConsumer::GetID () const
{
    return m_id;
}

bool TestConsumer::IsEventDelivered () const
{
    return m_isEventDelivered;
}

} // smart_home