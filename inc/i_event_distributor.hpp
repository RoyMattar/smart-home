#ifndef I_EVENT_DISTRIBUTOR_HPP
#define I_EVENT_DISTRIBUTOR_HPP

#include "common_utils.hpp"
#include "i_push_distribution_channel.hpp"
#include "i_tagged.hpp"
#include "event.hpp"
#include "distribution_list_tagged.hpp"

namespace smart_home
{

class IEventDistributor
{
public:
    virtual ~IEventDistributor ();

    virtual void AddChannel (SharedPtr<IPushDistributionChannel> a_pushChannel,
                             SharedPtr<ITagged> a_tagged) = 0;
    //@exception throws std::out_of_range if no channel found by the given tag
    virtual void Distribute (SharedPtr<Event> const& a_pEvent,
                             SharedPtr<DistributionListTagged> const& a_distributionListTagged) = 0;
};

inline IEventDistributor::~IEventDistributor () { }

} // smart_home

#endif // I_EVENT_DISTRIBUTOR_HPP