#include <vector>

#include "simple_event_distributor.hpp"
#include "common_utils.hpp"
#include "event.hpp"
#include "i_event_consumer.hpp"
#include "distribution_list.hpp"

namespace smart_home
{

void SimpleEventDistributor::Distribute (SharedPtr<Event> const& a_pEvent,
    SharedPtr<DistributionList> const& a_consumerListing) const
{
    for (std::vector<SharedPtr<IEventConsumer> >::size_type i = 0;
        i < a_consumerListing->size();
        ++i)
    {
        (*a_consumerListing)[i]->Consume(a_pEvent);
    }
}

} // smart_home