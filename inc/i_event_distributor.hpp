#ifndef I_EVENT_DISTRIBUTOR_HPP
#define I_EVENT_DISTRIBUTOR_HPP

#include "common_utils.hpp"
#include "distribution_list_tagged.hpp"

namespace smart_home
{

class IEventDistributor
{
public:
    virtual ~IEventDistributor ();

    virtual void Distribute (SharedPtr<Event> const& a_pEvent,
                             SharedPtr<DistributionListTagged> const& a_distributionListTagged) = 0;
};

IEventDistributor::~IEventDistributor () { }

} // smart_home

#endif // I_EVENT_DISTRIBUTOR_HPP