#ifndef CYCLIC_TAG_HPP
#define CYCLIC_TAG_HPP

#include "group_tag.hpp"

namespace smart_home
{

class CyclicTag
{
public:
    explicit CyclicTag (GroupTag a_numOfTags);
    //CyclicTag (CyclicTag const& a_other) = default;
    //~CyclicTag () = default;
    //CyclicTag& operator= (CyclicTag const& a_other) = default;

    CyclicTag& operator++ ();
    CyclicTag operator++ (int);

    GroupTag const& GetCurrent () const;
    GroupTag const& GetMax () const;

private:
    GroupTag m_currentTag;
    GroupTag m_maxTag;
};

inline CyclicTag& CyclicTag::operator++ ()
{
    m_currentTag = (m_currentTag + 1) % m_maxTag;
    return *this;
}

inline CyclicTag CyclicTag::operator++ (int)
{
    CyclicTag temp = *this;
    m_currentTag = (m_currentTag + 1) % m_maxTag;
    return temp;
}

inline GroupTag const& CyclicTag::GetCurrent () const { return m_currentTag; }
inline GroupTag const& CyclicTag::GetMax () const { return m_maxTag; }

} // smart_home

#endif // CYCLIC_TAG_HPP