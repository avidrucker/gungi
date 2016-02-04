#pragma once

#include "Utility.hpp"

namespace Gungi
{
    template <class T>
    class Heap3DMatrix 
    {
        public:
            Heap3DMatrix(const size_t& width, const size_t& length, const size_t& height)
            : _width  (width)
            , _length (length)
            , _height (height)
            , _matrix (new T[width * length * height])
            {}

            Heap3DMatrix(const size_t& width, const size_t& length, const size_t& height, const T& initValue)
            : _width  (width)
            , _length (length)
            , _height (height)
            , _matrix (new T[width * length * height])
            {
                for (size_t i = 0; i < getVolume(); ++i)
                    _matrix[i] = initValue;
            }
            
            ~Heap3DMatrix()
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

            size_t getHeight() const
            {
                return _height;
            }
            
            size_t getVolume() const
            {
                return _width * _length * _height;
            }

            T& operator [] (const size_t& i)
            {
                return _matrix[i];
            }


            const T& operator [] (const size_t& i) const
            {
                return _matrix[i];
            }

            T& operator [] (const XYZ_Indices& idx)
            {
                return _matrix[coorToIndex(idx,_width,_length)];
            }

            const T& operator [] (const XYZ_Indices& idx) const
            {
                return _matrix[coorToIndex(idx,_width,_length)];
            }
            
            T& operator () (const size_t& x, const size_t& y, const size_t& z)
            {
                return _matrix[coorToIndex(x,y,z,_width,_length)];
            }

            const T& operator () (const size_t& x, const size_t& y, const size_t& z) const
            {
                return _matrix[coorToIndex(x,y,z,_width,_length)];
            }
            
        protected:
            size_t _width, _length, _height;
            T* _matrix;
            
    };

    template <class T, size_t width, size_t length, size_t height>
    class Stack3DMatrix
    {
        public:
            Stack3DMatrix(const T& initValue = T())
            {
                for (size_t i = 0; i < (width * length * height); ++i)
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

            size_t getHeight() const
            {
                return height;
            }

            size_t volume() const
            {
                return width * length * height;
            }

            T& operator [] (const size_t& i)
            {
                return _matrix[i];
            }

            const T& operator [] (const size_t& i) const
            {
                return _matrix[i];
            }

            T& operator [] (const XYZ_Indices& idx)
            {
                return _matrix[coorToIndex(idx, width, length)];
            }

            const T& operator [] (const XYZ_Indices& idx) const
            {
                return _matrix[coorToIndex(idx, width, length)];
            }
            
            T& operator () (const size_t& x, const size_t& y, const size_t& z)
            {
                return _matrix[coorToIndex(x, y, z, width, length)];
            }

            const T& operator () (const size_t& x, const size_t& y, const size_t& z) const
            {
                return _matrix[coorToIndex(x, y, z, width, length)];
            }

        protected:
            T _matrix[width * length * height];
    };
}
