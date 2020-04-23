#ifndef SMART_HOME_SERVER_HPP
#define SMART_HOME_SERVER_HPP

#include "common_utils.hpp"
#include "cyclic_tag.hpp"

namespace smart_home
{

class SmartHomeServer
{
public:

private:
    static int hardwareCores () NOEXCEPTIONS;
    static CyclicTag::TagType defaultNumOfTags (unsigned char a_tagFactor) NOEXCEPTIONS;
};

} // smart_home

#endif // SMART_HOME_SERVER_HPP