#ifndef DISTRIBUTION_LIST_HPP
#define DISTRIBUTION_LIST_HPP

#include <vector>

#include "common_utils.hpp"
#include "i_event_consumer.hpp"

namespace smart_home
{

typedef std::vector<SharedPtr<IEventConsumer> > DistributionList;

} // smart_home

#endif // DISTRIBUTION_LIST_HPP