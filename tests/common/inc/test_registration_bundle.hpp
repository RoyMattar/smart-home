#ifndef TEST_REGISTRATION_BUNDLE_HPP
#define TEST_REGISTRATION_BUNDLE_HPP

#include <vector>

#include "common_utils.hpp"
#include "consumer_map_tagged.hpp"
#include "event.hpp"
#include "event_topic.hpp"
#include "test_consumer.hpp"
#include "group_tag.hpp"
#include "mutex.hpp"

namespace smart_home
{

class TestRegistrationBundle
{
public:
    TestRegistrationBundle (GroupTag a_numOfTags);

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
    std::vector<SharedPtr<TestConsumer> > subscribers;
    advcpp::Mutex m_consumerMutex;
};

typedef std::vector<SharedPtr<TestConsumer> > DerivedList;
DerivedList MakeDerivedList (SharedPtr<DistributionListTagged> a_list);

} // smart_home

#endif // TEST_REGISTRATION_BUNDLE_HPP