#include <cstddef> // size_t

#include "test_hybrid.hpp"
#include "common_utils.hpp"
#include "i_agent.hpp"
#include "i_event_consumer.hpp"
#include "i_push_event_bus.hpp"
#include "i_consumer_registrar.hpp"
#include "agent_info.hpp"
#include "event_topic.hpp"

namespace smart_home
{

TestHybrid::TestHybrid (AgentInfo::DeviceID const& a_id, AgentInfo::DeviceLocation const& a_location,
                                AgentInfo::AgentLog const& a_log, AgentInfo::AgentConfig const& a_config,
                                EventTopic const& a_topic)
    : m_info(a_id, "TestHybrid", a_location, a_log, a_config)
    , m_topic(a_topic)
    , m_countReturned(0)
    , m_pushBus()
    , m_registrar()
{ }

void TestHybrid::Connect (SharedPtr<IPushEventBus> const& a_pushBus,
                          SharedPtr<IConsumerRegistrar> const& a_registrar)
{
    m_registrar = a_registrar;
    m_registrar->Register(m_topic, shared_from_this());
}

void TestHybrid::Disconnect ()
{
    m_registrar->Deregister(m_topic, shared_from_this());
}

void TestHybrid::Consume (SharedPtr<Event> const& a_pEvent)
{
    try
    {
        m_pushBus->Push(a_pEvent);
    }
    catch (IPushEventBusShutdownExc const&)
    { }
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
        return SharedPtr<smart_home::IAgent>(new smart_home::TestHybrid(a_id, a_location, a_log, a_config, topic));
    }
}