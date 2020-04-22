#ifndef CONSUMER_LIST_TAGGED_MT_HPP
#define CONSUMER_LIST_TAGGED_MT_HPP

#include <list>

#include "common_utils.hpp"
#include "tagged_consumer.hpp"
#include "distribution_list_tagged.hpp"
#include "mutex.hpp"

namespace smart_home
{

class ConsumerListTaggedMT : private advcpp::Uncopyable
{
public:
    //ConsumerListTaggedMT () = default;
    //~ConsumerListTaggedMT () = default;

    bool Add (TaggedConsumer const& a_newTaggedConsumer);
    bool Remove (TaggedConsumer const& a_taggedConsumer);
    SharedPtr<DistributionListTagged> MakeDistribution () const;

private:
    typedef std::list<TaggedConsumer> ListTagged;

private:
    ListTagged m_listTagged;
    advcpp::Mutex m_listMutex;
};

} // smart_home

#endif // CONSUMER_LIST_TAGGED_MT_HPP