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
    m_map[a_eventType].Add(a_newConsumer);
}

template <typename SafeConsumerList>
void ConsumerMap<SafeConsumerList>::Deregister (Event::Type const& a_eventType, SharedPtr<IEventConsumer> const& a_consumerToRemove)
{
    typename std::tr1::unordered_map<Event::Type, SafeConsumerList>::iterator foundList = m_map.find(a_eventType);
    if (foundList == m_map.end())
    {
        throw InvalidEventTypeExc();
    }

    foundList->second.Remove(a_consumerToRemove);
}

template <typename SafeConsumerList>
SharedPtr<std::vector<SharedPtr<IEventConsumer> > > ConsumerMap<SafeConsumerList>::List (SharedPtr<Event> const& a_pEvent) const
{
    typename std::tr1::unordered_map<Event::Type, SafeConsumerList>::iterator foundList = m_map.find(a_pEvent->GetType());
    if (foundList == m_map.end())
    {
        throw InvalidEventTypeExc();
    }

    return foundList->second.GetCopy();
}