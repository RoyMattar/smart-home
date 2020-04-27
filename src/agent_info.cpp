#include "agent_info.hpp"

namespace smart_home
{

AgentInfo::AgentInfo (DeviceID const& a_deviceID, DeviceType const& a_deviceType,
               DeviceLocation const& a_deviceLocation,
               AgentLog const& a_agentLog, AgentConfig const& a_agentConfig) NOEXCEPTIONS
    : m_deviceID(a_deviceID)
    , m_deviceType(a_deviceType)
    , m_deviceLocation(a_deviceLocation)
    , m_agentLog(a_agentLog)
    , m_agentConfig(a_agentConfig)
{ }

} // smart_home