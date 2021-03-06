#include <iostream>

#include "test_consumer.hpp"
#include "common_utils.hpp"
#include "i_event_subscriber.hpp"
#include "i_event_consumer.hpp"
#include "event.hpp"
#include "event_topic.hpp"
#include "i_consumer_registrar.hpp"
#include "mutex.hpp"
#include "lock_guard.hpp"

namespace smart_home
{

TestConsumer::TestConsumer (EventTopic const& a_eventTopic, advcpp::Mutex& a_printMutex)
    : m_eventTopic(a_eventTopic)
    , m_countDelivered(0)
    , m_printMutex(a_printMutex)
{ }

void TestConsumer::Subscribe (SharedPtr<IConsumerRegistrar> const& a_consumerRegistrar)
{
    a_consumerRegistrar->Register(m_eventTopic, shared_from_this());
}

void TestConsumer::Consume (SharedPtr<Event> const& a_pEvent)
{
    ++m_countDelivered;

    advcpp::LockGuard lg(m_printMutex);
    std::cout << "Consumer registered to topic "; m_eventTopic.Print();
    std::cout << " received the following event:" << std::endl;
    a_pEvent->Print();
    std::cout << "This consumer has received " << m_countDelivered
              << " event(s) by now." << std::endl;
}

} // smart_home