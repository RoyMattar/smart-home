#include "mu_test.h"

#include <iostream>
#include <vector>
#include <cstddef> // size_t

#include "common_utils.hpp"
#include "event.hpp"
#include "test_consumer.hpp"
#include "test_registration_bundle.hpp"
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
    TestRegistrationBundle bundle(1, 4);

    SharedPtr<DistributionListTagged> list = bundle.map->List(bundle.light_F1_R3);
    DerivedList subs = MakeDerivedList(list);
    ConsumeTestEvent(subs);

    ASSERT_EQUAL(list->size(), 4);

    ASSERT_THAT(subs[0]->GetTopic() == bundle.light_F1_R3);
    ASSERT_THAT(subs[1]->GetTopic() == bundle.light_F1_Rany);
    ASSERT_THAT(subs[2]->GetTopic() == bundle.light_Fany_Rany);
    ASSERT_THAT(subs[3]->GetTopic() == bundle.Tany_Fany_Rany);
END_UNIT

UNIT(T_F_reg_R_not)
// light:f1:r5 -> 3, 5, 7
    TestRegistrationBundle bundle(1, 4);
    
    SharedPtr<DistributionListTagged> list = bundle.map->List(bundle.light_F1_R5);
    DerivedList subs = MakeDerivedList(list);
    ConsumeTestEvent(subs);

    ASSERT_EQUAL(list->size(), 3);

    ASSERT_THAT(subs[0]->GetTopic() == bundle.light_F1_Rany);
    ASSERT_THAT(subs[1]->GetTopic() == bundle.light_Fany_Rany);
    ASSERT_THAT(subs[2]->GetTopic() == bundle.Tany_Fany_Rany);
END_UNIT

UNIT(T_F_reg_R_notAny)
// light:f2:r5 -> 4, 5, 7
    TestRegistrationBundle bundle(1, 4);
    
    SharedPtr<DistributionListTagged> list = bundle.map->List(bundle.light_F2_R5);
    DerivedList subs = MakeDerivedList(list);
    ConsumeTestEvent(subs);

    ASSERT_EQUAL(list->size(), 3);

    ASSERT_THAT(subs[0]->GetTopic() == bundle.light_F2_R5);
    ASSERT_THAT(subs[1]->GetTopic() == bundle.light_Fany_Rany);
    ASSERT_THAT(subs[2]->GetTopic() == bundle.Tany_Fany_Rany);
END_UNIT

UNIT(F_R_reg_T_other)
// sound:f3:r2 -> 6, 7
    TestRegistrationBundle bundle(1, 4);
    
    SharedPtr<DistributionListTagged> list = bundle.map->List(bundle.sound_F3_R2);
    DerivedList subs = MakeDerivedList(list);
    ConsumeTestEvent(subs);

    ASSERT_EQUAL(list->size(), 2);

    ASSERT_THAT(subs[0]->GetTopic() == bundle.sound_F3_R2);
    ASSERT_THAT(subs[1]->GetTopic() == bundle.Tany_Fany_Rany);
END_UNIT

UNIT(T_F_R_notReg)
// fire:f4:r3 -> 7
    TestRegistrationBundle bundle(1, 4);
    
    SharedPtr<DistributionListTagged> list = bundle.map->List(bundle.fire_F4_R3);
    DerivedList subs = MakeDerivedList(list);
    ConsumeTestEvent(subs);

    ASSERT_EQUAL(list->size(), 1);

    ASSERT_THAT(subs[0]->GetTopic() == bundle.Tany_Fany_Rany);
END_UNIT

TEST_SUITE(listing)
    TEST(T_F_R_reg)
    TEST(T_F_reg_R_not)
    TEST(T_F_reg_R_notAny)
    TEST(F_R_reg_T_other)
    TEST(T_F_R_notReg)
END_SUITE