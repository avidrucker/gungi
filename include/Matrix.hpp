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

#include <MatrixUtility.hpp>

namespace Gungi
{
    template <class T, class SizeType>
    class Matrix2 
    {
        using Ref        = T&;
        using ConstRef   = const T&;
        using PtrType    = T*;
        using AccessType = Point2<SizeType>;

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
            
        private:
            SizeType _width, _length;
            PtrType _matrix;
    };

    template <class T, class SizeType>
    class Matrix3 
    {
        using Ref      = T&;
        using ConstRef = const T&;
        using PtrType  = T*;
        using AccessType = Point3<SizeType>;

        public:
            Matrix3(const SizeType& width, const SizeType& depth, const SizeType& height);
            Matrix3(const SizeType& width, const SizeType& depth, 
                    const SizeType& height, ConstRef initValue);
            ~Matrix3();
            SizeType getWidth() const;
            SizeType getDepth() const;
            SizeType getHeight() const;
            SizeType getSize() const;
            Ref operator [] (const SizeType& i);
            ConstRef operator [] (const SizeType& i) const;
            Ref operator [] (const AccessType& idx);
            ConstRef operator [] (const AccessType& idx) const;
            Ref operator () (const SizeType& x, const SizeType& z, const SizeType& y);
            ConstRef operator () (const SizeType& x, const SizeType& z, const SizeType& y) const;

        private:
            SizeType _width, _depth, _height;
            PtrType _matrix;
    };

    template <class T, class SizeType>
    Matrix2<T, SizeType>::Matrix2(const SizeType& width, const SizeType& length)
    : _width  (width)
    , _length (length)
    , _matrix (new T[width * length])
    {}

    template <class T, class SizeType>
    Matrix2<T, SizeType>::Matrix2(const SizeType& width, const SizeType& length, ConstRef initValue)
    : _width  (width)
    , _length (length)
    , _matrix (new T[width * length])
    {
        for (SizeType i = 0; i < getSize(); ++i)
            _matrix[i] = initValue;
    }

    template <class T, class SizeType>
    Matrix2<T, SizeType>::~Matrix2()
    {
        if (_matrix != nullptr)
        {
            delete [] _matrix;
            _matrix = nullptr;
        }
    }

    template <class T, class SizeType>
    SizeType Matrix2<T, SizeType>::getWidth() const
    {
        return _width;
    }

    template <class T, class SizeType>
    SizeType Matrix2<T, SizeType>::getLength() const
    {
        return _length;
    }

    template <class T, class SizeType>
    SizeType Matrix2<T, SizeType>::getSize() const
    {
        return _width * _length;
    }
    
    template <class T, class SizeType>
    typename Matrix2<T, SizeType>::Ref Matrix2<T, SizeType>::operator [] (const SizeType& i)
    {
        return _matrix[i];
    }

    template <class T, class SizeType>
    typename Matrix2<T, SizeType>::ConstRef Matrix2<T, SizeType>::operator [] 
        (const SizeType& i) const
    {
        return _matrix[i];
    }

    template <class T, class SizeType>
    typename Matrix2<T, SizeType>::Ref Matrix2<T, SizeType>::operator [] (const AccessType& idx)
    {
        return _matrix[coorToIndex(idx, _length)];
    }

    template <class T, class SizeType>
    typename Matrix2<T, SizeType>::ConstRef Matrix2<T, SizeType>::operator [] 
        (const AccessType& idx) const
    {
        return _matrix[coorToIndex(idx , _length)];
    }
    
    template <class T, class SizeType>
    typename Matrix2<T, SizeType>::Ref Matrix2<T, SizeType>::operator () 
        (const SizeType& x, const SizeType& y)
    {
        return _matrix[coorToIndex(x, y, _length)];
    }

    template <class T, class SizeType>
    typename Matrix2<T, SizeType>::ConstRef Matrix2<T, SizeType>::operator () 
        (const SizeType& x, const SizeType& y) const
    {
        return _matrix[coorToIndex(x, y, _length)];
    }

    template <class T, class SizeType>
    Matrix3<T, SizeType>::Matrix3
        (const SizeType& width, const SizeType& depth, const SizeType& height)
    : _width  (width)
    , _depth  (depth)
    , _height (height)
    , _matrix (new T[width * depth * height])
    {}

    template <class T, class SizeType>
    Matrix3<T, SizeType>::Matrix3
        (const SizeType& width, const SizeType& depth, const SizeType& height, ConstRef initValue)
    : _width  (width)
    , _depth  (depth)
    , _height (height)
    , _matrix (new T[width * depth * height])
    {
        for (SizeType i = 0u; i < getSize(); ++i)
            _matrix[i] = initValue;
    }

    template <class T, class SizeType>
    Matrix3<T, SizeType>::~Matrix3()
    {
        if (_matrix != nullptr)
        {
            delete [] _matrix;
            _matrix = nullptr;
        }
    }

    template <class T, class SizeType>
    SizeType Matrix3<T, SizeType>::getWidth() const
    {
        return _width;
    }

    template <class T, class SizeType>
    SizeType Matrix3<T, SizeType>::getDepth() const
    {
        return _depth;
    }

    template <class T, class SizeType>
    SizeType Matrix3<T, SizeType>::getHeight() const
    {
        return _height;
    }

    template <class T, class SizeType>
    SizeType Matrix3<T, SizeType>::getSize() const
    {
        return _width * _depth * _height;
    }

    template <class T, class SizeType>
    typename Matrix3<T, SizeType>::Ref Matrix3<T, SizeType>::operator [] (const SizeType& i)
    {
        return _matrix[i];
    }

    template <class T, class SizeType>
    typename Matrix3<T, SizeType>::ConstRef Matrix3<T, SizeType>::operator [] 
        (const SizeType& i) const
    {
        return _matrix[i];
    }

    template <class T, class SizeType>
    typename Matrix3<T, SizeType>::Ref Matrix3<T, SizeType>::operator [] 
        (const AccessType& idx)
    {
        return _matrix[coorToIndex(idx,_width,_depth)];
    }

    template <class T, class SizeType>
    typename Matrix3<T, SizeType>::ConstRef Matrix3<T, SizeType>::operator [] 
        (const AccessType& idx) const
    {
        return _matrix[coorToIndex(idx,_width,_depth)];
    }

    template <class T, class SizeType>
    typename Matrix3<T, SizeType>::Ref Matrix3<T, SizeType>::operator () (const SizeType& x, 
            const SizeType& z, const SizeType& y)
    {
        return _matrix[coorToIndex(x,z,y,_width,_depth)];
    }
    
    template <class T, class SizeType>
    typename Matrix3<T, SizeType>::ConstRef Matrix3<T, SizeType>::operator ()  
        (const SizeType& x, const SizeType& z, const SizeType& y) const
    {
        return _matrix[coorToIndex(x,z,y,_width,_depth)];
    }
}
