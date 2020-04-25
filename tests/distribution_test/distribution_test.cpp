#include "mu_test.h"

#include "common_utils.hpp"
#include "test_registration_bundle.hpp"
#include "test_distribution_bundle.hpp"
#include "distribution_list_tagged.hpp"
#include "event.hpp"
#include "event_topic.hpp"

using namespace smart_home;

// light:f1:r3 -> Expect: 1, 3, 5, 7
// light:f1:r5 -> Expect: 3, 5, 7
// light:f2:r5 -> Expect: 4, 5, 7
// sound:f3:r2 -> Expect: 6, 7
// fire:f4:r3 -> Expect: 7

const GroupTag numOfTags = 4;
const size_t channelCapacity = 10;

UNIT(event_light_F1_R3)
// light:f1:r3 -> Expect: 1, 3, 5, 7
    TestRegistrationBundle regBundle(numOfTags);
    TestDistributionBundle distBundle(numOfTags, channelCapacity);
    SharedPtr<Event> event(new Event("light", "0:0:1", "payload1", Event::Location("1", "3")));

    SharedPtr<DistributionListTagged> list = regBundle.map->List(EventTopic(*event));
    distBundle.distributor->Distribute(event, list);
    distBundle.factory->StopAll();

    ASSERT_EQUAL(regBundle.subscribers[0]->CountDelivered(), 1);
    ASSERT_EQUAL(regBundle.subscribers[1]->CountDelivered(), 0);
    ASSERT_EQUAL(regBundle.subscribers[2]->CountDelivered(), 1);
    ASSERT_EQUAL(regBundle.subscribers[3]->CountDelivered(), 0);
    ASSERT_EQUAL(regBundle.subscribers[4]->CountDelivered(), 1);
    ASSERT_EQUAL(regBundle.subscribers[5]->CountDelivered(), 0);
    ASSERT_EQUAL(regBundle.subscribers[6]->CountDelivered(), 1);
END_UNIT

UNIT(event_light_F1_R5)
// light:f1:r5 -> Expect: 3, 5, 7
    TestRegistrationBundle regBundle(numOfTags);
    TestDistributionBundle distBundle(numOfTags, channelCapacity);
    SharedPtr<Event> event(new Event("light", "0:0:2", "payload2", Event::Location("1", "5")));

    SharedPtr<DistributionListTagged> list = regBundle.map->List(EventTopic(*event));
    distBundle.distributor->Distribute(event, list);
    distBundle.factory->StopAll();

    ASSERT_EQUAL(regBundle.subscribers[0]->CountDelivered(), 0);
    ASSERT_EQUAL(regBundle.subscribers[1]->CountDelivered(), 0);
    ASSERT_EQUAL(regBundle.subscribers[2]->CountDelivered(), 1);
    ASSERT_EQUAL(regBundle.subscribers[3]->CountDelivered(), 0);
    ASSERT_EQUAL(regBundle.subscribers[4]->CountDelivered(), 1);
    ASSERT_EQUAL(regBundle.subscribers[5]->CountDelivered(), 0);
    ASSERT_EQUAL(regBundle.subscribers[6]->CountDelivered(), 1);
END_UNIT

UNIT(event_light_F2_R5)
// light:f2:r5 -> Expect: 4, 5, 7
    TestRegistrationBundle regBundle(numOfTags);
    TestDistributionBundle distBundle(numOfTags, channelCapacity);
    SharedPtr<Event> event(new Event("light", "0:0:3", "payload3", Event::Location("2", "5")));

    SharedPtr<DistributionListTagged> list = regBundle.map->List(EventTopic(*event));
    distBundle.distributor->Distribute(event, list);
    distBundle.factory->StopAll();

    ASSERT_EQUAL(regBundle.subscribers[0]->CountDelivered(), 0);
    ASSERT_EQUAL(regBundle.subscribers[1]->CountDelivered(), 0);
    ASSERT_EQUAL(regBundle.subscribers[2]->CountDelivered(), 0);
    ASSERT_EQUAL(regBundle.subscribers[3]->CountDelivered(), 1);
    ASSERT_EQUAL(regBundle.subscribers[4]->CountDelivered(), 1);
    ASSERT_EQUAL(regBundle.subscribers[5]->CountDelivered(), 0);
    ASSERT_EQUAL(regBundle.subscribers[6]->CountDelivered(), 1);
END_UNIT

UNIT(event_sound_F3_R2)
// sound:f3:r2 -> Expect: 6, 7
    TestRegistrationBundle regBundle(numOfTags);
    TestDistributionBundle distBundle(numOfTags, channelCapacity);
    SharedPtr<Event> event(new Event("sound", "0:0:4", "payload4", Event::Location("3", "2")));

    SharedPtr<DistributionListTagged> list = regBundle.map->List(EventTopic(*event));
    distBundle.distributor->Distribute(event, list);
    distBundle.factory->StopAll();

    ASSERT_EQUAL(regBundle.subscribers[0]->CountDelivered(), 0);
    ASSERT_EQUAL(regBundle.subscribers[1]->CountDelivered(), 0);
    ASSERT_EQUAL(regBundle.subscribers[2]->CountDelivered(), 0);
    ASSERT_EQUAL(regBundle.subscribers[3]->CountDelivered(), 0);
    ASSERT_EQUAL(regBundle.subscribers[4]->CountDelivered(), 0);
    ASSERT_EQUAL(regBundle.subscribers[5]->CountDelivered(), 1);
    ASSERT_EQUAL(regBundle.subscribers[6]->CountDelivered(), 1);
END_UNIT

UNIT(event_fire_F4_R3)
// fire:f4:r3 -> Expect: 7
    TestRegistrationBundle regBundle(numOfTags);
    TestDistributionBundle distBundle(numOfTags, channelCapacity);
    SharedPtr<Event> event(new Event("fire", "0:0:5", "payload5", Event::Location("4", "3")));

    SharedPtr<DistributionListTagged> list = regBundle.map->List(EventTopic(*event));
    distBundle.distributor->Distribute(event, list);
    distBundle.factory->StopAll();

    ASSERT_EQUAL(regBundle.subscribers[0]->CountDelivered(), 0);
    ASSERT_EQUAL(regBundle.subscribers[1]->CountDelivered(), 0);
    ASSERT_EQUAL(regBundle.subscribers[2]->CountDelivered(), 0);
    ASSERT_EQUAL(regBundle.subscribers[3]->CountDelivered(), 0);
    ASSERT_EQUAL(regBundle.subscribers[4]->CountDelivered(), 0);
    ASSERT_EQUAL(regBundle.subscribers[5]->CountDelivered(), 0);
    ASSERT_EQUAL(regBundle.subscribers[6]->CountDelivered(), 1);
END_UNIT

TEST_SUITE(distribution)
    TEST(event_light_F1_R3)
    TEST(event_light_F1_R5)
    TEST(event_light_F2_R5)
    TEST(event_sound_F3_R2)
    TEST(event_fire_F4_R3)
END_SUITE