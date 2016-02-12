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

#include "Utility.hpp"

namespace Gungi
{
    template <class T>
    class TwoDimMatrix 
    {
        public:
            TwoDimMatrix(const size_t& width, const size_t& length);
            TwoDimMatrix(const size_t& width, const size_t& length, const T& initValue);
            ~TwoDimMatrix();
            size_t getWidth() const;
            size_t getLength() const;
            size_t getSize() const;
            T& operator [] (const size_t& i);
            const T& operator [] (const size_t& i) const;
            T& operator [] (const XY_Indices& idx);
            const T& operator [] (const XY_Indices& idx) const;
            T& operator () (const size_t& x, const size_t& y);
            const T& operator () (const size_t& x, const size_t& y) const;
            
        protected:
            size_t _width, _length;
            T* _matrix;
    };

    template <class T>
    class ThreeDimMatrix 
    {
        public:
            ThreeDimMatrix(const size_t& width, const size_t& length, const size_t& height);
            ThreeDimMatrix(const size_t& width, const size_t& length, const size_t& height, const T& initValue);
            ~ThreeDimMatrix();
            size_t getWidth() const;
            size_t getLength() const;
            size_t getHeight() const;
            size_t getSize() const;
            T& operator [] (const size_t& i);
            const T& operator [] (const size_t& i) const;
            T& operator [] (const XYZ_Indices& idx);
            const T& operator [] (const XYZ_Indices& idx) const;
            T& operator () (const size_t& x, const size_t& y, const size_t& z);
            const T& operator () (const size_t& x, const size_t& y, const size_t& z) const;

        protected:
            size_t _width, _length, _height;
            T* _matrix;
    };
}

#include "Matrix.cpp"
