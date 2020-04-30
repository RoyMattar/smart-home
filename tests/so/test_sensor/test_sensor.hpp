#ifndef TEST_SENSOR_HPP
#define TEST_SENSOR_HPP

#include "common_utils.hpp"
#include "i_agent.hpp"
#include "i_runnable.hpp"
#include "i_push_event_bus.hpp"
#include "i_consumer_registrar.hpp"
#include "agent_info.hpp"
#include "thread.hpp"

namespace smart_home
{

class TestSensor : public IAgent, public advcpp::IRunnable, public std::tr1::enable_shared_from_this<TestSensor>
// TODO: receive only a_config and parse it
{
public:
    TestSensor (AgentInfo::DeviceID const& a_id, AgentInfo::DeviceLocation const& a_location,
                AgentInfo::AgentLog const& a_log, AgentInfo::AgentConfig const& a_config);
    //TestSensor (TestSensor const& a_other) = default;
    //~TestSensor () = default;
    //TestSensor& operator= (TestSensor const& a_other) = default;

    virtual void Connect (SharedPtr<IPushEventBus> const& a_pushBus,
                          SharedPtr<IConsumerRegistrar> const& a_registrar);
    virtual void Disconnect ();

private:
    virtual void Run ();

private:
    AgentInfo m_info;
    SharedPtr<advcpp::Thread> m_thread;
    SharedPtr<IPushEventBus> m_pushBus;
    bool m_connected;
};

} // smart_home

#endif // TEST_SENSOR_HPP