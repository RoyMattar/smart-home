#include "test_sensor_agent.hpp"

namespace test_smart_home
{

TestSensorAgent::TestSensorAgent (const SharedPtr<smart_home::IPushEventBus<SharedPtr<smart_home::Event> > >& a_pushBus)
    : m_pushBus(a_pushBus)
{ }

void TestSensorAgent::PublishEvent (const SmartHome::Event& a_event)
{
    m_pushBus->Enqueue(SharedPtr<SmartHome::Event>(new SmartHome::Event(a_event)));
}

} // test_smart_home