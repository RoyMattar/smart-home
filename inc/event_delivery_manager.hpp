#ifndef EVENT_DELIVERY_MANAGER_HPP
#define EVENT_DELIVERY_MANAGER_HPP

#include <cstddef> // size_t

#include "common_utils.hpp"
#include "i_pull_distribution_channel.hpp"
#include "thread_group_mt.hpp"
#include "event_courier.hpp"

namespace smart_home
{

class EventDeliveryManager
{
public:
    //EventDeliveryManager () = default;
    //EventDeliveryManager (EventDeliveryManager const& a_other) = default;
    //~EventDeliveryManager () = default;
    //EventDeliveryManager& operator= (EventDeliveryManager const& a_other) = default;

    void AddCourier (SharedPtr<IPullDistributionChannel> const& a_pullChannel);
    size_t NumOfCouriers () const NOEXCEPTIONS;
    //@brief joins all courier threads
    //@warning will block if IPullDistributionChannel had not been shut down
    void CleanUp ();

private:
    ThreadGroupMT<EventCourier> m_couriers;
};

} // smart_home

#endif // EVENT_DELIVERY_MANAGER_HPP