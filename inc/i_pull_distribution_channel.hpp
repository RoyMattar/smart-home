#ifndef I_PULL_DISTRIBUTION_CHANNEL_HPP
#define I_PULL_DISTRIBUTION_CHANNEL_HPP

#include <stdexcept> // std::exception

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
    virtual ~IPullDistributionChannelShutdownExc ();
};

IPullDistributionChannel::~IPullDistributionChannel () { }

IPullDistributionChannelShutdownExc::~IPullDistributionChannelShutdownExc () { }

} // smart_home

#endif // I_PULL_DISTRIBUTION_CHANNEL_HPP