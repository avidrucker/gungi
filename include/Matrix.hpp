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

#include <memory>

#include <MatrixUtility.hpp>

namespace Gungi
{
    /**
     * Matrix2 is a 2-dimensional matrix class. The coordinate system uses
     * standard x,y for marking it's points where x = cols and y = rows. To optimize
     * for size, the second template parameter takes a sizetype that stores the matrix
     * length (y or rows) and width (x or cols). Even though the matrix is stored on the heap,
     * it is a static container. Resizing is not possible. Future implementations will remedy
     * this.
     */
    template <class T, class SizeType>
    class Matrix2 
    {
        using Ref        = T&;
        using ConstRef   = const T&;
        using PtrType    = std::unique_ptr<T[]>;
        using AccessType = Point2<SizeType>;

        public:

            /**
             * This constructor will allocate a matrix with the given width and length.
             * @param width the width (x, or cols) of the matrix
             * @param length the length (y, or rows) of the matrix
             */
            Matrix2(const SizeType& width, const SizeType& length);

            /**
             * This constructor will allocate a matrix with the given width and length
             * and will initialize the matrix to the initValue parameter.
             * @param width the width (x, or cols) of the matrix
             * @param length the length (y, or rows) of the matrix
             * @param initValue the value to initialize all indices in the matrix to
             */
            Matrix2(const SizeType& width, const SizeType& length, ConstRef initValue);

            Matrix2(const Matrix2& rhs);

            Matrix2(Matrix2&& rhs);

            Matrix2& operator = (const Matrix2& rhs);

            Matrix2& operator = (Matrix2&& rhs);

            /**
             * This method returns the width(x, or cols) of the matrix.
             * @return the width of the matrix
             */
            SizeType getWidth() const;
            
            /**
             * This method returns the length(y, or rows) of the matrix. 
             * @return the length of the matrix
             */
            SizeType getLength() const;

            /**
             * This method will return the total size of the matrix. It is equivalent
             * to retrieving the value from getWidth() * getLength().
             * @return the size of the matrix
             */
            SizeType getSize() const;

            /**
             * This operator overload accesses the ref to the type using the index. Since
             * the matrix is stored as a single array, this serves as a method to access the array
             * if the user wants to override the functionality of a matrix.
             * @param i index to access element in the array
             * @return the reference to the object at that index
             */
            Ref operator [] (const SizeType& i);

            /**
             * This returns a const reference to the object at the index.
             * @param i index to access element in the array
             * @return the const reference to the object at that index
             */
            ConstRef operator [] (const SizeType& i) const;

            /**
             * This returns a reference using the convenience AccessType which is a 
             * Point2<SizeType>. 
             * @param idx index in the form of x,z,y
             * @return the reference to the object at that index
             */
            Ref operator [] (const AccessType& idx);

            /**
             * This returns a const reference using the convenience AccessType which is a 
             * Point2<SizeType>. 
             * @param idx index in the form of x,z,y
             * @return the const reference to the object at that index
             */
            ConstRef operator [] (const AccessType& idx) const;

            /**
             * This returns a reference to the object at the given x,y point.
             * @param x the x index of the object
             * @param y the y index of the object
             * @return the reference to the object at that x,y point.
             */
            Ref operator () (const SizeType& x, const SizeType& y);

            /**
             * This returns a const reference to the object at the given x,y point.
             * @param x the x index of the object
             * @param y the y index of the object
             * @return the const reference to the object at that x,y point.
             */
            ConstRef operator () (const SizeType& x, const SizeType& y) const;
            
        private:
            SizeType _width; /**< The width of the matrix. */
            SizeType _length; /**<  The length of the matrix. */
            PtrType _matrix; /**< The matrix. */
    };

    /**
     * Matrix3 is a 3-dimensional matrix class. The coordinate system uses
     * standard x,z,y for marking it's points where x = width, z = depth, and y = height. 
     * To optimize for size, the second template parameter takes a sizetype that stores the matrix
     * width, depth, and height. Even though the matrix is stored on the heap,
     * it is a static container. Resizing is not possible. Future implementations will remedy
     * this.
     */
    template <class T, class SizeType>
    class Matrix3 
    {
        using Ref      = T&;
        using ConstRef = const T&;
        using PtrType  = std::unique_ptr<T[]>;
        using AccessType = Point3<SizeType>;

        public:

            /**
             * This constructor will instatiate a 3-dimensional matrix with the given width,
             * depth and height.
             * @param width the width of the matrix
             * @param depth the depth of the matrix
             * @param height the height of the matrix
             */
            Matrix3(const SizeType& width, const SizeType& depth, const SizeType& height);

            /**
             * This constructor will instatiate a 3-dimensional matrix with the given width,
             * depth and height. It will also initialize the matrix to passed in value.
             * @param width the width of the matrix
             * @param depth the depth of the matrix
             * @param height the height of the matrix
             * @param initValue desired initial value for the matrix
             */
            Matrix3(const SizeType& width, const SizeType& depth, 
                    const SizeType& height, ConstRef initValue);

            Matrix3(const Matrix3& rhs);

            Matrix3(Matrix3&& rhs);

            Matrix3& operator = (const Matrix3& rhs);

            Matrix3& operator = (Matrix3&& rhs);

            /**
             * This method returns the width(x) of the matrix.
             * @return the width of the matrix
             */
            SizeType getWidth() const;

            /**
             * This method returns the depth(z) of the matrix. 
             * @return the depth of the matrix
             */
            SizeType getDepth() const;

            /**
             * This method returns the height(y) of the matrix.
             * @return the height of the matrix
             */
            SizeType getHeight() const;

            /**
             * This method will return the total size of the matrix. It is equivalent
             * to retrieving the value from getWidth() * getDepth() * getHeight().
             * @return the size of the matrix
             */
            SizeType getSize() const;

            /**
             * This operator overload accesses the ref to the type using the index. Since
             * the matrix is stored as a single array, this serves as a method to access the array
             * if the user wants to override the functionality of a matrix.
             * @param i index to access element in the array
             * @return the reference to the object at that index
             */
            Ref operator [] (const SizeType& i);

            /**
             * This returns a const reference to the object at the index.
             * @param i index to access element in the array
             * @return the const reference to the object at that index
             */
            ConstRef operator [] (const SizeType& i) const;

            /**
             * This returns a reference using the convenience AccessType which is a 
             * Point3<SizeType>. 
             * @param idx index in the form of x,z,y
             * @return the reference to the object at that index
             */
            Ref operator [] (const AccessType& idx);

            /**
             * This returns a const reference using the convenience AccessType which is a 
             * Point3<SizeType>. 
             * @param idx index in the form of x,z,y
             * @return the const reference to the object at that index
             */
            ConstRef operator [] (const AccessType& idx) const;

            /**
             * This returns a reference to the object at the given x,z,y point.
             * @param x the x index of the object
             * @param z the z index of the object
             * @param y the y index of the object
             * @return the reference to the object at that x,z,y point.
             */
            Ref operator () (const SizeType& x, const SizeType& z, const SizeType& y);

            /**
             * This returns a const reference to the object at the given x,y point.
             * @param x the x index of the object
             * @param z the z index of the object
             * @param y the y index of the object
             * @return the const reference to the object at that x,y point.
             */
            ConstRef operator () (const SizeType& x, const SizeType& z, const SizeType& y) const;

        private:
            SizeType _width; /**< The width of the matrix. */
            SizeType _depth; /**< The depth of the matrix. */
            SizeType _height; /**< The height of the matrix. */
            PtrType _matrix; /**< The matrix. */
    };

    template <class T, class SizeType>
    Matrix2<T, SizeType>::Matrix2(const SizeType& width, const SizeType& length)
    : _width  (width)
    , _length (length)
    , _matrix (std::make_unique<T[]>(width * length))
    {}

    template <class T, class SizeType>
    Matrix2<T, SizeType>::Matrix2(const SizeType& width, const SizeType& length, ConstRef initValue)
    : _width  (width)
    , _length (length)
    , _matrix (std::make_unique<T[]>(width * length))
    {
        for (SizeType i = 0; i < getSize(); ++i)
            _matrix[i] = initValue;
    }

    template <class T, class SizeType>
    Matrix2<T, SizeType>::Matrix2(const Matrix2& rhs)
    : _width  (rhs._width)
    , _length (rhs._length)
    , _matrix (std::move(rhs._matrix))
    {}

    template <class T, class SizeType>
    Matrix2<T, SizeType>::Matrix2(Matrix2&& rhs)
    : _width  (rhs._width)
    , _length (rhs._length)
    , _matrix (std::move(rhs._matrix))
    {}

    template <class T, class SizeType>
    Matrix2<T, SizeType>& Matrix2<T, SizeType>::operator = (const Matrix2& rhs)
    {
        _width  = rhs._width;
        _length = rhs._length;
        _matrix = std::move(rhs._matrix);
    }

    template <class T, class SizeType>
    Matrix2<T, SizeType>& Matrix2<T, SizeType>::operator = (Matrix2&& rhs)
    {
        _width  = rhs._width;
        _length = rhs._length;
        _matrix = std::move(rhs._matrix);
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
    , _matrix (std::make_unique<T[]>(width * depth * height))
    {}

    template <class T, class SizeType>
    Matrix3<T, SizeType>::Matrix3
        (const SizeType& width, const SizeType& depth, const SizeType& height, ConstRef initValue)
    : _width  (width)
    , _depth  (depth)
    , _height (height)
    , _matrix (std::make_unique<T[]>(width * depth * height))
    {
        for (SizeType i = 0u; i < getSize(); ++i)
            _matrix[i] = initValue;
    }

    template <class T, class SizeType>
    Matrix3<T, SizeType>::Matrix3(const Matrix3& rhs)
    : _width  (rhs._width)
    , _depth  (rhs._depth)
    , _height (rhs._height)
    , _matrix (std::move(rhs._matrix))
    {}

    template <class T, class SizeType>
    Matrix3<T, SizeType>::Matrix3(Matrix3&& rhs)
    : _width  (rhs._width)
    , _depth  (rhs._depth)
    , _height (rhs._height)
    , _matrix (std::move(rhs._matrix))
    {}

    template <class T, class SizeType>
    Matrix3<T, SizeType>& Matrix3<T, SizeType>::operator = (const Matrix3& rhs)
    {
        _width  = rhs._width;
        _depth  = rhs._depth;
        _height = rhs._height;
        _matrix = std::move(rhs._matrix);
    }

    template <class T, class SizeType>
    Matrix3<T, SizeType>& Matrix3<T, SizeType>::operator = (Matrix3&& rhs)
    {
        _width  = rhs._width;
        _depth  = rhs._depth;
        _height = rhs._height;
        _matrix = std::move(rhs._matrix);
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
