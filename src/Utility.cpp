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


    XYZ_Indices toXYZ(const XY_Indices& idx, const size_t& height)
    {
        XYZ_Indices res;
        res.x = idx.x;
        res.y = idx.y;
        res.z = height;
        return res;
    }

    XY_Indices toXY(const XYZ_Indices& idx)
    {
        XY_Indices res;
        res.x = idx.x;
        res.y = idx.y;
        return res;
    }
}
