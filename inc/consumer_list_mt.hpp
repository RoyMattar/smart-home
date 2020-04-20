#ifndef CONSUMER_LIST_HPP
#define CONSUMER_LIST_HPP

#include <list>

#include "common_utils.hpp"
#include "i_event_consumer.hpp"
#include "distribution_list.hpp"
#include "mutex.hpp"

namespace smart_home
{

class ConsumerListMT : private advcpp::Uncopyable
{
public:
    //ConsumerListMT () = default;
    //~ConsumerListMT () = default;

    void Add (SharedPtr<IEventConsumer> const& a_newConsumer);
    void Remove (SharedPtr<IEventConsumer> const& a_consumer);
    SharedPtr<DistributionList> MakeDistribution () const;

private:
    std::list<SharedPtr<IEventConsumer> > m_list;
    advcpp::Mutex m_listMutex;
};

} // smart_home

#endif // CONSUMER_LIST_HPP