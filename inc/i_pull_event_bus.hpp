#ifndef I_PULL_EVENT_BUS_HPP
#define I_PULL_EVENT_BUS_HPP

#include "common_utils.hpp"
#include "event.hpp"

namespace smart_home
{

class IPullEventBus
{
public:
    virtual ~IPullEventBus () NOEXCEPTIONS;

    virtual void Pull (SharedPtr<Event>& a_event) = 0;
};

inline IPullEventBus::~IPullEventBus () NOEXCPETIONS
{ }

} // smart_home

#endif // I_PULL_EVENT_BUS_HPP