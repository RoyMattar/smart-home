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
           , Payload const& a_payload, Location const& a_location) NOEXCEPTIONS;
    //Event (const Event& a_other) = default;
    //~Event () = default;
    //Event& operator= (const Event& a_other) = default;

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
        
    private:
        Floor m_floor;
        Room m_room;
    };

private:
    Type m_type;
    Timestamp m_timestamp;
    Payload m_payload;
    Location m_location;
};

inline bool operator== (Event::Location const& a_firstLocation, Event::Location const& a_secondLocation) NOEXCEPTIONS
{
    return a_firstLocation.GetFloor() == a_secondLocation.GetFloor()
        && a_firstLocation.GetRoom() == a_secondLocation.GetRoom();
}

inline bool operator== (Event const& a_firstEvent, Event const& a_secondEvent) NOEXCEPTIONS
{
    return a_firstEvent.GetType() == a_secondEvent.GetType()
        && a_firstEvent.GetTimestamp() == a_secondEvent.GetTimestamp()
        && a_firstEvent.GetPayload() == a_secondEvent.GetPayload()
        && a_firstEvent.GetLocation() == a_secondEvent.GetLocation();
}

inline Event::Type const& Event::GetType () const NOEXCEPTIONS { return m_type; }
inline Event::Timestamp const& Event::GetTimestamp () const NOEXCEPTIONS { return m_timestamp; }
inline Event::Payload const& Event::GetPayload () const NOEXCEPTIONS { return m_payload; }
inline Event::Location const& Event::GetLocation () const NOEXCEPTIONS { return m_location; }

inline Event::Location::Floor const& Event::Location::GetFloor () const { return m_floor; }
inline Event::Location::Room const& Event::Location::GetRoom () const { return m_room; }

} // SmartHome

#endif // EVENT_HPP