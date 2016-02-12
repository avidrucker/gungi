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
    TwoDimMatrix<T>::TwoDimMatrix(const size_t& width, const size_t& length)
    : _width  (width)
    , _length (length)
    , _matrix (new T[width * length])
    {}

    template <class T>
    TwoDimMatrix<T>::TwoDimMatrix(const size_t& width, const size_t& length, const T& initValue)
    : _width  (width)
    , _length (length)
    , _matrix (new T[width * length])
    {
        for (size_t i = 0; i < getSize(); ++i)
            _matrix[i] = initValue;
    }

    template <class T>
    TwoDimMatrix<T>::~TwoDimMatrix()
    {
        if (_matrix != nullptr)
        {
            delete [] _matrix;
            _matrix = nullptr;
        }
    }

    template <class T>
    size_t TwoDimMatrix<T>::getWidth() const
    {
        return _width;
    }

    template <class T>
    size_t TwoDimMatrix<T>::getLength() const
    {
        return _length;
    }

    template <class T>
    size_t TwoDimMatrix<T>::getSize() const
    {
        return _width * _length;
    }
    
    template <class T>
    T& TwoDimMatrix<T>::operator [] (const size_t& i)
    {
        return _matrix[i];
    }

    template <class T>
    const T& TwoDimMatrix<T>::operator [] (const size_t& i) const
    {
        return _matrix[i];
    }

    template <class T>
    T& TwoDimMatrix<T>::operator [] (const XY_Indices& idx)
    {
        return _matrix[coorToIndex(idx, _length)];
    }

    template <class T>
    const T& TwoDimMatrix<T>::operator [] (const XY_Indices& idx) const
    {
        return _matrix[coorToIndex(idx , _length)];
    }
    
    template <class T>
    T& TwoDimMatrix<T>::operator () (const size_t& x, const size_t& y)
    {
        return _matrix[coorToIndex(x, y, _length)];
    }

    template <class T>
    const T& TwoDimMatrix<T>::operator () (const size_t& x, const size_t& y) const
    {
        return _matrix[coorToIndex(x, y, _length)];
    }
    template <class T>
    ThreeDimMatrix<T>::ThreeDimMatrix
        (const size_t& width, const size_t& length, const size_t& height)
    : _width  (width)
    , _length (length)
    , _height (height)
    , _matrix (new T[width * length * height])
    {}

    template <class T>
    ThreeDimMatrix<T>::ThreeDimMatrix
        (const size_t& width, const size_t& length, const size_t& height, const T& initValue)
    : _width  (width)
    , _length (length)
    , _height (height)
    , _matrix (new T[width * length * height])
    {
        for (size_t i = 0; i < getSize(); ++i)
            _matrix[i] = initValue;
    }

    template <class T>
    ThreeDimMatrix<T>::~ThreeDimMatrix()
    {
        if (_matrix != nullptr)
        {
            delete [] _matrix;
            _matrix = nullptr;
        }
    }

    template <class T>
    size_t ThreeDimMatrix<T>::getWidth() const
    {
        return _width;
    }

    template <class T>
    size_t ThreeDimMatrix<T>::getLength() const
    {
        return _length;
    }

    template <class T>
    size_t ThreeDimMatrix<T>::getHeight() const
    {
        return _height;
    }

    template <class T>
    size_t ThreeDimMatrix<T>::getSize() const
    {
        return _width * _length * _height;
    }

    template <class T>
    T& ThreeDimMatrix<T>::operator [] (const size_t& i)
    {
        return _matrix[i];
    }

    template <class T>
    const T& ThreeDimMatrix<T>::operator [] (const size_t& i) const
    {
        return _matrix[i];
    }

    template <class T>
    T& ThreeDimMatrix<T>::operator [] (const XYZ_Indices& idx)
    {
        return _matrix[coorToIndex(idx,_width,_length)];
    }

    template <class T>
    const T& ThreeDimMatrix<T>::operator [] (const XYZ_Indices& idx) const
    {
        return _matrix[coorToIndex(idx,_width,_length)];
    }

    template <class T>
    T& ThreeDimMatrix<T>::operator () (const size_t& x, const size_t& y, const size_t& z)
    {
        return _matrix[coorToIndex(x,y,z,_width,_length)];
    }

    template <class T>
    const T& ThreeDimMatrix<T>::operator ()  
        (const size_t& x, const size_t& y, const size_t& z) const
    {
        return _matrix[coorToIndex(x,y,z,_width,_length)];
    }

}
