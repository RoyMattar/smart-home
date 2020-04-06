#ifndef TEST_SENSOR_AGENT_HPP
#define TEST_SENSOR_AGENT_HPP

#include "common_utils.hpp"
#include "iEnqueueableQueue.hpp"
#include "Event.hpp"

namespace testSmartHome
{

class TestSensorAgent
{
public:
    TestSensorAgent (const SharedPtr<SmartHome::iEnqueueableQueue<SharedPtr<SmartHome::Event> > >& a_pEnqableQ);
    //TestSensorAgent (const TestSensorAgent& a_other) = default;
    //~TestSensorAgent () = default;
    //TestSensorAgent& operator= (const TestSensorAgent& a_other) = default;

    void PublishEvent (const SmartHome::Event& a_event);

private:
    SharedPtr<SmartHome::iEnqueueableQueue<SharedPtr<SmartHome::Event> > > m_pEnqableQ;
};

} // testSmartHome

#endif // TEST_SENSOR_AGENT_HPP