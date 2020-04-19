#ifndef I_CONSUMER_LISTER_HPP
#define I_CONSUMER_LISTER_HPP

#include <vector>

#include "common_utils.hpp"
#include "i_event_consumer.hpp"
#include "event.hpp"
#include "distribution_list.hpp"

namespace smart_home
{

class IConsumerLister
{
public:
    virtual ~IConsumerLister ();

    virtual SharedPtr<DistributionList> List (Event::Type const& a_eventType) const = 0;
};

inline IConsumerLister::~IConsumerLister ()
{ }

} // smart_home

#endif // I_CONSUMER_LISTER_HPP