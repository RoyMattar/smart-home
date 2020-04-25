#ifndef EVENT_DELIVERY_FACTORY_HPP
#define EVENT_DELIVERY_FACTORY_HPP

#include <vector>
#include <cstddef> // size_t

#include "common_utils.hpp"
#include "i_distribution_channel.hpp"
#include "thread_group_mt.hpp"
#include "event_courier.hpp"

namespace smart_home
{

class EventDeliveryFactory
{
public:
    //EventDeliveryFactory () = default;
    //~EventDeliveryFactory () = default;

    //@brief adds a courier thread, pulling from a_distributionChannel for delivery
    void AddCourier (SharedPtr<IDistributionChannel> const& a_distributionChannel);
    //@retval returns the number of courier threads currently running deliveries
    size_t NumOfCouriers () const NOEXCEPTIONS;
    //@brief calls all courier threads to stop deliveries
    void StopAll ();

private:
    void intoxicateAll ();
    void joinAll ();

private:
    advcpp::ThreadGroupMT<EventCourier> m_deliveryCrew;
    std::vector<SharedPtr<IDistributionChannel> > m_distributionChannels;
};

inline size_t EventDeliveryFactory::NumOfCouriers () const NOEXCEPTIONS { return m_deliveryCrew.NumOfThreads(); }

} // smart_home

#endif // EVENT_DELIVERY_FACTORY_HPP