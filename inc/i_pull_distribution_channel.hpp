#ifndef I_PULL_DISTRIBUTION_CHANNEL_HPP
#define I_PULL_DISTRIBUTION_CHANNEL_HPP

#include <stdexcept> // std::exception

#include "common_utils.hpp"
#include "delivery_box.hpp"

namespace smart_home
{

class IPullDistributionChannel
{
public:
    virtual ~IPullDistributionChannel ();

    //@exception: may throw IPullDistributionChannelShutdownExc
    virtual void Pull (SharedPtr<DeliveryBox>& a_deliveryBox) = 0;
};

class IPullDistributionChannelShutdownExc : public std::exception
{
public:
    virtual ~IPullDistributionChannelShutdownExc () NOEXCEPTIONS;
};

inline IPullDistributionChannel::~IPullDistributionChannel () { }

inline IPullDistributionChannelShutdownExc::~IPullDistributionChannelShutdownExc () NOEXCEPTIONS { }

} // smart_home

#endif // I_PULL_DISTRIBUTION_CHANNEL_HPP