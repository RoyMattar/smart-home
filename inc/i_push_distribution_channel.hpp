#ifndef I_PUSH_DISTRIBUTION_CHANNEL_HPP
#define I_PUSH_DISTRIBUTION_CHANNEL_HPP

#include <stdexcept> // std::exception

#include "common_utils.hpp"
#include "delivery_box.hpp"

namespace smart_home
{

class IPushDistributionChannel
{
public:
    virtual ~IPushDistributionChannel ();

    //@exception: may throw IPushDistributionChannelShutdownExc
    virtual void Push (SharedPtr<DeliveryBox> const& a_deliveryBox) = 0;
};

class IPushDistributionChannelShutdownExc : public std::exception
{
public:
    virtual ~IPushDistributionChannelShutdownExc () NOEXCEPTIONS;
};

inline IPushDistributionChannel::~IPushDistributionChannel () { }

inline IPushDistributionChannelShutdownExc::~IPushDistributionChannelShutdownExc () NOEXCEPTIONS { }

} // smart_home

#endif // I_PUSH_DISTRIBUTION_CHANNEL_HPP