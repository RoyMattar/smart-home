#ifndef TAGGED_CONSUMER_DATABASE_HPP
#define TAGGED_CONSUMER_DATABASE_HPP

#include <vector>
#include <cstddef> // size_t

#include "common_utils.hpp"
#include "consumer_map.hpp"
#include "i_consumer_registrar.hpp"
#include "i_consumer_lister.hpp"
#include "event.hpp"
#include "i_event_consumer.hpp"
#include "distribution_list.hpp"

namespace smart_home
{

template <typename ConsumerMap = ConsumerMap<> >
class TaggedConsumerDatabase : public IConsumerRegistrar, public IConsumerLister, private advcpp::Uncopyable
{
public:
    TaggedConsumerDatabase (size_t a_numOfTags);
    // ~TaggedConsumerDatabase () = default;

    //@exception: may throw std::bad_alloc
    virtual void Register (SharedPtr<IEventConsumer> const& a_newConsumer, Event::Type const& a_eventType, Event::Location const& a_eventLocation);
    //@exception: may throw EventNotFoundExc if no corresponding event found in the map, or ... if a_consumerToRemove is not subscribed to a_eventType
    virtual void Deregister (SharedPtr<IEventConsumer> const& a_consumer, Event::Type const& a_eventType, Event::Location const& a_eventLocation);
    //@exception may throw NoConsumersExc if no consumers were found for the corresponding event
    virtual SharedPtr<DistributionList> List (Event::Type const& a_eventType, Event::Location const& a_eventLocation) const;

private:
    typedef std::vector<ConsumerMap> PartitionContainer;

private:
    PartitionContainer m_taggedMaps;
    PartitionContainer::size_type m_indexRoundRobin;
};

} // smart_home

#endif // TAGGED_CONSUMER_DATABASE_HPP