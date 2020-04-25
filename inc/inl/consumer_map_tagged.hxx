#include <stdexcept> // std::exception, std::out_of_range
#include <string> // std::tr1::hash<std::string>
#include <utility> // std::pair

// struct EventTopicNotFoundExc : public std::exception
// {
//     const char* what () const NOEXCEPTIONS
//     {
//         return "Event topic not found in map";
//     }
// };

struct EventTopicHasher
{
    size_t operator() (EventTopic const& a_eventTopic) const
    {
        std::tr1::hash<std::string> stringHasher;
        return stringHasher("t-" + a_eventTopic.GetType() + ":"
                            + "f-" + a_eventTopic.GetFloor() + ":"
                            + "r-" + a_eventTopic.GetRoom());
    }
};

template <typename SafeTaggedList>
ConsumerMapTagged<SafeTaggedList>::ConsumerMapTagged (CyclicTag const& a_cyclicTag)
    : m_tagMap()
    , m_listMap()
    , m_cyclicTag(a_cyclicTag)
{ }

template <typename SafeTaggedList>
bool ConsumerMapTagged<SafeTaggedList>::Register (EventTopic const& a_eventTopic, SharedPtr<IEventConsumer> const& a_newConsumer)
{
    bool hasConsumerNewTag = tryInsertNewTag(a_newConsumer);
    if (hasConsumerNewTag)
    {
        ++m_cyclicTag;
    }
    
    tryInsertNewTopic(a_eventTopic);

    return tryAddNewConsumer(a_eventTopic, a_newConsumer);
}

template <typename SafeTaggedList>
bool ConsumerMapTagged<SafeTaggedList>::Deregister (EventTopic const& a_eventTopic, SharedPtr<IEventConsumer> const& a_consumer)
{
    // get tag for a_consumer
    typename TagMap::const_iterator tagPairItr = m_tagMap.find(a_consumer.get());
    if (tagPairItr == m_tagMap.end()) { return false; }
    GroupTag groupTag = tagPairItr->second;

    // get list for a_eventTopic
    typename ListMap::iterator listPairItr = m_listMap.find(a_eventTopic);
    if (listPairItr == m_listMap.end()) { throw std::out_of_range("Event topic not found"); }
    SharedPtr<SafeTaggedList> pConsumerList = listPairItr->second;

    return pConsumerList->Remove(TaggedConsumer(groupTag, a_consumer));
}

template <typename SafeTaggedList>
SharedPtr<DistributionListTagged> ConsumerMapTagged<SafeTaggedList>::List (EventTopic const& a_eventTopic) const
{
    SharedPtr<DistributionListTagged> specificRoomList = listSpecificRoom(a_eventTopic);
    SharedPtr<DistributionListTagged> anyRoomList = listAnyRoom(a_eventTopic.GetType(), a_eventTopic.GetFloor());
    SharedPtr<DistributionListTagged> anyFloorList = listAnyFloor(a_eventTopic.GetType());
    SharedPtr<DistributionListTagged> anyTypeList = listAnyType();

    return concatLists(specificRoomList, anyRoomList, anyFloorList, anyTypeList);
}

template <typename SafeTaggedList>
bool ConsumerMapTagged<SafeTaggedList>::tryInsertNewTag (SharedPtr<IEventConsumer> const& a_newConsumer)
{
    IEventConsumer* consumerRawPtr = a_newConsumer.get();
    GroupTag groupTag = m_cyclicTag.GetCurrent();

    std::pair<typename TagMap::iterator, bool> insertTagResult
        = m_tagMap.insert(std::make_pair(consumerRawPtr, groupTag));
    return insertTagResult.second;
}

template <typename SafeTaggedList>
bool ConsumerMapTagged<SafeTaggedList>::tryInsertNewTopic (EventTopic const& a_eventTopic)
{
    std::pair<typename ListMap::iterator, bool> insertListResult
        = m_listMap.insert(std::make_pair(a_eventTopic, SharedPtr<SafeTaggedList>(new SafeTaggedList())));
    return insertListResult.second;
}

template <typename SafeTaggedList>
bool ConsumerMapTagged<SafeTaggedList>::tryAddNewConsumer (EventTopic const& a_eventTopic, SharedPtr<IEventConsumer> const& a_newConsumer)
{
    IEventConsumer* consumerRawPtr = a_newConsumer.get();
    return m_listMap[a_eventTopic]->Add(TaggedConsumer(m_tagMap[consumerRawPtr], a_newConsumer));
}

template <typename SafeTaggedList>
SharedPtr<DistributionListTagged> ConsumerMapTagged<SafeTaggedList>::listCombination (EventTopic const& a_eventTopic) const
{
    typename ListMap::const_iterator listPairItr = m_listMap.find(a_eventTopic);
    if (listPairItr == m_listMap.end())
    {
        return SharedPtr<DistributionListTagged>(new DistributionListTagged());
    }

    return listPairItr->second->MakeDistribution();
}

template <typename SafeTaggedList>
SharedPtr<DistributionListTagged>
        ConsumerMapTagged<SafeTaggedList>::listSpecificRoom
                (EventTopic const& a_eventTopic) const
{
    return listCombination(a_eventTopic);
}

template <typename SafeTaggedList>
SharedPtr<DistributionListTagged>
        ConsumerMapTagged<SafeTaggedList>::listAnyRoom
                (Event::Type const& a_eventType, Event::Location::Floor const& a_eventFloor) const
{
    return listCombination(EventTopic(a_eventType, Event::Location(a_eventFloor, EventTopic::ANY_ROOM)));
}

template <typename SafeTaggedList>
SharedPtr<DistributionListTagged>
        ConsumerMapTagged<SafeTaggedList>::listAnyFloor
                (Event::Type const& a_eventType) const
{
    return listCombination(EventTopic(a_eventType, EventTopic::ANY_LOCATION));
}

template <typename SafeTaggedList>
SharedPtr<DistributionListTagged>
        ConsumerMapTagged<SafeTaggedList>::listAnyType
                () const
{
    return listCombination(EventTopic(EventTopic::ANY_TYPE, EventTopic::ANY_LOCATION));
}

template <typename SafeTaggedList>
SharedPtr<DistributionListTagged>
        ConsumerMapTagged<SafeTaggedList>::concatLists
                (SharedPtr<DistributionListTagged> a_specificRoomList,
                SharedPtr<DistributionListTagged> a_anyRoomList,
                SharedPtr<DistributionListTagged> a_anyFloorList,
                SharedPtr<DistributionListTagged> a_anyTypeList) const
{
    SharedPtr<DistributionListTagged> fullList(a_specificRoomList);
    fullList->insert(fullList->end(), a_anyRoomList->begin(), a_anyRoomList->end());
    fullList->insert(fullList->end(), a_anyFloorList->begin(), a_anyFloorList->end());
    fullList->insert(fullList->end(), a_anyTypeList->begin(), a_anyTypeList->end());

    return fullList;
}