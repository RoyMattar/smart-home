#include "test_sensor_agent.hpp"

namespace test_smart_home
{

TestSensorAgent::TestSensorAgent (const SharedPtr<smart_home::IPushEventBus>& a_pushBus)
    : m_pushBus(a_pushBus)
{ }

void TestSensorAgent::PublishEvent (const smart_home::Event& a_event)
{
    m_pushBus->Push(SharedPtr<smart_home::Event>(new smart_home::Event(a_event)));
}

} // test_smart_home