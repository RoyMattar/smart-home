#ifndef I_CONSUMER_LISTER_HPP
#define I_CONSUMER_LISTER_HPP

#include "common_utils.hpp"
#include "event.hpp"
#include "distribution_list.hpp"

namespace smart_home
{

class IConsumerLister
{
public:
    virtual ~IConsumerLister ();

    virtual SharedPtr<DistributionList> List (Event::Type const& a_eventType, Event::Location const& a_eventLocation) const = 0;
};

inline IConsumerLister::~IConsumerLister ()
{ }

} // smart_home

#endif // I_CONSUMER_LISTER_HPP