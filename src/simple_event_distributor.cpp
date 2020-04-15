#include <vector>

#include "simple_event_distributor.hpp"
#include "common_utils.hpp"
#include "event.hpp"
#include "i_event_consumer.hpp"

namespace smart_home
{

void SimpleEventDistributor::Distribute (SharedPtr<Event> const& a_pEvent,
    SharedPtr<std::vector<SharedPtr<IEventConsumer> > > const& a_consumerListing) const
{
    for (std::vector<SharedPtr<IEventConsumer> >::size_type i = 0;
        i < a_consumerListing->size();
        ++i)
    {
        (*a_consumerListing)[i]->Deliver(a_pEvent);
    }
}

} // smart_home