#ifndef I_CONSUMER_LISTER_HPP
#define I_CONSUMER_LISTER_HPP

#include "common_utils.hpp"
#include "event_topic.hpp"
#include "distribution_list_tagged.hpp"

namespace smart_home
{

class IConsumerLister
{
public:
    virtual ~IConsumerLister ();

    virtual SharedPtr<DistributionListTagged> List (EventTopic const& a_eventTopic) const = 0;
};

inline IConsumerLister::~IConsumerLister () { }

} // smart_home

#endif // I_CONSUMER_LISTER_HPP