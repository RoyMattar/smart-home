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
    class Location;

public:
    //@brief constructor from event params: type, timestamp, payload & location
    Event (Type const& a_type, Timestamp const& a_timestamp
           , Payload const& a_payload, Location const& a_location);
    //Event (const Event& a_other) = default;
    //~Event () = default;
    //Event& operator= (const Event& a_other) = default;

    bool operator== (const Event& a_other) const NOEXCEPTIONS;

    //@brief returns event type
    Type const& GetType () const NOEXCEPTIONS;
    //@brief returns event timestamp
    Timestamp const& GetTimestamp () const NOEXCEPTIONS;
    //@brief returns event payload
    Payload const& GetPayload () const NOEXCEPTIONS;
    //@brief returns event location
    Location const& GetLocation () const NOEXCEPTIONS;
    //@brief prints event to stdout
    void Print () const NOEXCEPTIONS;

public:
    class Location
    {
    public:
        typedef std::string Floor;
        typedef std::string Room;

    public:
        Location (Floor const& a_floor, Room const& a_room);
        Floor const& GetFloor () const;
        Room const& GetRoom () const;

        bool operator== (const Location& a_other) const NOEXCEPTIONS;

    public:
        static const Floor ANY_FLOOR;
        static const Room ANY_ROOM;
    
    private:
        Floor m_floor;
        Room m_room;
    };

public:
    static const Type ANY_TYPE;

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
        && (m_location.GetFloor() == a_other.m_location.GetFloor()
        && m_location.GetRoom() == a_other.m_location.GetRoom());
}

inline Event::Type const& Event::GetType () const NOEXCEPTIONS
{
    return m_type;
}

inline Event::Timestamp const& Event::GetTimestamp () const NOEXCEPTIONS
{
    return m_timestamp;
}

inline Event::Payload const& Event::GetPayload () const NOEXCEPTIONS
{
    return m_payload;
}

inline Event::Location const& Event::GetLocation () const NOEXCEPTIONS
{
    return m_location;
} 

inline Event::Location::Floor const& Event::Location::GetFloor () const
{
    return m_floor;
}

inline Event::Location::Room const& Event::Location::GetRoom () const
{
    return m_room;
}

} // SmartHome

#endif // EVENT_HPP