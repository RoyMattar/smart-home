#ifndef EVENT_DISTRIBUTOR_HPP
#define EVENT_DISTRIBUTOR_HPP

#include <vector>
#include <tr1/unordered_map>

#include "i_event_distributor.hpp"
#include "common_utils.hpp"
#include "i_push_distribution_channel.hpp"
#include "i_tag_getter.hpp"
#include "event.hpp"
#include "distribution_list_tagged.hpp"
#include "group_tag.hpp"

namespace smart_home
{

class EventDistributor : public IEventDistributor
{
public:
    //EventDistributor () = default;
    //EventDistributor (EventDistributor const& a_other) = default;
    //~EventDistributor () = default;
    //EventDistributor& operator= (EventDistributor const& a_other) = default;

    virtual void AddTaggedChannel (SharedPtr<ITagGetter> const& a_tagGetter, 
                                   SharedPtr<IPushDistributionChannel> const& a_pushChannel);
    //@exception throws std::out_of_range if no channel matches given tag
    virtual void Distribute (SharedPtr<Event> const& a_pEvent,
                             SharedPtr<DistributionListTagged> const& a_distributionListTagged);

private:
    typedef std::tr1::unordered_map<GroupTag, SharedPtr<IPushDistributionChannel> > ChannelMap;

private:
    static SharedPtr<DeliveryBox> makeDeliveryBox (SharedPtr<Event> const& a_pEvent, SharedPtr<IEventConsumer> const& a_pConsumer);

    void pushBoxToChannel (GroupTag a_channelTag, SharedPtr<DeliveryBox> const& a_deliveryBox);

private:
    ChannelMap m_channelMap;
};

} // smart_home

#endif // EVENT_DISTRIBUTOR_HPP