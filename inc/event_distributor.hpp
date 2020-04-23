#ifndef EVENT_DISTRIBUTOR_HPP
#define EVENT_DISTRIBUTOR_HPP

#include <vector>
#include <tr1/unordered_map>

#include "i_event_distributor.hpp"
#include "common_utils.hpp"
#include "i_push_tagged_distribution_channel.hpp"
#include "event.hpp"
#include "distribution_list_tagged.hpp"
#include "group_tag.hpp"

namespace smart_home
{

class EventDistributor : public IEventDistributor
{
public:
    EventDistributor (std::vector<SharedPtr<IPushTaggedDistributionChannel> > const& a_taggedChannels);
    //EventDistributor (EventDistributor const& a_other) = default;
    //~EventDistributor () = default;
    //EventDistributor& operator= (EventDistributor const& a_other) = default;

    virtual void Distribute (SharedPtr<Event> const& a_pEvent,
                             SharedPtr<DistributionListTagged> const& a_distributionListTagged);

private:
    typedef std::tr1::unordered_map<GroupTag, SharedPtr<IPushTaggedDistributionChannel> > ChannelMap;

private:
    static SharedPtr<DeliveryBox> makeDeliveryBox (SharedPtr<Event> const& a_pEvent, SharedPtr<IEventConsumer> const& a_pConsumer);

    void mapTaggedChannels (std::vector<SharedPtr<IPushTaggedDistributionChannel> > const& a_taggedChannels);
    void pushBoxToChannel (GroupTag a_channelTag, SharedPtr<DeliveryBox> const& a_deliveryBox);

private:
    ChannelMap m_channelMap;
};

} // smart_home

#endif // EVENT_DISTRIBUTOR_HPP