#ifndef CONSUMER_MAP_HPP
#define CONSUMER_MAP_HPP

#include <tr1/unordered_map>
#include <string>

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
//                              has SharedPtr<DistributionList> MakeDistribution () const
//                              is multithread safe
class ConsumerMap : public IConsumerRegistrar, public IConsumerLister, private advcpp::Uncopyable
{
public:
    //ConsumerMap () = default;
    //~ConsumerMap () = default;

    //@exception: may throw std::bad_alloc
    virtual void Register (SharedPtr<IEventConsumer> const& a_newConsumer, Event::Type const& a_eventType, Event::Location const& a_eventLocation);
    //@exception: may throw EventNotFoundExc if no corresponding event found in the map, or ... if a_consumerToRemove is not subscribed to a_eventType
    virtual void Deregister (SharedPtr<IEventConsumer> const& a_consumer, Event::Type const& a_eventType, Event::Location const& a_eventLocation);
    //@exception may throw NoConsumersExc if no consumers were found for the corresponding event
    virtual SharedPtr<DistributionList> List (Event::Type const& a_eventType, Event::Location const& a_eventLocation) const;

private:
    static std::string makeKey (Event::Type const& a_eventType, Event::Location const& a_eventLocation);
    //@exception may throw NoConsumersExc if no consumers were found for the corresponding event
    SharedPtr<DistributionList> listCombination (Event::Type const& a_eventType, Event::Location const& a_eventLocation) const;

private:
    std::tr1::unordered_map<std::string, SharedPtr<SafeConsumerList> > m_map;
};

#include "inl/consumer_map.hxx"

} // smart_home

#endif // CONSUMER_MAP_HPP