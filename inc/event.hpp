#ifndef EVENT_HPP
#define EVENT_HPP

#include <string>
#include "common_utils.hpp"

namespace smart_home
{

class Event
{
public:
    typedef std::string Type;
    typedef std::string Timestamp;
    typedef std::string Payload;
    typedef std::string Location;

    //@brief constructor from event params: type, timestamp, payload & location
    Event (const Type& a_type, const Timestamp& a_timestamp
        , const Payload& a_payload, const Location& a_location);
    //Event (const Event& a_other) = default;
    //~Event () = default;
    //Event& operator= (const Event& a_other) = default;

    bool operator== (const Event& a_other) const NOEXCEPTIONS;

    //@brief returns event type
    Type GetType () const NOEXCEPTIONS;
    //@brief returns event timestamp
    Timestamp GetTimestamp () const NOEXCEPTIONS;
    //@brief returns event payload
    Payload GetPayload () const NOEXCEPTIONS;
    //@brief returns event location
    Location GetLocation () const NOEXCEPTIONS;
    //@brief prints event to stdout
    void Print () const NOEXCEPTIONS;

    //static void FromBuffer (const char* a_buffer);
    //static std::string ToStr () const NOEXCEPTIONS;

private:
    Type m_type;
    Timestamp m_timestamp;
    Payload m_payload;
    Location m_location;
};

inline bool Event::operator== (const Event& a_other) const NOEXCEPTIONS
{
    return m_type == a_other.m_type
        && m_timestamp == a_other.m_timestamp
        && m_payload == a_other.m_payload
        && m_location = a_other.m_location;
}

inline Event::Type Event::GetType () const NOEXCEPTIONS
{
    return m_type;
}

inline Event::Timestamp Event::GetTimestamp () const NOEXCEPTIONS
{
    return m_timestamp;
}

inline Event::Payload Event::GetPayload () const NOEXCEPTIONS
{
    return m_payload;
}

inline Event::Location Event::GetLocation () const NOEXCEPTIONS
{
    return m_location;
} 

} // SmartHome

#endif // EVENT_HPP