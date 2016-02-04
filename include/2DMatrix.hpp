
#pragma once

#include "Utility.hpp"

namespace Gungi
{
    template <class T>
    class Heap2DMatrix 
    {
        public:
            Heap2DMatrix(const size_t& width, const size_t& length)
            : _width  (width)
            , _length (length)
            , _matrix (new T[width * length])
            {}

            Heap2DMatrix(const size_t& width, const size_t& length, const T& initValue)
            : _width  (width)
            , _length (length)
            , _matrix (new T[width * length])
            {
                for (size_t i = 0; i < getArea(); ++i)
                    _matrix[i] = initValue;
            }

            
            ~Heap2DMatrix()
            {
                delete [] _matrix;
            }

            size_t getWidth() const
            {
                return _width;
            }

            size_t getLength() const
            {
                return _length;
            }

            size_t getArea() const
            {
                return _width * _length;
            }
            
            T& operator [] (const size_t& i)
            {
                return _matrix[i];
            }

            const T& operator [] (const size_t& i) const
            {
                return _matrix[i];
            }

            T& operator [] (const XY_Indices& idx)
            {
                return _matrix[coorToIndex(idx, _length)];
            }

            const T& operator [] (const XY_Indices& idx) const
            {
                return _matrix[coorToIndex(idx , _length)];
            }
            
            T& operator () (const size_t& x, const size_t& y)
            {
                return _matrix[coorToIndex(x, y, _length)];
            }

            const T& operator () (const size_t& x, const size_t& y) const
            {
                return _matrix[coorToIndex(x, y, _length)];
            }
            
        protected:
            size_t _width, _length;
            T* _matrix;
            
    };

    template <class T, size_t width, size_t length>
    class Stack2DMatrix
    {
        public:
            Stack2DMatrix(const T& initValue = T())
            {
                for (size_t i = 0; i < (width * length); ++i)
                    _matrix[i] = initValue;
            }

            size_t getWidth() const
            {
                return width;
            }

            size_t getLength() const
            {
                return length;
            }

            size_t area() const
            {
                return width * length;
            }

            T& operator [] (const size_t& i)
            {
                return _matrix[i];
            }

            const T& operator [] (const size_t& i) const
            {
                return _matrix[i];
            }

            T& operator [] (const XY_Indices& idx)
            {
                return _matrix[coorToIndex(idx, length)];
            }

            const T& operator [] (const XY_Indices& idx) const
            {
                return _matrix[coorToIndex(idx,length)];
            }
            
            T& operator () (const size_t& x, const size_t& y)
            {
                return _matrix[coorToIndex(x, y, length)];
            }

            const T& operator () (const size_t& x, const size_t& y) const
            {
                return _matrix[coorToIndex(x, y, length)];
            }

        protected:
            T _matrix[width * length];
    };
}
