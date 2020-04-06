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

// classes
// vlaue types : semi regular, regular
// reference types: polymorfic, not copyable, no ==

// regular class
    bool operator==(A,A);
    !(x==y)
    bool operator!=(A x, A y) { return !(x==y);}
// semi regular class

typedef WaitableBoundedQueue<SharedPtr<Event> > EventBus;

UNIT(mvp)
    SharedPtr<EventBus> q(new EventBus(5));
    TestEventHub hub(q);

    TestSensorAgent sensor(q);

    TestControllerAgent controller;
    hub.Subscribe(controller);

// setup is done, lets test behavior
    Event e("fdkdo");
    ASSERT_EQUAL(q.size(), 0);
    sensor.PublishEvent(e);
    ASSERT_EQUAL(q.size(), 1);
    hub.DistributeEvent();

// lets assert and verify
    eout = controller.GetEvent();
    ASSERT_EQUAL(eout, e);
    ASSERT_EQUAL(q.size(), 0);
    
    ASSERT_EQUAL(e.GetType(), e.GetType());
    ASSERT_EQUAL(e.GetTimestamp(), controller.GetEvent().GetTimestamp());
    ASSERT_EQUAL(e.GetPayload(), controller.GetEvent().GetPayload());
    ASSERT_EQUAL(e.GetLocation(), controller.GetEvent().GetLocation());
END_UNIT

TEST_SUITE(mvptest)
    TEST(mvp)
END_SUITE