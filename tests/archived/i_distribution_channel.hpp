#ifndef I_DISTRIBUTION_CHANNEL_HPP
#define I_DISTRIBUTION_CHANNEL_HPP

#include "i_push_distribution_channel.hpp"
#include "i_pull_distribution_channel.hpp"

namespace smart_home
{

class IDistributionChannel : public IPushDistributionChannel, public IPullDistributionChannel
{
public:
    virtual ~IDistributionChannel ();

    //@exception: may throw IPushDistributionChannelShutdownExc
    virtual void Push (SharedPtr<DeliveryBox> const& a_deliveryBox) = 0;
    //@exception: may throw IPullDistributionChannelShutdownExc
    virtual void Pull (SharedPtr<DeliveryBox>& a_deliveryBox) = 0;
};

inline IDistributionChannel::~IDistributionChannel () { }

} // smart_home

#endif // I_DISTRIBUTION_CHANNEL_HPP