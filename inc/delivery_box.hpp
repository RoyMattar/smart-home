#ifndef DELIVERY_BOX_HPP
#define DELIVERY_BOX_HPP

#include <utility> // std::pair

#include "common_utils.hpp"
#include "event.hpp"
#include "i_event_consumer.hpp"

namespace smart_home
{

typedef std::pair<SharedPtr<Event>, SharedPtr<IEventConsumer> > DeliveryBox;

} // smart_home

#endif // DELIVERY_BOX_HPP