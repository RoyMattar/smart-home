#ifndef CONSUMER_MAP_HPP
#define CONSUMER_MAP_HPP

#include <tr1/unordered_map>
#include <vector>

#include "common_utils.hpp"
#include "i_consumer_registrar.hpp"
#include "i_consumer_lister.hpp"
#include "i_event_consumer.hpp"
#include "event.hpp"
#include "consumer_list_mt.hpp"

namespace smart_home
{

template <typename SafeConsumerList = ConsumerListMT>
// require: SafeConsumerList    has void Add(SharedPtr<IEventConsumer>)
//                              has void Remove(SharedPtr<IEventConsumer>)
//                              has SharedPtr<ListCopy> GetCopy () const
//                              is multithread safe
class ConsumerMap : public IConsumerRegistrar, public IConsumerLister, private advcpp::Uncopyable
{
public:
    //ConsumerMap () = default;
    //~ConsumerMap () = default;

    virtual void Register (Event::Type a_eventType, SharedPtr<IEventConsumer> const& a_newConsumer);
    virtual void Deregister (Event::Type a_eventType, SharedPtr<IEventConsumer> const& a_oldConsumer);
    virtual SharedPtr<std::vector<SharedPtr<IEventConsumer> > > List (SharedPtr<Event> const& a_pEvent) const;

private:
    std::tr1::unordered_map<Event::Type, SafeConsumerList> m_map;
};

} // smart_home

#endif // CONSUMER_MAP_HPP