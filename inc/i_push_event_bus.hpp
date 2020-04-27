#ifndef I_PUSH_EVENT_BUS_HPP
#define I_PUSH_EVENT_BUS_HPP

#include <stdexcept> // std::exception

#include "common_utils.hpp"
#include "event.hpp"

namespace smart_home
{

class IPushEventBus
{
public:
    virtual ~IPushEventBus ();

    //@exception: throws IPushEventBusShutdownExc
    virtual void Push (SharedPtr<Event> const& a_pEvent) = 0;
};

class IPushEventBusShutdownExc : public std::exception
{
public:
    virtual ~IPushEventBusShutdownExc () NOEXCEPTIONS;
};

inline IPushEventBus::~IPushEventBus () { }

inline IPushEventBusShutdownExc::~IPushEventBusShutdownExc () NOEXCEPTIONS { }

} // smart_home

#endif // I_PUSH_BUS_HPP