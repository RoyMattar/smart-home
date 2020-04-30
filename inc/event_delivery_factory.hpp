#ifndef EVENT_DELIVERY_FACTORY_HPP
#define EVENT_DELIVERY_FACTORY_HPP

#include <vector>
#include <utility> // std::pair
#include <cstddef> // size_t

#include "common_utils.hpp"
#include "i_push_distribution_channel.hpp"
#include "i_pull_distribution_channel.hpp"
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
    //       a_pushChannel for stopping the courier thread
    void AddCourier (SharedPtr<IPullDistributionChannel> const& a_pullChannel,
                     SharedPtr<IPushDistributionChannel> const& a_pushChannel);
    //@retval returns the number of courier threads currently running deliveries
    size_t NumOfCouriers () const NOEXCEPTIONS;
    //@brief calls all courier threads to stop deliveries
    void StopAll ();

private:
    void intoxicateAll ();

private:
    typedef std::pair<SharedPtr<IPullDistributionChannel>, SharedPtr<IPushDistributionChannel> > ChannelPair;

private:
    advcpp::ThreadGroupMT<EventCourier> m_deliveryCrew;
    std::vector<ChannelPair> m_distributionChannels;
};

inline size_t EventDeliveryFactory::NumOfCouriers () const NOEXCEPTIONS { return m_deliveryCrew.NumOfThreads(); }

} // smart_home

#endif // EVENT_DELIVERY_FACTORY_HPP