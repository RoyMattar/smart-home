#ifndef I_TAG_GETTER_HPP
#define I_TAG_GETTER_HPP

#include "common_utils.hpp"
#include "group_tag.hpp"

namespace smart_home
{

class ITagGetter
{
public:
    virtual ~ITagGetter ();

    virtual GroupTag GetTag () const NOEXCEPTIONS = 0;
};

inline ITagGetter::~ITagGetter () { }

} // smart_home

#endif // I_TAG_GETTER_HPP