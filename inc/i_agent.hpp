#ifndef I_AGENT_HPP
#define I_AGENT_HPP

#include "common_utils.hpp"
#include "i_push_event_bus.hpp"
#include "i_consumer_registrar.hpp"

namespace smart_home
{

class IAgent
{
public:
    virtual void Connect (SharedPtr<IPushEventBus> const& a_pushBus,
                          SharedPtr<IConsumerRegistrar> const& a_registrar) = 0;
};

} // smart_home

#endif // I_AGENT_HPP