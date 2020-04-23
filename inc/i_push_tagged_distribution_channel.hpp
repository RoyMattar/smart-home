#ifndef I_PUSH_TAGGED_DISTRIBUTION_CHANNEL_HPP
#define I_PUSH_TAGGED_DISTRIBUTION_CHANNEL_HPP

#include <stdexcept> // std::exception

#include "delivery_box.hpp"
#include "group_tag.hpp"

namespace smart_home
{

class IPushTaggedDistributionChannel
{
public:
    virtual ~IPushTaggedDistributionChannel ();

    //@exception: may throw IPushTaggedDistributionChannelShutdownExc
    virtual void Push (SharedPtr<DeliveryBox> const& a_deliveryBox) = 0;
    //@retval: the channel's tag
    virtual GroupTag GetTag () const NOEXCEPTIONS = 0;
};

class IPushTaggedDistributionChannelShutdownExc : public std::exception
{
public:
    virtual ~IPushTaggedDistributionChannelShutdownExc ();
};

IPushTaggedDistributionChannel::~IPushTaggedDistributionChannel () { }

IPushTaggedDistributionChannelShutdownExc::~IPushTaggedDistributionChannelShutdownExc () { }

} // smart_home

#endif // I_PUSH_TAGGED_DISTRIBUTION_CHANNEL_HPP