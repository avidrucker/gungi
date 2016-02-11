#pragma once

#include <algorithm>

namespace Gungi
{
    constexpr size_t INDEX_OVERFLOW = ~0; 

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

    XYZ_Indices toXYZ(const XY_Indices& idx, const size_t& height);
    XY_Indices toXY(const XYZ_Indices& idx);
}
