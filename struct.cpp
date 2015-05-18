#pragma once
#include "struct.h"

std::string IntToStr(int x)
{
    std::stringstream r;
    r << x;
    return r.str();
}

bool allTrue(bool x[], int Size)
{
    for(int i = 0; i < Size; i++)
    {
        if(x[i] == false)
            return false;
    }
    return true;
}
