#include "Utility.hpp"

namespace Gungi
{
    size_t coorToIndex(const size_t& x, const size_t& y, const size_t& length)
    {
        return y + x * length;
    }

    size_t coorToIndex(const XY_Indices& idx, const size_t& length)
    {
        return idx.y + idx.x * length; 
    }

    size_t coorToIndex(const size_t& x, const size_t& y, const size_t& z, const size_t& width, const size_t& length)
    {
        return (z * width * length) + (y * width) + x;
    }

    size_t coorToIndex(const XYZ_Indices& idx, const size_t& width, const size_t& length)
    {
        return (idx.z * width * length) + (idx.y * width) + idx.x;
    }
}
