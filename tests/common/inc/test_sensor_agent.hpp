#ifndef TEST_SENSOR_AGENT_HPP
#define TEST_SENSOR_AGENT_HPP

#include "common_utils.hpp"
#include "i_push_event_bus.hpp"
#include "event.hpp"

namespace test_smart_home
{

class TestSensorAgent
{
public:
    TestSensorAgent (const SharedPtr<smart_home::IPushEventBus<SharedPtr<smart_home::Event> > >& a_pushBus);
    //TestSensorAgent (const TestSensorAgent& a_other) = default;
    //~TestSensorAgent () = default;
    //TestSensorAgent& operator= (const TestSensorAgent& a_other) = default;

    void PublishEvent (const smart_home::Event& a_event);

private:
    SharedPtr<smart_home::IPushEventBus<SharedPtr<smart_home::Event> > > m_pushBus;
};

} // test_smart_home

#endif // TEST_SENSOR_AGENT_HPP