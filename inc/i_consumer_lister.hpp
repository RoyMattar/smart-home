#ifndef I_CONSUMER_LISTER_HPP
#define I_CONSUMER_LISTER_HPP

#include <vector>

#include "common_utils.hpp"
#include "i_event_consumer.hpp"
#include "event.hpp"

namespace smart_home
{

class IConsumerLister
{
public:
    virtual ~IConsumerLister ();

    virtual SharedPtr<std::vector<SharedPtr<IEventConsumer> > > List (SharedPtr<Event> const& a_pEvent) const;
};

inline IConsumerLister::~IConsumerLister ()
{ }

} // smart_home

#endif // I_CONSUMER_LISTER_HPP