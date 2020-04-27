#ifndef SMART_HOME_SERVER_HPP
#define SMART_HOME_SERVER_HPP

#include <string>
#include <cstddef> // size_t

#include "common_utils.hpp"
#include "cyclic_tag.hpp"

namespace smart_home
{

class SmartHomeServer : private advcpp::Uncopyable
{
public:
    SmartHomeServer (std::string const& a_configFile, unsigned char a_parallelFactor,
                     size_t a_publicationBandwidth, size_t a_distributionBandwidth);
    //~SmartHomeServer () = default;

    void Go ();

private:
    static int hardwareCores () NOEXCEPTIONS;
    static CyclicTag::TagType numOfTags (unsigned char a_tagFactor) NOEXCEPTIONS;

private:
    std::string m_configFile;
    CyclicTag::TagType m_numOfTags;
    size_t m_publicationBandwidth;
    size_t m_distributionBandwidth;
};

} // smart_home

#endif // SMART_HOME_SERVER_HPP