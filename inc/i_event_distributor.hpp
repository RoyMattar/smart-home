#ifndef I_EVENT_DISTRIBUTOR_HPP
#define I_EVENT_DISTRIBUTOR_HPP

#include <vector>

#include "common_utils.hpp"
#include "event.hpp"
#include "i_event_consumer.hpp"

namespace smart_home
{

class IEventDistributor
{
public:
    virtual ~IEventDistributor ();

    virtual void Distribute (SharedPtr<Event> const& a_pEvent,
        SharedPtr<std::vector<SharedPtr<IEventConsumer> > > const& a_consumerListing) const = 0;
};

inline IEventDistributor::~IEventDistributor ()
{ }

} // smart_home

#endif // I_EVENT_DISTRIBUTOR_HPP