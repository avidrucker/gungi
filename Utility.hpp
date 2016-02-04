#pragma once

namespace Gungi
{
    size_t coorToIndex(const size_t& x, const size_t& y, const size_t& z, const size_t& width, const size_t& length)
    {
        return (z * width * length) + (y * width) + x;
    }

    struct indices
    {
      size_t x, y, z;  
    };
}
