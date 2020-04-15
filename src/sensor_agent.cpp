#include "sensor_agent.hpp"

namespace smart_home
{

SensorAgent::SensorAgent (SharedPtr<IPushEventBus> const& a_pushBus)
    : m_pushBus(a_pushBus)
{ }

void SensorAgent::Publish (Event const& a_event)
{
    m_pushBus->Push(SharedPtr<Event>(new Event(a_event)));
}

} // smart_home