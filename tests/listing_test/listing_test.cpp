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

SharedPtr<ConsumerMap<> > g_map(new ConsumerMap<>());
Event::Type lightType("light");
Event::Type soundType("sound");
Event::Location f1r3("1", "3");
Event::Location f1r4("1", "4");
Event::Location f1rAny("1", Event::Location::ANY_ROOM);
Event::Location f2r5("2", "5");
Event::Location fAnyrAny(Event::Location::ANY_FLOOR, Event::Location::ANY_ROOM);
Event::Location f3r2("3", "2");

void makeSubscribers ()
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
        subscribers[i]->Subscribe(g_map);
    }
}

UNIT(T_F_R_reg)
// light:f1:r3 -> 1, 3, 5, 7
    makeSubscribers();

    SharedPtr<DistributionList> list = g_map->List(lightType, f1r3);

    ASSERT_EQUAL(list->size(), 4);

    SharedPtr<TestConsumer> sub1 = std::tr1::static_pointer_cast<TestConsumer>((*list)[0]);
    SharedPtr<TestConsumer> sub2 = std::tr1::static_pointer_cast<TestConsumer>((*list)[1]);
    SharedPtr<TestConsumer> sub3 = std::tr1::static_pointer_cast<TestConsumer>((*list)[2]);
    SharedPtr<TestConsumer> sub4 = std::tr1::static_pointer_cast<TestConsumer>((*list)[3]);

    ASSERT_THAT(sub1->GetType() == lightType);
    ASSERT_THAT(sub1->GetLocation() == f1r3);

    ASSERT_THAT(sub1->GetType() == lightType);
    ASSERT_THAT(sub1->GetLocation() == f1rAny);
    
    ASSERT_THAT(sub1->GetType() == lightType);
    ASSERT_THAT(sub1->GetLocation() == fAnyrAny);
    
    ASSERT_THAT(sub1->GetType() == Event::ANY_TYPE);
    ASSERT_THAT(sub1->GetLocation() == fAnyrAny);
END_UNIT

UNIT(T_F_reg_R_not)
// light:f1:r5 -> 3, 5, 7

END_UNIT

UNIT(T_F_reg_R_notAny)
// light:f2:r5 -> 4, 5, 7

END_UNIT

UNIT(F_R_reg_T_other)
// sound:f3:r2 -> 6, 7

END_UNIT

UNIT(T_F_R_notReg)
// fire:f4:r3 -> 7

END_UNIT

TEST_SUITE(listing)
    TEST(T_F_R_reg)
    // TEST(T_F_reg_R_not)
    // TEST(T_F_reg_R_notAny)
    // TEST(F_R_reg_T_other)
    // TEST(T_F_R_notReg)
END_SUITE