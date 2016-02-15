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

#include "Matrix.hpp"

namespace Gungi
{

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
        (const SizeType& width, const SizeType& length, const SizeType& height)
    : _width  (width)
    , _length (length)
    , _height (height)
    , _matrix (new T[width * length * height])
    {}

    template <class T>
    Matrix3<T>::Matrix3
        (const SizeType& width, const SizeType& length, const SizeType& height, ConstRef initValue)
    : _width  (width)
    , _length (length)
    , _height (height)
    , _matrix (new T[width * length * height])
    {
        for (SizeType i = 0; i < getSize(); ++i)
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
    typename Matrix3<T>::SizeType Matrix3<T>::getLength() const
    {
        return _length;
    }

    template <class T>
    typename Matrix3<T>::SizeType Matrix3<T>::getHeight() const
    {
        return _height;
    }

    template <class T>
    typename Matrix3<T>::SizeType Matrix3<T>::getSize() const
    {
        return _width * _length * _height;
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
        return _matrix[coorToIndex(idx,_width,_length)];
    }

    template <class T>
    typename Matrix3<T>::ConstRef Matrix3<T>::operator [] (const AccessType& idx) const
    {
        return _matrix[coorToIndex(idx,_width,_length)];
    }

    template <class T>
    typename Matrix3<T>::Ref Matrix3<T>::operator () (const SizeType& x, const SizeType& y, const SizeType& z)
    {
        return _matrix[coorToIndex(x,y,z,_width,_length)];
    }
    
    template <class T>
    typename Matrix3<T>::ConstRef Matrix3<T>::operator ()  
        (const SizeType& x, const SizeType& y, const SizeType& z) const
    {
        return _matrix[coorToIndex(x,y,z,_width,_length)];
    }
}
