#ifndef AGENT_INFO_HPP
#define AGENT_INFO_HPP

#include <string>

#include "event.hpp"

namespace smart_home
{

class AgentInfo
{
public:
    typedef std::string DeviceID;
    typedef std::string DeviceType;
    typedef Event::Location DeviceLocation; // TODO: separate Location from Event, into EventLocation
    typedef std::string AgentLog;
    typedef std::string AgentConfig;

public:
    AgentInfo (DeviceID const& a_deviceID, DeviceType const& a_deviceType,
               DeviceLocation const& a_deviceLocation,
               AgentLog const& a_agentLog, AgentConfig const& a_agentConfig) NOEXCEPTIONS;
    //AgentInfo (AgentInfo const& a_other) = default;
    //~AgentInfo () = default;
    //AgentInfo& operator= (AgentInfo const& a_other) = default;

    DeviceID const& GetID () const NOEXCEPTIONS;
    DeviceType const& GetType () const NOEXCEPTIONS;
    DeviceLocation const& GetLocation () const NOEXCEPTIONS;
    AgentLog const& GetLog () const NOEXCEPTIONS;
    AgentConfig const& GetConfig () const NOEXCEPTIONS;

private:
    DeviceID m_deviceID;
    DeviceType m_deviceType;
    DeviceLocation m_deviceLocation;
    AgentLog m_agentLog;
    AgentConfig m_agentConfig;
};

inline AgentInfo::DeviceID const& AgentInfo::GetID () const NOEXCEPTIONS { return m_deviceID; }
inline AgentInfo::DeviceType const& AgentInfo::GetType () const NOEXCEPTIONS { return m_deviceType; }
inline AgentInfo::DeviceLocation const& AgentInfo::GetLocation () const NOEXCEPTIONS { return m_deviceLocation; }
inline AgentInfo::AgentLog const& AgentInfo::GetLog () const NOEXCEPTIONS { return m_agentLog; }
inline AgentInfo::AgentConfig const& AgentInfo::GetConfig () const NOEXCEPTIONS { return m_agentConfig; }

} // smart_home

#endif // AGENT_INFO_HPP