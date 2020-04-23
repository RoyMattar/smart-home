#include "mu_test.h"

#include <iostream>
#include <vector>
#include <cstddef> // size_t

#include "common_utils.hpp"
#include "event.hpp"
#include "event_topic.hpp"
#include "test_consumer.hpp"
#include "cyclic_tag.hpp"
#include "consumer_map_tagged.hpp"
#include "distribution_list_tagged.hpp"

using namespace advcpp;
using namespace smart_home;

// TEST DRAFT
// Subscribers:
// 1. light:f1:r3
// 2. light:f1:r4
// 3. light:f1:*
// 4. light:f2:r5
// 5. light:*:*
// 6. sound:f3:r2
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
    SharedPtr<ConsumerMapTagged<> > map;
    EventTopic light_F1_R3;     //sub1
    EventTopic light_F1_R4;     //sub2
    EventTopic light_F1_Rany;   //sub3
    EventTopic light_F2_R5;     //sub4
    EventTopic light_Fany_Rany; //sub5
    EventTopic sound_F3_R2;     //sub6
    EventTopic Tany_Fany_Rany;  //sub7
    EventTopic light_F1_R5;     //not a sub
    EventTopic fire_F4_R3;      //not a sub

    TestDetails ()
        : map(new ConsumerMapTagged<>(1, 4))
        , light_F1_R3("light", Event::Location("1", "3"))
        , light_F1_R4("light", Event::Location("1", "4"))
        , light_F1_Rany("light", Event::Location("1", EventTopic::ANY_ROOM))
        , light_F2_R5("light", Event::Location("2", "5"))
        , light_Fany_Rany("light", EventTopic::ANY_LOCATION)
        , sound_F3_R2("sound", Event::Location("3", "2"))
        , Tany_Fany_Rany(EventTopic::ANY_TYPE, EventTopic::ANY_LOCATION)
        , light_F1_R5("light", Event::Location("1", "5"))
        , fire_F4_R3("fire", Event::Location("4", "3"))
    {
        std::vector<SharedPtr<TestConsumer> > subscribers;
        subscribers.push_back(SharedPtr<TestConsumer>(new TestConsumer(light_F1_R3)));
        subscribers.push_back(SharedPtr<TestConsumer>(new TestConsumer(light_F1_R4)));
        subscribers.push_back(SharedPtr<TestConsumer>(new TestConsumer(light_F1_Rany)));
        subscribers.push_back(SharedPtr<TestConsumer>(new TestConsumer(light_F2_R5)));
        subscribers.push_back(SharedPtr<TestConsumer>(new TestConsumer(light_Fany_Rany)));
        subscribers.push_back(SharedPtr<TestConsumer>(new TestConsumer(sound_F3_R2)));
        subscribers.push_back(SharedPtr<TestConsumer>(new TestConsumer(Tany_Fany_Rany)));

        for (std::vector<SharedPtr<TestConsumer> >::size_type i = 0; i < subscribers.size(); ++i)
        {
            subscribers[i]->Subscribe(map);
        }
    }
};

typedef std::vector<SharedPtr<TestConsumer> > DerivedList;

DerivedList MakeDerived (SharedPtr<DistributionListTagged> a_list)
{
    DerivedList subs;
    for (DerivedList::size_type i = 0; i < a_list->size(); ++i)
    {
        subs.push_back(std::tr1::static_pointer_cast<TestConsumer>((*a_list)[i].second));
    }
    return subs;
}

void ConsumeTestEvent (DerivedList const& a_derivedList)
{
    for (DerivedList::size_type i = 0; i < a_derivedList.size(); ++i)
    {
        a_derivedList[i]->Consume(SharedPtr<Event>(new Event("test", "test", "test", Event::Location("test", "test"))));
        std::cout << std::endl;
    }
}

UNIT(T_F_R_reg)
// light:f1:r3 -> 1, 3, 5, 7
    TestDetails det;

    SharedPtr<DistributionListTagged> list = det.map->List(det.light_F1_R3);
    DerivedList subs = MakeDerived(list);
    ConsumeTestEvent(subs);

    ASSERT_EQUAL(list->size(), 4);

    ASSERT_THAT(subs[0]->GetTopic() == det.light_F1_R3);
    ASSERT_THAT(subs[1]->GetTopic() == det.light_F1_Rany);
    ASSERT_THAT(subs[2]->GetTopic() == det.light_Fany_Rany);
    ASSERT_THAT(subs[3]->GetTopic() == det.Tany_Fany_Rany);
END_UNIT

UNIT(T_F_reg_R_not)
// light:f1:r5 -> 3, 5, 7
    TestDetails det;
    
    SharedPtr<DistributionListTagged> list = det.map->List(det.light_F1_R5);
    DerivedList subs = MakeDerived(list);
    ConsumeTestEvent(subs);

    ASSERT_EQUAL(list->size(), 3);

    ASSERT_THAT(subs[0]->GetTopic() == det.light_F1_Rany);
    ASSERT_THAT(subs[1]->GetTopic() == det.light_Fany_Rany);
    ASSERT_THAT(subs[2]->GetTopic() == det.Tany_Fany_Rany);
END_UNIT

UNIT(T_F_reg_R_notAny)
// light:f2:r5 -> 4, 5, 7
    TestDetails det;
    
    SharedPtr<DistributionListTagged> list = det.map->List(det.light_F2_R5);
    DerivedList subs = MakeDerived(list);
    ConsumeTestEvent(subs);

    ASSERT_EQUAL(list->size(), 3);

    ASSERT_THAT(subs[0]->GetTopic() == det.light_F2_R5);
    ASSERT_THAT(subs[1]->GetTopic() == det.light_Fany_Rany);
    ASSERT_THAT(subs[2]->GetTopic() == det.Tany_Fany_Rany);
END_UNIT

UNIT(F_R_reg_T_other)
// sound:f3:r2 -> 6, 7
    TestDetails det;
    
    SharedPtr<DistributionListTagged> list = det.map->List(det.sound_F3_R2);
    DerivedList subs = MakeDerived(list);
    ConsumeTestEvent(subs);

    ASSERT_EQUAL(list->size(), 2);

    ASSERT_THAT(subs[0]->GetTopic() == det.sound_F3_R2);
    ASSERT_THAT(subs[1]->GetTopic() == det.Tany_Fany_Rany);
END_UNIT

UNIT(T_F_R_notReg)
// fire:f4:r3 -> 7
    TestDetails det;
    
    SharedPtr<DistributionListTagged> list = det.map->List(det.fire_F4_R3);
    DerivedList subs = MakeDerived(list);
    ConsumeTestEvent(subs);

    ASSERT_EQUAL(list->size(), 1);

    ASSERT_THAT(subs[0]->GetTopic() == det.Tany_Fany_Rany);
END_UNIT

TEST_SUITE(listing)
    TEST(T_F_R_reg)
    TEST(T_F_reg_R_not)
    TEST(T_F_reg_R_notAny)
    TEST(F_R_reg_T_other)
    TEST(T_F_R_notReg)
END_SUITE