#include "mu_test.h"

#include <vector>
#include <cstddef> // size_t 
#include "common_utils.hpp"
#include "event.hpp"
#include "test_consumer.hpp"
#include "consumer_map.hpp"
#include "distribution_list.hpp"

using namespace advcpp;
using namespace smart_home;

// TEST DRAFT
// Subscribers:
// 1. light:f1:r3
// 2. light:f1:r4
// 3. light:f1:*
// 4. light:f2:r5
// 5. light:*:*
// 6. sound:f3:f2
// 7. *:*:*
// List for:
// light:f1:r3 -> Expect: 1, 3, 5, 7
// light:f1:r5 -> Expect: 3, 5, 7
// light:f2:r5 -> Expect: 4, 5, 7
// sound:f3:r2 -> Expect: 6, 7
// fire:f4:r3 -> Expect: 7

class TestDetails
{
public:
    SharedPtr<ConsumerMap<> > map;
    Event::Type lightType;
    Event::Type soundType;
    Event::Type fireType;
    Event::Location f1r3; // sub1 (light)
    Event::Location f1r4; // sub2 (light)
    Event::Location f1rAny; // sub3 (light)
    Event::Location f2r5; // sub4 (light)
    Event::Location fAnyrAny; // sub5 (light)
    Event::Location f3r2; // sub6 (sound)
    Event::Location f1r5; // not sub'd
    Event::Location f4r3; // not sub'd
    // sub7: *:*:*

    TestDetails ()
        : map(new ConsumerMap<>())
        , lightType("light")
        , soundType("sound")
        , fireType("fire")
        , f1r3("1", "3")
        , f1r4("1", "4")
        , f1rAny("1", Event::Location::ANY_ROOM)
        , f2r5("2", "5")
        , fAnyrAny(Event::Location::ANY_FLOOR, Event::Location::ANY_ROOM)
        , f3r2("3", "2")
        , f1r5("1", "5")
        , f4r3("4", "3")
    {
        std::vector<SharedPtr<TestConsumer> > subscribers;
        subscribers.push_back(SharedPtr<TestConsumer>(new TestConsumer(lightType, f1r3)));
        subscribers.push_back(SharedPtr<TestConsumer>(new TestConsumer(lightType, f1r4)));
        subscribers.push_back(SharedPtr<TestConsumer>(new TestConsumer(lightType, f1rAny)));
        subscribers.push_back(SharedPtr<TestConsumer>(new TestConsumer(lightType, f2r5)));
        subscribers.push_back(SharedPtr<TestConsumer>(new TestConsumer(lightType, fAnyrAny)));
        subscribers.push_back(SharedPtr<TestConsumer>(new TestConsumer(soundType, f3r2)));
        subscribers.push_back(SharedPtr<TestConsumer>(new TestConsumer(Event::ANY_TYPE, fAnyrAny)));

        for (std::vector<SharedPtr<TestConsumer> >::size_type i = 0; i < subscribers.size(); ++i)
        {
            subscribers[i]->Subscribe(map);
        }
    }
};

UNIT(T_F_R_reg)
// light:f1:r3 -> 1, 3, 5, 7
    TestDetails det;

    SharedPtr<DistributionList> list = det.map->List(det.lightType, det.f1r3);

    ASSERT_EQUAL(list->size(), 4);

    SharedPtr<TestConsumer> sub1 = std::tr1::static_pointer_cast<TestConsumer>((*list)[0]);
    SharedPtr<TestConsumer> sub2 = std::tr1::static_pointer_cast<TestConsumer>((*list)[1]);
    SharedPtr<TestConsumer> sub3 = std::tr1::static_pointer_cast<TestConsumer>((*list)[2]);
    SharedPtr<TestConsumer> sub4 = std::tr1::static_pointer_cast<TestConsumer>((*list)[3]);

    ASSERT_THAT(sub1->GetType() == det.lightType);
    ASSERT_THAT(sub1->GetLocation() == det.f1r3);

    ASSERT_THAT(sub2->GetType() == det.lightType);
    ASSERT_THAT(sub2->GetLocation() == det.f1rAny);
    
    ASSERT_THAT(sub3->GetType() == det.lightType);
    ASSERT_THAT(sub3->GetLocation() == det.fAnyrAny);
    
    ASSERT_THAT(sub4->GetType() == Event::ANY_TYPE);
    ASSERT_THAT(sub4->GetLocation() == det.fAnyrAny);
END_UNIT

UNIT(T_F_reg_R_not)
// light:f1:r5 -> 3, 5, 7
    TestDetails det;

    SharedPtr<DistributionList> list = det.map->List(det.lightType, det.f1r5);

    ASSERT_EQUAL(list->size(), 3);

    SharedPtr<TestConsumer> sub1 = std::tr1::static_pointer_cast<TestConsumer>((*list)[0]);
    SharedPtr<TestConsumer> sub2 = std::tr1::static_pointer_cast<TestConsumer>((*list)[1]);
    SharedPtr<TestConsumer> sub3 = std::tr1::static_pointer_cast<TestConsumer>((*list)[2]);

    ASSERT_THAT(sub1->GetType() == det.lightType);
    ASSERT_THAT(sub1->GetLocation() == det.f1rAny);
    
    ASSERT_THAT(sub2->GetType() == det.lightType);
    ASSERT_THAT(sub2->GetLocation() == det.fAnyrAny);
    
    ASSERT_THAT(sub3->GetType() == Event::ANY_TYPE);
    ASSERT_THAT(sub3->GetLocation() == det.fAnyrAny);
END_UNIT

UNIT(T_F_reg_R_notAny)
// light:f2:r5 -> 4, 5, 7
    TestDetails det;

    SharedPtr<DistributionList> list = det.map->List(det.lightType, det.f2r5);

    ASSERT_EQUAL(list->size(), 3);

    SharedPtr<TestConsumer> sub1 = std::tr1::static_pointer_cast<TestConsumer>((*list)[0]);
    SharedPtr<TestConsumer> sub2 = std::tr1::static_pointer_cast<TestConsumer>((*list)[1]);
    SharedPtr<TestConsumer> sub3 = std::tr1::static_pointer_cast<TestConsumer>((*list)[2]);

    ASSERT_THAT(sub1->GetType() == det.lightType);
    ASSERT_THAT(sub1->GetLocation() == det.f2r5);
    
    ASSERT_THAT(sub2->GetType() == det.lightType);
    ASSERT_THAT(sub2->GetLocation() == det.fAnyrAny);
    
    ASSERT_THAT(sub3->GetType() == Event::ANY_TYPE);
    ASSERT_THAT(sub3->GetLocation() == det.fAnyrAny);
END_UNIT

UNIT(F_R_reg_T_other)
// sound:f3:r2 -> 6, 7
    TestDetails det;

    SharedPtr<DistributionList> list = det.map->List(det.soundType, det.f3r2);

    ASSERT_EQUAL(list->size(), 2);

    SharedPtr<TestConsumer> sub1 = std::tr1::static_pointer_cast<TestConsumer>((*list)[0]);
    SharedPtr<TestConsumer> sub2 = std::tr1::static_pointer_cast<TestConsumer>((*list)[1]);

    ASSERT_THAT(sub1->GetType() == det.soundType);
    ASSERT_THAT(sub1->GetLocation() == det.f3r2);
    
    ASSERT_THAT(sub2->GetType() == Event::ANY_TYPE);
    ASSERT_THAT(sub2->GetLocation() == det.fAnyrAny);
END_UNIT

UNIT(T_F_R_notReg)
// fire:f4:r3 -> 7
    TestDetails det;

    SharedPtr<DistributionList> list = det.map->List(det.fireType, det.f4r3);

    ASSERT_EQUAL(list->size(), 1);

    SharedPtr<TestConsumer> sub1 = std::tr1::static_pointer_cast<TestConsumer>((*list)[0]);

    ASSERT_THAT(sub1->GetType() == Event::ANY_TYPE);
    ASSERT_THAT(sub1->GetLocation() == det.fAnyrAny);
END_UNIT

TEST_SUITE(listing)
    TEST(T_F_R_reg)
    TEST(T_F_reg_R_not)
    TEST(T_F_reg_R_notAny)
    TEST(F_R_reg_T_other)
    TEST(T_F_R_notReg)
END_SUITE