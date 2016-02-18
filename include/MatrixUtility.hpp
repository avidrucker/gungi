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

#pragma once

#include <algorithm>

namespace Gungi
{
    template <class SizeType>
    struct Point3;

    template <class SizeType>
    struct Point2
    {
        Point2(const SizeType& a, const SizeType& b)
        : x (a)
        , y (b)
        {}

        Point2(const Point3<SizeType>& pt3)
        : x (pt3.x)
        , y (pt3.z)
        {}

        SizeType x, y;
    };

    template <class SizeType>
    struct Point3
    {
        Point3(const SizeType& a, const SizeType& b, const SizeType& c)
        : x (a)
        , z (c)
        , y (b)
        {}

        Point3(const Point2<SizeType>& pt)
        : x (pt.x)
        , z (pt.y)
        , y (0)
        {}

        SizeType x, z, y;
    };

    template <class SizeType>
    SizeType coorToIndex(const SizeType& x, const SizeType& y, const SizeType& length)
    {
        return y + x * length;
    }

    template <class SizeType>
    SizeType coorToIndex(const Point2<SizeType>& idx, const SizeType& length)
    {
        return idx.y + idx.x * length; 
    }

    template <class SizeType>
    SizeType coorToIndex(const SizeType& x, const SizeType& z, const SizeType& y, 
            const SizeType& width, const SizeType& depth)
    {
        return (y * width * depth) + (z * width) + y;
    }

    template <class SizeType>
    SizeType coorToIndex(const Point3<SizeType>& idx, const SizeType& width, const SizeType& depth)
    {
        return (idx.y * width * depth) + (idx.z * width) + idx.x;
    }

    template <class SizeType>
    Point3<SizeType> toXYZ(const Point2<SizeType>& idx, const SizeType& height)
    {
        return Point3<SizeType>(idx.x, idx.y, height);
    }

    template <class SizeType>
    Point2<SizeType> toXY(const Point3<SizeType>& idx)
    {
        return Point2<SizeType>(idx.x, idx.z);
    }
    
    template <class SizeType>
    bool operator < (const Point2<SizeType>& lhs, const Point2<SizeType>& rhs)
    {
        if (lhs.x < rhs.x)
            return true;

        if (rhs.x < lhs.x)
            return false;

        return lhs.y < rhs.y;
    }

    template <class SizeType>
    bool operator < (const Point3<SizeType>& lhs, const Point3<SizeType>& rhs)
    {
        if (lhs.x < rhs.x)
            return true;

        if (rhs.x < lhs.x)
            return false;
        
        if (lhs.z < rhs.z)
            return true;

        if (rhs.z < lhs.z)
            return false;

        return lhs.y < rhs.y;
    }

    template <class SizeType>
    bool operator == (const Point2<SizeType>& lhs, const Point2<SizeType>& rhs)
    {
        return lhs.x == rhs.x && lhs.y == rhs.y; 
    }

    template <class SizeType>
    bool operator == (const Point3<SizeType>& lhs, const Point3<SizeType>& rhs)
    {
        return lhs.x == rhs.x && lhs.z == rhs.z && lhs.y == rhs.y;
    }
}
