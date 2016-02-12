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
