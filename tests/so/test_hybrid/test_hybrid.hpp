#ifndef TEST_HYBRID_HPP
#define TEST_HYBRID_HPP

#include <cstddef> // size_t

#include "common_utils.hpp"
#include "i_agent.hpp"
#include "i_event_consumer.hpp"
#include "i_push_event_bus.hpp"
#include "i_consumer_registrar.hpp"
#include "agent_info.hpp"
#include "event_topic.hpp"

namespace smart_home
{

class TestHybrid : public IAgent, public IEventConsumer, public std::tr1::enable_shared_from_this<TestHybrid>
// TODO: receive only a_config and parse it
{
public:
    TestHybrid (AgentInfo::DeviceID const& a_id, AgentInfo::DeviceLocation const& a_location,
                AgentInfo::AgentLog const& a_log, AgentInfo::AgentConfig const& a_config,
                EventTopic const& a_topic);
    //TestHybrid (TestHybrid const& a_other) = default;
    //~TestHybrid () = default;
    //TestHybrid& operator= (TestHybrid const& a_other) = default;

    virtual void Connect (SharedPtr<IPushEventBus> const& a_pushBus,
                          SharedPtr<IConsumerRegistrar> const& a_registrar);

private:
    virtual void Consume (SharedPtr<Event> const& a_pEvent);

private:
    AgentInfo m_info;
    EventTopic m_topic;
    size_t m_countReturned;
    SharedPtr<IPushEventBus> m_pushBus;
};

} // smart_home

#endif // TEST_HYBRID_HPP