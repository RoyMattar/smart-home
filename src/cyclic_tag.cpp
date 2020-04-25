#include "cyclic_tag.hpp"

namespace smart_home
{

CyclicTag::CyclicTag (TagType a_numOfTags)
    : m_currentTag(0)
    , m_maxTag(a_numOfTags)
{ }

} // smart_home