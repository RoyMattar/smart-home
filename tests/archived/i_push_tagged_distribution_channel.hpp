#ifndef I_PUSH_TAGGED_DISTRIBUTION_CHANNEL_HPP
#define I_PUSH_TAGGED_DISTRIBUTION_CHANNEL_HPP

#include "i_push_distribution_channel.hpp"
#include "i_tag_getter.hpp"
#include "common_utils.hpp"
#include "delivery_box.hpp"
#include "group_tag.hpp"

namespace smart_home
{

class IPushTaggedDistributionChannel : public IPushDistributionChannel, public ITagGetter
{
public:
    virtual ~IPushTaggedDistributionChannel ();

    //@exception: may throw IPushTaggedDistributionChannelShutdownExc
    virtual void Push (SharedPtr<DeliveryBox> const& a_deliveryBox) = 0;
    //@retval: the channel's tag
    virtual GroupTag GetTag () const NOEXCEPTIONS = 0;
};

inline IPushTaggedDistributionChannel::~IPushTaggedDistributionChannel () { }

} // smart_home

#endif // I_PUSH_TAGGED_DISTRIBUTION_CHANNEL_HPP