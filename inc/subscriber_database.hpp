#ifndef SUBSCRIBER_DATABASE_HPP
#define SUBSCRIBER_DATABASE_HPP

#include <tr1/unordered_map>

#include "common_utils.hpp"
#include "i_registrar.hpp"
#include "i_distributor.hpp"
#include "i_subscriber.hpp"
#include "event.hpp"
#include "subscriber_list.hpp"

namespace smart_home
{

class SubscriberDatabase : private advcpp::Uncopyable, public IRegistrar, public IDistributor
{
public:
    //SubscriberDatabase () = default;
    //~SubscriberDatabase () = default;

    virtual void Register (SharedPtr<ISubscriber> const& a_newSubscriber, Event::Type a_eventType);
    virtual void Distribute (SharedPtr<Event> const& a_pEvent);

private:
    std::tr1::unordered_map<Event::Type, SubscriberList> m_database;
};

} // smart_home

#endif // SUBSCRIBER_DATABASE_HPP