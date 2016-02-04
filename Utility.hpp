#pragma once

#include <algorithm>

namespace Gungi
{
    struct 2D_Indices
    {
        size_t x,y; 
    }

    struct 3D_Indices
    {
      size_t x, y, z;  
    };

    size_t coorToIndex(const size_t& x, const size_t& y, const size_t& length)
    {
        return y + x * length;
    }

    size_t coorToIndex(const 2D_Indices& pt, const size_t& length)
    {
        return idx.y + x * length; 
    }

    size_t coorToIndex(const size_t& x, const size_t& y, const size_t& z, const size_t& width, const size_t& length)
    {
        return (z * width * length) + (y * width) + x;
    }

    size_t coorToIndex(const 3D_Indices& idx, const size_t& width, const size_t& length)
    {
        return (idx.z * width * length) + (idx.y * width) + idx.x;
    }
}
