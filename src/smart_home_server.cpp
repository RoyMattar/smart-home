#include <sys/sysinfo.h> // get_nprocs()

#include "smart_home_server.hpp"
#include "cyclic_tag.hpp"

namespace smart_home
{

int SmartHomeServer::hardwareCores () NOEXCEPTIONS
{
    return get_nprocs();
}

CyclicTag::TagType SmartHomeServer::defaultNumOfTags (unsigned char a_tagFactor) NOEXCEPTIONS
{
    return hardwareCores() * a_tagFactor;
}

} // smart_home