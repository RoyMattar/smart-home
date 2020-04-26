#ifndef EVENT_MIDDLEWARE_HPP
#define EVENT_MIDDLEWARE_HPP

#include "i_runnable.hpp"
#include "common_utils.hpp"
#include "i_pull_event_bus.hpp"
#include "i_consumer_lister.hpp"
#include "i_event_distributor.hpp"
#include "event.hpp"
#include "event_topic.hpp"
#include "distribution_list_tagged.hpp"

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
    bool tryPull (SharedPtr<Event>& a_pEventRef);
    SharedPtr<DistributionListTagged> tryList (EventTopic const& a_eventTopic);
    void tryDistribute (SharedPtr<Event> const& a_pEvent,
                        SharedPtr<DistributionListTagged> const& a_distributionListTagged);

private:
    SharedPtr<IPullEventBus> m_pullBus;
    SharedPtr<IConsumerLister> m_consumerLister;
    SharedPtr<IEventDistributor> m_eventDistributor;
};

} // smart_home

#endif // EVENT_MIDDLEWARE_HPP