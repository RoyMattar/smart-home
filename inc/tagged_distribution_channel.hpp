#ifndef TAGGED_DISTRIBUTION_CHANNEL_HPP
#define TAGGED_DISTRIBUTION_CHANNEL_HPP

#include <cstddef> // size_t

#include "common_utils.hpp"
#include "i_push_tagged_distribution_channel.hpp"
#include "i_pull_distribution_channel.hpp"
#include "waitable_bounded_queue.hpp"
#include "delivery_box.hpp"
#include "group_tag.hpp"

namespace smart_home
{

class TaggedDistributionChannel : public IPushTaggedDistributionChannel, public IPullDistributionChannel, private advcpp::Uncopyable
{
public:
    TaggedDistributionChannel (size_t a_capacity, GroupTag a_tag);
    //~TaggedDistributionChannel () = default;

    virtual void Push (SharedPtr<DeliveryBox> const& a_deliveryBox);
    virtual GroupTag GetTag () const NOEXCEPTIONS;
    virtual void Pull (SharedPtr<DeliveryBox>& a_deliveryBox);
    size_t NumOfElems () const NOEXCEPTIONS;

private:
    typedef advcpp::WaitableBoundedQueue<SharedPtr<DeliveryBox> > ChannelType;

private:
    ChannelType m_channel;
    GroupTag m_tag;
};

class TaggedDistributionChannelShutdownExc : public IPushTaggedDistributionChannelShutdownExc, public IPullDistributionChannelShutdownExc
{
    const char* what () const NOEXCEPTIONS;
};

inline size_t TaggedDistributionChannel::NumOfElems () const NOEXCEPTIONS
{
    return m_channel.NumOfElems();
}

inline const char* TaggedDistributionChannelShutdownExc::what() const NOEXCEPTIONS
{
    return "Distribution channel is shutting down";
}

} // smart_home

#endif // TAGGED_DISTRIBUTION_CHANNEL_HPP