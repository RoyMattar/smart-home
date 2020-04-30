#include <unistd.h> // sleep()

#include "test_sensor.hpp"
#include "common_utils.hpp"
#include "i_push_event_bus.hpp"
#include "i_consumer_registrar.hpp"
#include "agent_info.hpp"
#include "thread.hpp"
#include "event.hpp"

namespace smart_home
{

TestSensor::TestSensor (AgentInfo::DeviceID const& a_id, AgentInfo::DeviceLocation const& a_location,
                        AgentInfo::AgentLog const& a_log, AgentInfo::AgentConfig const& a_config)
    : m_info(a_id, "TestSensor", a_location, a_log, a_config)
    , m_thread()
    , m_pushBus()
    , m_connected(false)
{ }

void TestSensor::Connect (SharedPtr<IPushEventBus> const& a_pushBus,
                          SharedPtr<IConsumerRegistrar> const& a_registrar)
{
    m_pushBus = a_pushBus;
    m_connected = true;
    m_thread = SharedPtr<advcpp::Thread>(new advcpp::Thread(shared_from_this()));
}

void TestSensor::Disconnect ()
{
    m_connected = false;
    m_thread->Join();
}

void TestSensor::Run ()
{
    try
    {
        while (m_connected)
        {
            Event e("test-type", "now", "test-payload", m_info.GetLocation());
            SharedPtr<Event> pe(new Event(e));
            m_pushBus->Push(pe);
            usleep(MILLI_TO_MICRO(500));
        }
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
        return SharedPtr<smart_home::IAgent>(new smart_home::TestSensor(a_id, a_location, a_log, a_config));
    }
}