#ifndef SENSOR_AGENT_HPP
#define SENSOR_AGENT_HPP

#include "common_utils.hpp"
#include "i_push_event_bus.hpp"
#include "event.hpp"

namespace smart_home
{

class SensorAgent
{
public:
    SensorAgent (SharedPtr<IPushEventBus> const& a_pushBus);
    //SensorAgent (SensorAgent const& a_other) = default;
    //~SensorAgent () = default;
    //SensorAgent& operator= (SensorAgent const& a_other) = default;

    void PublishEvent (Event const& a_event);

private:
    SharedPtr<IPushEventBus> m_pushBus;
};

} // smart_home

#endif // SENSOR_AGENT_HPP