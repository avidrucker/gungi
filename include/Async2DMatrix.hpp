#pragma once

#include <mutex>

#include "2DMatrix.hpp"

namespace Gungi
{
    template <class T>
    class AsyncHeap2DMatrix 
    : Heap2DMatrix<T>
    {
        using Super = Heap2DMatrix<T>;

        public:
            AsyncHeap2DMatrix(const size_t& width, const size_t& length);
            AsyncHeap2DMatrix(const size_t& width, const size_t& length, const T& initValue);
            T& operator [] (const size_t& i);
            T& operator [] (const XY_Indices& idx);
            T& operator () (const size_t& x, const size_t& y);

        private:
            std::mutex _mutex;
    };

    template <class T, size_t width, size_t length>
    class AsyncStack2DMatrix 
    : Stack2DMatrix<T, width, length>
    {
        using Super = Stack2DMatrix<T, width, length>;

        public:
            AsyncStack2DMatrix <T,width,length>(const T& initValue = T());
            T& operator [] (const size_t& i);
            T& operator [] (const XY_Indices& idx);
            T& operator () (const size_t& x, const size_t& y);

        private:
            std::mutex _mutex;
    };
}

#include "Async2DMatrix.cpp"
