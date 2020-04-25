#include <vector>

#include "test_registration_bundle.hpp"
#include "common_utils.hpp"
#include "consumer_map_tagged.hpp"
#include "cyclic_tag.hpp"
#include "event.hpp"
#include "event_topic.hpp"
#include "test_consumer.hpp"
#include "mutex.hpp"

namespace smart_home
{

TestRegistrationBundle::TestRegistrationBundle (CyclicTag::TagType a_numOfTags)
    : map(new ConsumerMapTagged<>(CyclicTag(a_numOfTags)))
    , light_F1_R3("light", Event::Location("1", "3"))
    , light_F1_R4("light", Event::Location("1", "4"))
    , light_F1_Rany("light", Event::Location("1", EventTopic::ANY_ROOM))
    , light_F2_R5("light", Event::Location("2", "5"))
    , light_Fany_Rany("light", EventTopic::ANY_LOCATION)
    , sound_F3_R2("sound", Event::Location("3", "2"))
    , Tany_Fany_Rany(EventTopic::ANY_TYPE, EventTopic::ANY_LOCATION)
    , light_F1_R5("light", Event::Location("1", "5"))
    , fire_F4_R3("fire", Event::Location("4", "3"))
    , subscribers()
    , m_consumerMutex()
{
    subscribers.push_back(SharedPtr<TestConsumer>(new TestConsumer(light_F1_R3, m_consumerMutex)));
    subscribers.push_back(SharedPtr<TestConsumer>(new TestConsumer(light_F1_R4, m_consumerMutex)));
    subscribers.push_back(SharedPtr<TestConsumer>(new TestConsumer(light_F1_Rany, m_consumerMutex)));
    subscribers.push_back(SharedPtr<TestConsumer>(new TestConsumer(light_F2_R5, m_consumerMutex)));
    subscribers.push_back(SharedPtr<TestConsumer>(new TestConsumer(light_Fany_Rany, m_consumerMutex)));
    subscribers.push_back(SharedPtr<TestConsumer>(new TestConsumer(sound_F3_R2, m_consumerMutex)));
    subscribers.push_back(SharedPtr<TestConsumer>(new TestConsumer(Tany_Fany_Rany, m_consumerMutex)));

    for (std::vector<SharedPtr<TestConsumer> >::size_type i = 0; i < subscribers.size(); ++i)
    {
        subscribers[i]->Subscribe(map);
    }
}

DerivedList MakeDerivedList (SharedPtr<DistributionListTagged> a_list)
{
    DerivedList subs;
    for (DerivedList::size_type i = 0; i < a_list->size(); ++i)
    {
        subs.push_back(std::tr1::static_pointer_cast<TestConsumer>((*a_list)[i].second));
    }
    return subs;
}

} // smart_home