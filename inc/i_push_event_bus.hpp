#ifndef I_PUSH_EVENT_BUS_HPP
#define I_PUSH_EVENT_BUS_HPP

#include "common_utils.hpp"
#include "event.hpp"

namespace smart_home
{

class IPushEventBus
{
public:
    virtual ~IPushEventBus ();

    virtual void Push (const SharedPtr<Event>& a_event) = 0;
};

inline IPushEventBus::~IPushEventBus ()
{ }

} // smart_home

#endif // I_PUSH_BUS_HPP