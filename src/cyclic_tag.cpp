#include "cyclic_tag.hpp"

namespace smart_home
{

CyclicTag::CyclicTag (TagType a_firstTag, TagType a_numOfTags)
    : m_currentTag(a_firstTag)
    , m_maxTag(a_firstTag + a_numOfTags)
{ }

} // smart_home