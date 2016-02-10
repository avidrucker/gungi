#pragma once

#include "Utility.hpp"

namespace Gungi
{
    template <class T>
    class Heap3DMatrix 
    {
        public:
            Heap3DMatrix(const size_t& width, const size_t& length, const size_t& height);
            Heap3DMatrix(const size_t& width, const size_t& length, const size_t& height, const T& initValue);
            ~Heap3DMatrix();
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

    template <class T, size_t width, size_t length, size_t height>
    class Stack3DMatrix
    {
        public:
            Stack3DMatrix(const T& initValue = T());
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
            T _matrix[width * length * height];
    };
}

#include "3DMatrix.cpp"
