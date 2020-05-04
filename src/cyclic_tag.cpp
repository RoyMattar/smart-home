#include "cyclic_tag.hpp"
#include "group_tag.hpp"

namespace smart_home
{

CyclicTag::CyclicTag (GroupTag a_numOfTags)
    : m_currentTag(0)
    , m_numOfTags(a_numOfTags)
{ }

} // smart_home