#ifndef I_EVENT_DISTRIBUTOR_HPP
#define I_EVENT_DISTRIBUTOR_HPP

#include "common_utils.hpp"
#include "event.hpp"
#include "distribution_list_tagged.hpp"

namespace smart_home
{

class IEventDistributor
{
public:
    virtual ~IEventDistributor ();

    //@exception throws std::out_of_range if no channel found by the given tag
    virtual void Distribute (SharedPtr<Event> const& a_pEvent,
                             SharedPtr<DistributionListTagged> const& a_distributionListTagged) = 0;
};

inline IEventDistributor::~IEventDistributor () { }

} // smart_home

#endif // I_EVENT_DISTRIBUTOR_HPP