#include <iostream>

#include "cat.hpp"
#include "i_cat.hpp"
#include "common_utils.hpp"

namespace smart_home
{

void Cat::Meow () const NOEXCEPTIONS
{
    std::cout << "meow!" << std::endl;
}

} // smart_home

extern "C"
{
    SharedPtr<smart_home::ICat> MakeCat ()
    {
        return SharedPtr<smart_home::ICat>(new smart_home::Cat());
    }
}