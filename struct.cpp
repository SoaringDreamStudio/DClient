#pragma once
#include "struct.h"

std::string IntToStr(int x)
{
    std::stringstream r;
    r << x;
    return r.str();
}

