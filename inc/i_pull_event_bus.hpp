#ifndef I_PULL_EVENT_BUS_HPP
#define I_PULL_EVENT_BUS_HPP

#include "common_utils.hpp"
#include "event.hpp"

namespace smart_home
{

class IPullEventBus
{
public:
    virtual ~IPullEventBus ();

    virtual void Pull (SharedPtr<Event>& a_event) = 0;
};

inline IPullEventBus::~IPullEventBus ()
{ }

} // smart_home

#endif // I_PULL_EVENT_BUS_HPP