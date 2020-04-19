#include <stdexcept> // std::exception

struct InvalidEventTypeExc : public std::exception
{
    const char* what () const NOEXCEPTIONS
    {
        return "Event type is not in map";
    }
};

template <typename SafeConsumerList>
void ConsumerMap<SafeConsumerList>::Register (Event::Type const& a_eventType, SharedPtr<IEventConsumer> const& a_newConsumer)
{
    // try insert
    m_map.insert(std::pair<Event::Type, SharedPtr<SafeConsumerList> >(a_eventType, SharedPtr<SafeConsumerList>(new SafeConsumerList())));
    m_map[a_eventType]->Add(a_newConsumer);
}

template <typename SafeConsumerList>
void ConsumerMap<SafeConsumerList>::Deregister (Event::Type const& a_eventType, SharedPtr<IEventConsumer> const& a_consumerToRemove)
{
    typename std::tr1::unordered_map<Event::Type, SharedPtr<SafeConsumerList> >::iterator foundList = m_map.find(a_eventType);
    if (foundList == m_map.end())
    {
        throw InvalidEventTypeExc();
    }

    foundList->second->Remove(a_consumerToRemove);
}

template <typename SafeConsumerList>
SharedPtr<DistributionList> ConsumerMap<SafeConsumerList>::List (Event::Type const& a_eventType) const
{
    typename std::tr1::unordered_map<Event::Type, SharedPtr<SafeConsumerList> >::const_iterator foundList = m_map.find(a_eventType);
    if (foundList == m_map.end())
    {
        throw InvalidEventTypeExc();
    }

    return foundList->second->GetCopy();
}