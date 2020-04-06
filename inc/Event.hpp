#ifndef EVENT_HPP
#define EVENT_HPP

#include <string>
#include "common_utils.hpp"

namespace SmartHome
{

class Event
{
public:
    typedef std::string EventType;
    typedef std::string EventTimestamp;
    typedef std::string EventPayload;
    typedef std::string EventLocation;

    Event ();
    Event (const EventType& a_type, const EventTimestamp& a_timestamp
        , const EventPayload& a_payload, const EventLocation& a_location);
    Event (const std::string& a_str);
    //Event (const Event& a_other) = default;
    //~Event () = default;
    //Event& operator= (const Event& a_other) = default;

    std::string ToStr () const NOEXCEPTIONS;

    EventType GetType () const NOEXCEPTIONS;
    EventTimestamp GetTimestamp () const NOEXCEPTIONS;
    EventPayload GetPayload () const NOEXCEPTIONS;
    EventLocation GetLocation () const NOEXCEPTIONS;

    void Print () const NOEXCEPTIONS;

private:
    EventType m_type;
    EventTimestamp m_timestamp;
    EventPayload m_payload;
    EventLocation m_location;
};

inline Event::EventType Event::GetType () const NOEXCEPTIONS
{
    return m_type;
}

inline Event::EventTimestamp Event::GetTimestamp () const NOEXCEPTIONS
{
    return m_timestamp;
}

inline Event::EventPayload Event::GetPayload () const NOEXCEPTIONS
{
    return m_payload;
}

inline Event::EventLocation Event::GetLocation () const NOEXCEPTIONS
{
    return m_location;
}

} // SmartHome

#endif // EVENT_HPP