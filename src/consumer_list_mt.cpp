#include <vector>
#include <list>
#include <cassert> // to be removed when Remove is implemented

#include "consumer_list_mt.hpp"
#include "common_utils.hpp"
#include "i_event_consumer.hpp"
#include "event.hpp"
#include "mutex.hpp"
#include "lock_guard.hpp"

namespace smart_home
{

void ConsumerListMT::Add (SharedPtr<IEventConsumer> const& a_newConsumer)
{
    advcpp::LockGuard lg(m_listMutex);
    m_list.push_back(a_newConsumer);
}

void ConsumerListMT::Remove (SharedPtr<IEventConsumer> const& a_consumer)
{
    assert(!"Remove(consumer) not yet implemented - might require operator== at IEventConsumer");
}

SharedPtr<ConsumerListMT::ListCopy> ConsumerListMT::GetCopy () const
{
    return SharedPtr<ListCopy>(new ListCopy(m_list.begin(), m_list.end()));
}

} // smart_home