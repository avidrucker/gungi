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
    using PointSize = size_t;

    constexpr PointSize UNBOUND = ~0;

    struct Point
    {
        Point()
        : x (UNBOUND) 
        , y (UNBOUND) 
        {}

        Point(const PointSize& a, const PointSize& b)
        : x (a)
        , y (b)
        {}

        PointSize x, y;
    };

    struct Point3
    {
        Point3()
        : x (UNBOUND) 
        , y (UNBOUND) 
        , z (UNBOUND) 
        {}

        Point3(const PointSize& a, const PointSize& b, const PointSize& c)
        : x (a)
        , y (b)
        , z (c)
        {}

        PointSize x, y, z;
    };

    size_t coorToIndex(const PointSize& x, const PointSize& y, const PointSize& length);
    size_t coorToIndex(const Point& idx, const PointSize& length);
    size_t coorToIndex(const PointSize& x, const PointSize& y, const PointSize& z, 
            const PointSize& width, const PointSize& length);
    size_t coorToIndex(const Point3& idx, const PointSize& width, const PointSize& length);

    Point3 toXYZ(const Point& idx, const PointSize& height);
    Point toXY(const Point3& idx);

    bool operator < (const Point& lhs, const Point& rhs);
    bool operator < (const Point3& lhs, const Point3& rhs);
    bool operator == (const Point& lhs, const Point& rhs);
    bool operator == (const Point3& lhs, const Point3& rhs);
}
