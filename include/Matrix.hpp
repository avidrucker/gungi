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
    class Matrix2 
    {
        using SizeType   = size_t;
        using Ref        = T&;
        using ConstRef   = const T&;
        using PtrType    = T*;
        using AccessType = Point;

        public:
            Matrix2(const SizeType& width, const SizeType& length);
            Matrix2(const SizeType& width, const SizeType& length, ConstRef initValue);
            ~Matrix2();
            SizeType getWidth() const;
            SizeType getLength() const;
            SizeType getSize() const;
            Ref operator [] (const SizeType& i);
            ConstRef operator [] (const SizeType& i) const;
            Ref operator [] (const AccessType& idx);
            ConstRef operator [] (const AccessType& idx) const;
            Ref operator () (const SizeType& x, const SizeType& y);
            ConstRef operator () (const SizeType& x, const SizeType& y) const;
            
        protected:
            SizeType _width, _length;
            PtrType _matrix;
    };

    template <class T>
    class Matrix3 
    {
        using SizeType = size_t;
        using Ref      = T&;
        using ConstRef = const T&;
        using PtrType  = T*;
        using AccessType = Point3;

        public:
            Matrix3(const SizeType& width, const SizeType& length, const SizeType& height);
            Matrix3(const SizeType& width, const SizeType& length, 
                    const SizeType& height, ConstRef initValue);
            ~Matrix3();
            SizeType getWidth() const;
            SizeType getLength() const;
            SizeType getHeight() const;
            SizeType getSize() const;
            Ref operator [] (const SizeType& i);
            ConstRef operator [] (const SizeType& i) const;
            Ref operator [] (const AccessType& idx);
            ConstRef operator [] (const AccessType& idx) const;
            Ref operator () (const SizeType& x, const SizeType& y, const SizeType& z);
            ConstRef operator () (const SizeType& x, const SizeType& y, const SizeType& z) const;

        protected:
            SizeType _width, _length, _height;
            PtrType _matrix;
    };
}

#include "Matrix.cpp"
