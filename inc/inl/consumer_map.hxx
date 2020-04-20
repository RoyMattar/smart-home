#include <stdexcept> // std::exception

struct EventNotFoundExc : public std::exception
{
    const char* what () const NOEXCEPTIONS
    {
        return "No corresponding event found in the map";
    }
};

template <typename SafeConsumerList>
void ConsumerMap<SafeConsumerList>::Register (SharedPtr<IEventConsumer> const& a_newConsumer, Event::Type const& a_eventType, Event::Location const& a_eventLocation)
{
    std::string key = makeKey(a_eventType, a_eventLocation);
    // try insert
    m_map.insert(std::pair<std::string, SharedPtr<SafeConsumerList> >(key, SharedPtr<SafeConsumerList>(new SafeConsumerList())));

    m_map[key]->Add(a_newConsumer);
}

template <typename SafeConsumerList>
void ConsumerMap<SafeConsumerList>::Deregister (SharedPtr<IEventConsumer> const& a_consumer, Event::Type const& a_eventType, Event::Location const& a_eventLocation)
{
    std::string key = makeKey(a_eventType, a_eventLocation);

    typename std::tr1::unordered_map<std::string, SharedPtr<SafeConsumerList> >::iterator foundList = m_map.find(key);
    if (foundList == m_map.end())
    {
        throw EventNotFoundExc();
    }

    foundList->second->Remove(a_consumer);
}

template <typename SafeConsumerList>
SharedPtr<DistributionList> ConsumerMap<SafeConsumerList>::List (Event::Type const& a_eventType, Event::Location const& a_eventLocation) const
{
    SharedPtr<DistributionList> specificRoomList = makePartialList(a_eventType, a_eventLocation);

    Event::Location anyRoomLocation(a_eventLocation.GetFloor(), Event::Location::ANY_ROOM);
    SharedPtr<DistributionList> anyRoomList = makePartialList(a_eventType, anyRoomLocation);

    Event::Location anyFloorLocation(Event::Location::ANY_FLOOR, Event::Location::ANY_ROOM);
    SharedPtr<DistributionList> anyFloorList = makePartialList(a_eventType, anyFloorLocation);

    SharedPtr<DistributionList> anyTypeList = makePartialList(Event::ANY_TYPE, anyFloorLocation);

    SharedPtr<DistributionList> fullList(specificRoomList);
    fullList->insert(fullList->end(), anyRoomList->begin(), anyRoomList->end());
    fullList->insert(fullList->end(), anyFloorList()->begin(), anyFloorList->end());
    fullList->insert(fullList->end(), anyTypeList()->begin(), anyTypeList->end());

    return fullList;
}

template <typename SafeConsumerList>
std::string ConsumerMap<SafeConsumerList>::makeKey (Event::Type const& a_eventType, Event::Location const& a_eventLocation)
{
    return a_eventType + ":"
           + a_eventLocation.GetFloor() + ":"
           + a_eventLocation.GetRoom();
}

template <typename SafeConsumerList>
SharedPtr<DistributionList> ConsumerMap<SafeConsumerList>::makePartialList (Event::Type const& a_eventType, Event::Location const& a_eventLocation) const
{
    std::string key = makeKey(a_eventType, a_eventLocation);

    typename std::tr1::unordered_map<std::string, SharedPtr<SafeConsumerList> >::const_iterator foundList = m_map.find(key);
    if (foundList == m_map.end())
    {
        throw EventNotFoundExc();
    }

    return foundList->second->MakeDistribution();
}