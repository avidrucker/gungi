
#pragma once

#include "Utility.hpp"

namespace Gungi
{
    template <class T>
    class Heap2DMatrix 
    {
        public:
            Heap2DMatrix(const size_t& width, const size_t& length);
            Heap2DMatrix(const size_t& width, const size_t& length, const T& initValue);
            ~Heap2DMatrix();
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

    template <class T, size_t width, size_t length>
    class Stack2DMatrix
    {
        public:
            Stack2DMatrix(const T& initValue = T());
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
            T _matrix[width * length];
    };
}

#include "2DMatrix.cpp"
