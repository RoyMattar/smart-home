#ifndef SIMPLE_EVENT_DISTRIBUTOR_HPP
#define SIMPLE_EVENT_DISTRIBUTOR_HPP

#include <vector>

#include "i_event_distributor.hpp"
#include "common_utils.hpp"
#include "event.hpp"
#include "i_event_consumer.hpp"
#include "distribution_list.hpp"

namespace smart_home
{

class SimpleEventDistributor : public IEventDistributor
{
public:
    //SimpleEventDistributor ();
    //SimpleEventDistributor (SimpleEventDistributor const& a_other);
    //~SimpleEventDistributor ();
    //SimpleEventDistributor& operator= (SimpleEventDistributor const& a_other);

    virtual void Distribute (SharedPtr<Event> const& a_pEvent,
        SharedPtr<DistributionList> const& a_consumerListing) const;
};

} // smart_home

#endif // SIMPLE_EVENT_DISTRIBUTOR_HPP