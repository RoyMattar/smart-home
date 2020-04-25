#ifndef I_TAGGED_HPP
#define I_TAGGED_HPP

#include "common_utils.hpp"
#include "group_tag.hpp"

namespace smart_home
{

class ITagged
{
public:
    virtual ~ITagged ();

    virtual GroupTag GetTag () const NOEXCEPTIONS = 0;
};

inline ITagged::~ITagged () { }

} // smart_home

#endif // I_TAGGED_HPP