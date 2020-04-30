#include <iostream>
#include <cstddef> // size_t

#include "test_controller.hpp"
#include "common_utils.hpp"
#include "i_push_event_bus.hpp"
#include "i_consumer_registrar.hpp"
#include "agent_info.hpp"
#include "event.hpp"
#include "mutex.hpp"
#include "lock_guard.hpp"
#include "event_topic.hpp"

namespace smart_home
{

TestController::TestController (AgentInfo::DeviceID const& a_id, AgentInfo::DeviceLocation const& a_location,
                                AgentInfo::AgentLog const& a_log, AgentInfo::AgentConfig const& a_config,
                                EventTopic const& a_topic)
    : m_info(a_id, "TestController", a_location, a_log, a_config)
    , m_topic(a_topic)
    , m_countConsumed(0)
    , m_printMutex()
    , m_registrar()
{ }

void TestController::Connect (SharedPtr<IPushEventBus> const& a_pushBus,
                              SharedPtr<IConsumerRegistrar> const& a_registrar)
{
    m_registrar = a_registrar;
    m_registrar->Register(m_topic, shared_from_this());
}

void TestController::Disconnect ()
{
    m_registrar->Deregister(m_topic, shared_from_this());
}

void TestController::Consume (SharedPtr<Event> const& a_pEvent)
{
    ++m_countConsumed;

    advcpp::LockGuard lg(m_printMutex);
    std::cout << "Controller received the following event:" << std::endl;
    a_pEvent->Print();
    std::cout << "This controller has received " << m_countConsumed
              << " event(s) by now." << std::endl;
}

} // smart_home

extern "C"
{
    SharedPtr<smart_home::IAgent> MakeAgent (smart_home::AgentInfo::DeviceID const& a_id,
                                             smart_home::AgentInfo::DeviceLocation const& a_location,
                                             smart_home::AgentInfo::AgentLog const& a_log,
                                             smart_home::AgentInfo::AgentConfig const& a_config)
    {
        smart_home::EventTopic topic("test-type", a_location);
        return SharedPtr<smart_home::IAgent>(new smart_home::TestController(a_id, a_location, a_log, a_config, topic));
    }
}