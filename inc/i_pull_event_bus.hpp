#ifndef I_PULL_EVENT_BUS_HPP
#define I_PULL_EVENT_BUS_HPP

#include <stdexcept> // std::exception

#include "common_utils.hpp"
#include "event.hpp"

namespace smart_home
{

class IPullEventBus
{
public:
    virtual ~IPullEventBus ();

    //@exception: throws IPullEventBusShutdownExc
    virtual void Pull (SharedPtr<Event>& a_pEvent) = 0;
};

class IPullEventBusShutdownExc : public std::exception
{
public:
    virtual ~IPullEventBusShutdownExc ();
};

inline IPullEventBus::~IPullEventBus () { }

inline IPullEventBusShutdownExc::~IPullEventBusShutdownExc () { }

} // smart_home

#endif // I_PULL_EVENT_BUS_HPP