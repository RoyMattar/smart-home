#include "mu_test.h"

#include "common_utils.hpp"
#include "Event.hpp"
#include "WaitableBoundedQueue.hpp"
#include "TestSensorAgent.hpp"
#include "TestEventHub.hpp"
#include "TestControllerAgent.hpp"

using namespace advcpp;
using SmartHome::Event;
using testSmartHome::TestSensorAgent;
using testSmartHome::TestEventHub;
using testSmartHome::TestControllerAgent;

UNIT(mvp)
    Event e("TEMP_CHANGE", "06/04/20 06:44", "+5C", "B-1-3");
    SharedPtr<WaitableBoundedQueue<SharedPtr<Event> > > q(new WaitableBoundedQueue<SharedPtr<Event> >(5));

    TestSensorAgent sensor(q);
    TestEventHub hub(q);
    TestControllerAgent controller;

    hub.Subscribe(controller);
    sensor.PublishEvent(e);
    hub.DistributeEvent();

    ASSERT_EQUAL(e.GetType(), controller.GetEvent().GetType());
    ASSERT_EQUAL(e.GetTimestamp(), controller.GetEvent().GetTimestamp());
    ASSERT_EQUAL(e.GetPayload(), controller.GetEvent().GetPayload());
    ASSERT_EQUAL(e.GetLocation(), controller.GetEvent().GetLocation());
END_UNIT

TEST_SUITE(mvptest)
    TEST(mvp)
END_SUITE