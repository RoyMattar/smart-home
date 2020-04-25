#ifndef EVENT_TOPIC_HPP
#define EVENT_TOPIC_HPP

#include "common_utils.hpp"
#include "event.hpp"

namespace smart_home
{

class EventTopic
{
public:
    EventTopic (Event::Type const& a_type, Event::Location const& a_location) NOEXCEPTIONS;
    EventTopic (Event const& a_event) NOEXCEPTIONS;
    //EventTopic (EventTopic const& a_other) = default;
    //~EventTopic () = default;
    //EventTopic& operator= (EventTopic const& a_other) = default;

    Event::Type const& GetType () const NOEXCEPTIONS;
    Event::Location const& GetLocation () const NOEXCEPTIONS;
    Event::Location::Floor const& GetFloor () const NOEXCEPTIONS;
    Event::Location::Room const& GetRoom () const NOEXCEPTIONS;
    void Print () const NOEXCEPTIONS;

public:
    static const Event::Type ANY_TYPE;
    static const Event::Location ANY_LOCATION;
    static const Event::Location::Floor ANY_FLOOR;
    static const Event::Location::Room ANY_ROOM;

private:
    Event::Type m_type;
    Event::Location m_location;
};

inline bool operator== (EventTopic const& a_firstTopic, EventTopic const& a_secondTopic) NOEXCEPTIONS
{
    return a_firstTopic.GetType() == a_secondTopic.GetType()
        && a_firstTopic.GetLocation() == a_secondTopic.GetLocation();
}

inline Event::Type const& EventTopic::GetType () const NOEXCEPTIONS { return m_type; }
inline Event::Location const& EventTopic::GetLocation () const NOEXCEPTIONS { return m_location; }
inline Event::Location::Floor const& EventTopic::GetFloor () const NOEXCEPTIONS { return m_location.GetFloor(); }
inline Event::Location::Room const& EventTopic::GetRoom () const NOEXCEPTIONS { return m_location.GetRoom(); }

} // smart_home

#endif // EVENT_TOPIC_HPP