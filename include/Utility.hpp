#pragma once

#include <algorithm>

namespace Gungi
{
    struct XY_Indices
    {
        size_t x,y; 
    };

    struct XYZ_Indices
    {
        size_t x, y, z;  
    };

    size_t coorToIndex(const size_t& x, const size_t& y, const size_t& length);
    size_t coorToIndex(const XY_Indices& idx, const size_t& length);
    size_t coorToIndex(const size_t& x, const size_t& y, const size_t& z, const size_t& width, const size_t& length);
    size_t coorToIndex(const XYZ_Indices& idx, const size_t& width, const size_t& length);
}
