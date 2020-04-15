#include <tr1/unordered_map>
#include <vector>

#include "common_utils.hpp"
#include "consumer_map.hpp"
#include "i_event_consumer.hpp"
#include "event.hpp"
#include "consumer_list_mt.hpp"

namespace smart_home
{

template <typename SafeConsumerList>
void ConsumerMap<SafeConsumerList>::Register (Event::Type a_eventType, SharedPtr<IEventConsumer> const& a_newConsumer)
{
    m_map[a_eventType].Add(a_eventConsumer);
}

template <typename SafeConsumerList>
void ConsumerMap<SafeConsumerList>::Deregister (Event::Type a_eventType, SharedPtr<IEventConsumer> const& a_oldConsumer)
{
    m_map[a_eventType].Remove(a_eventConsumer);
}

template <typename SafeConsumerList>
SharedPtr<std::vector<SharedPtr<IEventConsumer> > > ConsumerMap<SafeConsumerList>::List (SharedPtr<Event> const& a_pEvent) const
{
    return m_map[a_pEvent->GetType()].GetCopy();
}

} // smart_home