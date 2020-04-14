#include "subscriber_list.hpp"
#include "common_utils.hpp"
#include "i_event_subscriber.hpp"
#include "event.hpp"

namespace smart_home
{

void SubscriberList::Add (SharedPtr<ISubscriber> const& a_newSubscriber)
{
    m_list.push_back(a_newSubscriber);
}

void SubscriberList::Distribute (SharedPtr<Event> const& a_pEvent)
{
    for (std::list<SharedPtr<ISubscriber> >::iterator itr = m_list.begin()
        ; itr != m_list.end()
        ; ++itr)
    {
        (*itr)->Deliver(a_pEvent);
    }
}

} // smart_home