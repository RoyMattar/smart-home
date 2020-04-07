#include "subscriber_database.hpp"
#include "common_utils.hpp"
#include "i_subscriber.hpp"
#include "event.hpp"

namespace smart_home
{

void SubscriberDatabase::Register (SharedPtr<ISubscriber> const& a_newSubscriber, Event::Type a_eventType)
{
    m_database[a_eventType].Add(a_newSubscriber);
}

void SubscriberDatabase::Distribute (SharedPtr<Event> const& a_pEvent)
{
    m_database[a_pEvent->GetType()].Distribute(a_pEvent);
}

} // smart_home