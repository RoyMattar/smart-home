#ifndef CONSUMER_MAP_TAGGED_HPP
#define CONSUMER_MAP_TAGGED_HPP

#include <tr1/unordered_map>

#include "common_utils.hpp"
#include "i_consumer_registrar.hpp"
#include "i_consumer_lister.hpp"
#include "i_event_consumer.hpp"
#include "event.hpp"
#include "event_topic.hpp"
#include "consumer_list_tagged_mt.hpp"
#include "distribution_list_tagged.hpp"
#include "cyclic_tag.hpp"
#include "group_tag.hpp"

namespace smart_home
{
struct EventTopicHasher;


template <typename SafeTaggedList = ConsumerListTaggedMT>
// require: SafeTaggedList      has bool Add(TaggedConsumer)
//                              has bool Remove(TaggedConsumer)
//                              has SharedPtr<DistributionListTagged> MakeDistribution () const
//                              is multithread safe
class ConsumerMapTagged : public IConsumerRegistrar, public IConsumerLister, private advcpp::Uncopyable
{
public:
    explicit ConsumerMapTagged (CyclicTag::TagType const& a_numOfTags);
    //~ConsumerMapTagged () = default;

    //@retval: true if successfully registered, false if consumer had already been registered to a_eventTopic
    virtual bool Register (EventTopic const& a_eventTopic, SharedPtr<IEventConsumer> const& a_newConsumer);
    //@retval: true if successfully deregistered, false if consumer is not registered to a_eventTopic
    //@exception: throws std::out_of_range if a_eventTopic is not in map
    virtual bool Deregister (EventTopic const& a_eventTopic, SharedPtr<IEventConsumer> const& a_consumer);
    //@retval: list of tagged consumers registered to a_eventTopic; if a_eventTopic is not found, returned list will be empty
    virtual SharedPtr<DistributionListTagged> List (EventTopic const& a_eventTopic) const;

private:
    typedef std::tr1::unordered_map<IEventConsumer*, GroupTag> TagMap;
    typedef std::tr1::unordered_map<EventTopic, SharedPtr<SafeTaggedList> , EventTopicHasher> ListMap;

private:
    bool tryInsertNewTag (SharedPtr<IEventConsumer> const& a_newConsumer);
    bool tryInsertNewTopic (EventTopic const& a_eventTopic);
    bool tryAddNewConsumer (EventTopic const& a_eventTopic, SharedPtr<IEventConsumer> const& a_newConsumer);
    SharedPtr<DistributionListTagged> listCombination (EventTopic const& a_eventTopic) const;
    SharedPtr<DistributionListTagged> listSpecificRoom (EventTopic const& a_eventTopic) const;
    SharedPtr<DistributionListTagged> listAnyRoom (Event::Type const& a_eventType, Event::Location::Floor const& a_eventFloor) const;
    SharedPtr<DistributionListTagged> listAnyFloor (Event::Type const& a_eventType) const;
    SharedPtr<DistributionListTagged> listAnyType () const;
    SharedPtr<DistributionListTagged> concatLists (SharedPtr<DistributionListTagged> a_specificRoomList, SharedPtr<DistributionListTagged> a_anyRoomList, SharedPtr<DistributionListTagged> a_anyFloorList, SharedPtr<DistributionListTagged> a_anyTypeList) const;

private:
    TagMap m_tagMap;
    ListMap m_listMap;
    CyclicTag m_cyclicTag;
};

#include "inl/consumer_map_tagged.hxx"

} // smart_home

#endif // CONSUMER_MAP_TAGGED_HPP