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
