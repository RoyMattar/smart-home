#include <cstddef> // size_t

#include "tagged_distribution_channel.hpp"
#include "common_utils.hpp"
#include "waitable_bounded_queue.hpp"
#include "delivery_box.hpp"
#include "group_tag.hpp"

namespace smart_home
{

TaggedDistributionChannel::TaggedDistributionChannel (size_t a_capacity, GroupTag a_tag)
    : m_channel(a_capacity)
    , m_tag(a_tag)
{ }

void TaggedDistributionChannel::Push (SharedPtr<DeliveryBox> const& a_deliveryBox)
{
    try
    {
        m_channel.Enqueue(a_deliveryBox);
    }
    catch (advcpp::WaitableBoundedQueueShutdownExc const&)
    {
        throw TaggedDistributionChannelShutdownExc();
    }
    
}

GroupTag TaggedDistributionChannel::GetTag () const NOEXCEPTIONS
{
    return m_tag;
}

void TaggedDistributionChannel::Pull (SharedPtr<DeliveryBox>& a_deliveryBox)
{
    try
    {
        m_channel.Dequeue(a_deliveryBox);
    }
    catch (advcpp::WaitableBoundedQueueShutdownExc const&)
    {
        throw TaggedDistributionChannelShutdownExc();
    }
    
}

} // smart_home