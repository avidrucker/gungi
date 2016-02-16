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

#include <Utility.hpp>
#include <MatrixManip.hpp>

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

        protected:
            SizeType _width, _depth, _height;
            PtrType _matrix;
    };

    template <class T>
    Matrix2<T>::Matrix2(const SizeType& width, const SizeType& length)
    : _width  (width)
    , _length (length)
    , _matrix (new T[width * length])
    {}

    template <class T>
    Matrix2<T>::Matrix2(const SizeType& width, const SizeType& length, ConstRef initValue)
    : _width  (width)
    , _length (length)
    , _matrix (new T[width * length])
    {
        for (SizeType i = 0; i < getSize(); ++i)
            _matrix[i] = initValue;
    }

    template <class T>
    Matrix2<T>::~Matrix2()
    {
        if (_matrix != nullptr)
        {
            delete [] _matrix;
            _matrix = nullptr;
        }
    }

    template <class T>
    typename Matrix2<T>::SizeType Matrix2<T>::getWidth() const
    {
        return _width;
    }

    template <class T>
    typename Matrix2<T>::SizeType Matrix2<T>::getLength() const
    {
        return _length;
    }

    template <class T>
    typename Matrix2<T>::SizeType Matrix2<T>::getSize() const
    {
        return _width * _length;
    }
    
    template <class T>
    typename Matrix2<T>::Ref Matrix2<T>::operator [] (const SizeType& i)
    {
        return _matrix[i];
    }

    template <class T>
    typename Matrix2<T>::ConstRef Matrix2<T>::operator [] (const SizeType& i) const
    {
        return _matrix[i];
    }

    template <class T>
    typename Matrix2<T>::Ref Matrix2<T>::operator [] (const AccessType& idx)
    {
        return _matrix[coorToIndex(idx, _length)];
    }

    template <class T>
    typename Matrix2<T>::ConstRef Matrix2<T>::operator [] (const AccessType& idx) const
    {
        return _matrix[coorToIndex(idx , _length)];
    }
    
    template <class T>
    typename Matrix2<T>::Ref Matrix2<T>::operator () (const SizeType& x, const SizeType& y)
    {
        return _matrix[coorToIndex(x, y, _length)];
    }

    template <class T>
    typename Matrix2<T>::ConstRef Matrix2<T>::operator () (const SizeType& x, const SizeType& y) const
    {
        return _matrix[coorToIndex(x, y, _length)];
    }

    template <class T>
    Matrix3<T>::Matrix3
        (const SizeType& width, const SizeType& depth, const SizeType& height)
    : _width  (width)
    , _depth  (depth)
    , _height (height)
    , _matrix (new T[width * depth * height])
    {}

    template <class T>
    Matrix3<T>::Matrix3
        (const SizeType& width, const SizeType& depth, const SizeType& height, ConstRef initValue)
    : _width  (width)
    , _depth  (depth)
    , _height (height)
    , _matrix (new T[width * depth * height])
    {
        for (SizeType i = 0u; i < getSize(); ++i)
            _matrix[i] = initValue;
    }

    template <class T>
    Matrix3<T>::~Matrix3()
    {
        if (_matrix != nullptr)
        {
            delete [] _matrix;
            _matrix = nullptr;
        }
    }

    template <class T>
    typename Matrix3<T>::SizeType Matrix3<T>::getWidth() const
    {
        return _width;
    }

    template <class T>
    typename Matrix3<T>::SizeType Matrix3<T>::getDepth() const
    {
        return _depth;
    }

    template <class T>
    typename Matrix3<T>::SizeType Matrix3<T>::getHeight() const
    {
        return _height;
    }

    template <class T>
    typename Matrix3<T>::SizeType Matrix3<T>::getSize() const
    {
        return _width * _depth * _height;
    }

    template <class T>
    typename Matrix3<T>::Ref Matrix3<T>::operator [] (const SizeType& i)
    {
        return _matrix[i];
    }

    template <class T>
    typename Matrix3<T>::ConstRef Matrix3<T>::operator [] (const SizeType& i) const
    {
        return _matrix[i];
    }

    template <class T>
    typename Matrix3<T>::Ref Matrix3<T>::operator [] (const AccessType& idx)
    {
        return _matrix[coorToIndex(idx,_width,_depth)];
    }

    template <class T>
    typename Matrix3<T>::ConstRef Matrix3<T>::operator [] (const AccessType& idx) const
    {
        return _matrix[coorToIndex(idx,_width,_depth)];
    }

    template <class T>
    typename Matrix3<T>::Ref Matrix3<T>::operator () (const SizeType& x, 
            const SizeType& z, const SizeType& y)
    {
        return _matrix[coorToIndex(x,z,y,_width,_depth)];
    }
    
    template <class T>
    typename Matrix3<T>::ConstRef Matrix3<T>::operator ()  
        (const SizeType& x, const SizeType& z, const SizeType& y) const
    {
        return _matrix[coorToIndex(x,z,y,_width,_depth)];
    }
}
