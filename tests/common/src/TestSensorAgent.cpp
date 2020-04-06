#include "TestSensorAgent.hpp"

namespace testSmartHome
{

TestSensorAgent::TestSensorAgent (const SharedPtr<SmartHome::iEnqueueableQueue<SharedPtr<SmartHome::Event> > >& a_pEnqableQ)
    : m_pEnqableQ(a_pEnqableQ)
{ }

void TestSensorAgent::PublishEvent (const SmartHome::Event& a_event)
{
    m_pEnqableQ->Enqueue(SharedPtr<SmartHome::Event>(new SmartHome::Event(a_event)));
}

} // testSmartHome