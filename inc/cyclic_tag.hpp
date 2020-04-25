#ifndef CYCLIC_TAG_HPP
#define CYCLIC_TAG_HPP

namespace smart_home
{

class CyclicTag
{
public:
    typedef unsigned long TagType;

public:
    CyclicTag (TagType a_numOfTags);
    //CyclicTag (CyclicTag const& a_other) = default;
    //~CyclicTag () = default;
    //CyclicTag& operator= (CyclicTag const& a_other) = default;

    CyclicTag& operator++ ();
    CyclicTag operator++ (int);

    TagType const& GetCurrent () const;
    TagType const& GetMax () const;

private:
    TagType m_currentTag;
    TagType m_maxTag;
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

inline CyclicTag::TagType const& CyclicTag::GetCurrent () const { return m_currentTag; }
inline CyclicTag::TagType const& CyclicTag::GetMax () const { return m_maxTag; }

} // smart_home

#endif // CYCLIC_TAG_HPP