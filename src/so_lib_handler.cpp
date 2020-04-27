#include <stdexcept> // std::exception
#include <string>
#include <dlfcn.h>

#include "so_lib_handler.hpp"
#include "common_utils.hpp"

namespace advcpp
{

struct DLOpenExc : public std::exception
{
    DLOpenExc (std::string const& a_dlerror)
        : m_what("dlopen() failed: " + a_dlerror)
    { }

    ~DLOpenExc () NOEXCEPTIONS
    { }

    virtual const char* what () const NOEXCEPTIONS
    {
        return m_what.c_str();
    }

    std::string m_what;
};

DLSymExc::DLSymExc (std::string const& a_dlerror)
    : m_what("dlsym() failed: " + a_dlerror)
{ }

DLSymExc::~DLSymExc () NOEXCEPTIONS
{ }

const char* DLSymExc::what () const NOEXCEPTIONS
{
    return m_what.c_str();
}

SOLibHandler::SOLibHandler (const char* a_fileName, int a_flags)
{
    m_handle = dlopen(a_fileName, a_flags);
    if (m_handle == 0)
    {
        throw DLOpenExc(dlerror());
    }
}

SOLibHandler::~SOLibHandler () NOEXCEPTIONS
{
    dlclose(m_handle);
}

} // advcpp