#include "mu_test.h"

#include "common_utils.hpp"
#include "event.hpp"
#include "waitable_bounded_queue.hpp"
#include "test_sensor_agent.hpp"
#include "test_event_hub.hpp"
#include "test_controller_agent.hpp"

using namespace advcpp;
using smart_home::Event;
using test_smart_home::TestSensorAgent;
using test_smart_home::TestEventHub;
using test_smart_home::TestControllerAgent;

UNIT(mvp)
    SharedPtr<EventBus> q(new EventBus(5));
    TestEventHub hub(q);

    TestSensorAgent sensor(q);

    TestControllerAgent controller;
    hub.Subscribe(controller);

// setup is done, lets test behavior
    Event e("fdkdo");
    ASSERT_EQUAL(q.NumOfElems(), 0);
    sensor.PublishEvent(e);
    ASSERT_EQUAL(q.NumOfElems(), 1);
    hub.DistributeEvent();

// lets assert and verify
    eout = controller.GetEvent();
    ASSERT_EQUAL(eout, e);
    ASSERT_EQUAL(q.NumOfElems(), 0);
END_UNIT

TEST_SUITE(mvptest)
    TEST(mvp)
END_SUITE