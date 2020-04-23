#ifndef EVENT_COURIER_HPP
#define EVENT_COURIER_HPP

#include "common_utils.hpp"
#include "i_runnable.hpp"
#include "i_pull_distribution_channel.hpp"

namespace smart_home
{

class EventCourier : public advcpp::IRunnable
{
public:
    EventCourier (SharedPtr<IPullDistributionChannel> const& a_pullChannel);
    //EventCourier (EventCourier const& a_other) = default;
    //~EventCourier () = default;
    //EventCourier& operator= (EventCourier const& a_other) = default;

    virtual void Run ();

private:
    static void handOutEventToConsumer (SharedPtr<Event> const& a_event, SharedPtr<IEventConsumer> const& a_consumer);

private:
    SharedPtr<IPullDistributionChannel> m_pullChannel;
};

} // smart_home

#endif // EVENT_COURIER_HPP