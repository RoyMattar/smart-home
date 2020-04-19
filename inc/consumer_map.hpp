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
#include "distribution_list.hpp"

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

    //@exception: may throw std::bad_alloc
    virtual void Register (Event::Type const& a_eventType, SharedPtr<IEventConsumer> const& a_newConsumer);
    //@exception: may throw InvalidEventTypeExc if a_eventType not in map, or ... if a_consumerToRemove is not subscribed to a_eventType
    virtual void Deregister (Event::Type const& a_eventType, SharedPtr<IEventConsumer> const& a_consumerToRemove);
    //@exception may throw InvalidEventTypeExc if a_eventType not in map
    virtual SharedPtr<DistributionList> List (Event::Type const& a_eventType) const;

private:
    std::tr1::unordered_map<Event::Type, SharedPtr<SafeConsumerList> > m_map;
};

#include "inl/consumer_map.hxx"

} // smart_home

#endif // CONSUMER_MAP_HPP