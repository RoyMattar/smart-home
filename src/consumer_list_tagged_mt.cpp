#include <list>
#include <algorithm> // std::find

#include "consumer_list_tagged_mt.hpp"
#include "common_utils.hpp"
#include "i_event_consumer.hpp"
#include "distribution_list_tagged.hpp"
#include "mutex.hpp"
#include "lock_guard.hpp"

namespace smart_home
{

bool ConsumerListTaggedMT::Add (TaggedConsumer const& a_newTaggedConsumer)
{
    advcpp::LockGuard lg(m_listMutex);

    ListTagged::const_iterator taggedConsumerItr = std::find(m_listTagged.begin(), m_listTagged.end(), a_newTaggedConsumer);
    if (taggedConsumerItr != m_listTagged.end()) { return false; }

    m_listTagged.push_back(a_newTaggedConsumer);
    return true;
}

bool ConsumerListTaggedMT::Remove (TaggedConsumer const& a_taggedConsumer)
{
    advcpp::LockGuard lg(m_listMutex);

    ListTagged::iterator taggedConsumerItr = std::find(m_listTagged.begin(), m_listTagged.end(), a_taggedConsumer);
    if (taggedConsumerItr == m_listTagged.end()) { return false; }

    m_listTagged.erase(taggedConsumerItr);
    return true;
}

SharedPtr<DistributionListTagged> ConsumerListTaggedMT::MakeDistribution () const
{
    return SharedPtr<DistributionListTagged>(new DistributionListTagged(m_listTagged.begin(), m_listTagged.end()));
}

} // smart_home