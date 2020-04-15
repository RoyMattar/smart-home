#ifndef SUBSCRIBER_LIST_HPP
#define SUBSCRIBER_LIST_HPP

#include <list>

#include "common_utils.hpp"
#include "i_event_subscriber.hpp"
#include "event.hpp"

namespace smart_home
{

class SubscriberList : private advcpp::Uncopyable
{
public:
    //SubscriberList () = default;
    //~SubscriberList () = default;

    void Add (SharedPtr<ISubscriber> const& a_newSubscriber);
    void Distribute (SharedPtr<Event> const& a_pEvent);

private:
    std::list<SharedPtr<ISubscriber> > m_list;
};

} // smart_home

#endif // SUBSCRIBER_LIST_HPP