#ifndef TAGGED_CONSUMER_HPP
#define TAGGED_CONSUMER_HPP

#include <utility> // std::pair

#include "common_utils.hpp"
#include "group_tag.hpp"
#include "i_event_consumer.hpp"

namespace smart_home
{

typedef std::pair<GroupTag, SharedPtr<IEventConsumer> > TaggedConsumer;

} // smart_home

#endif // TAGGED_CONSUMER_HPP