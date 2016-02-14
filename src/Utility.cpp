/*
 * Copyright 2016 Fermin, Yaneury <fermin.yaneury@gmail.com>
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "Utility.hpp"

namespace Gungi
{
    size_t coorToIndex(const size_t& x, const size_t& y, const size_t& length)
    {
        return y + x * length;
    }

    size_t coorToIndex(const Point& idx, const size_t& length)
    {
        return idx.y + idx.x * length; 
    }

    size_t coorToIndex(const size_t& x, const size_t& y, const size_t& z, const size_t& width, const size_t& length)
    {
        return (z * width * length) + (y * width) + x;
    }

    size_t coorToIndex(const Point3& idx, const size_t& width, const size_t& length)
    {
        return (idx.z * width * length) + (idx.y * width) + idx.x;
    }


    Point3 toXYZ(const Point& idx, const size_t& height)
    {
        return Point3(idx.x, idx.y, height);
    }

    Point toXY(const Point3& idx)
    {
        return Point(idx.x, idx.y);
    }

    bool operator < (const Point& lhs, const Point& rhs)
    {
        if (lhs.x < rhs.x)
            return true;

        if (rhs.x < lhs.x)
            return false;

        return lhs.y < rhs.y;
    }

    bool operator < (const Point3& lhs, const Point3& rhs)
    {
        if (lhs.x < rhs.x)
            return true;

        if (rhs.x < lhs.x)
            return false;

        if (lhs.y < rhs.y)
            return true;

        if (rhs.y < lhs.y)
            return false;

        return lhs.z < rhs.z;
    }
}
