#ifndef EVENT_MIDDLEWARE_HPP
#define EVENT_MIDDLEWARE_HPP

#include <vector>

#include "i_runnable.hpp"
#include "common_utils.hpp"
#include "event.hpp"
#include "i_pull_event_bus.hpp"
#include "i_consumer_lister.hpp"
#include "i_event_distributor.hpp"
#include "i_event_consumer.hpp"

namespace smart_home
{

class EventMiddleware : public advcpp::IRunnable, private advcpp::Uncopyable
{
public:
    EventMiddleware (SharedPtr<IPullEventBus> const& a_pullBus,
        SharedPtr<IConsumerLister> const& a_consumerLister,
        SharedPtr<IEventDistributor> const& a_eventDistributor);
    //~EventMiddleware () = default;

    virtual void Run ();

private:
    typedef std::vector<SharedPtr<IEventConsumer> > ConsumerListing;

private:
    bool tryPull (SharedPtr<Event>& a_pEventRef);
    SharedPtr<ConsumerListing> tryList (SharedPtr<Event> const& a_pEvent);
    void tryDistribute (SharedPtr<Event> const& a_pEvent, SharedPtr<ConsumerListing> const& a_consumerListing);

private:
    SharedPtr<IPullEventBus> m_pullBus;
    SharedPtr<IConsumerLister> m_consumerLister;
    SharedPtr<IEventDistributor> m_eventDistributor;
};

} // smart_home

#endif // EVENT_MIDDLEWARE_HPP