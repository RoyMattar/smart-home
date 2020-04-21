#ifndef I_CONSUMER_PARTITIONED_LISTER_HPP
#define I_CONSUMER_PARTITIONED_LISTER_HPP

#include <vector>

#include "common_utils.hpp"
#include "event.hpp"
#include "distribution_list.hpp"

namespace smart_home
{

class IConsumerPartitionedLister
{
public:
    virtual ~IConsumerPartitionedLister ();

    virtual SharedPtr<std::vector<DistributionList> > List (Event::Type const& a_eventType, Event::Location const& a_eventLocation) const = 0;
};

inline IConsumerPartitionedLister::~IConsumerPartitionedLister ()
{ }

} // smart_home

#endif // I_CONSUMER_PARTITIONED_LISTER_HPP