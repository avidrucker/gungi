#pragma once

#include <mutex>

#include "3DMatrix.hpp"

namespace Gungi
{
    template <class T>
    class AsyncHeap3DMatrix 
    : Heap3DMatrix<T>
    {
        using Super = Heap3DMatrix<T>;

        public:
            AsyncHeap3DMatrix(const size_t& width, const size_t& length, const size_t& height);
            AsyncHeap3DMatrix(const size_t& width, const size_t& length, const size_t& height, const T& initValue);
            T& operator [] (const size_t& i);
            T& operator [] (const XYZ_Indices& idx);
            T& operator () (const size_t& x, const size_t& y, const size_t& z);

        private:
            std::mutex _mutex;
    };

    template <class T, size_t width, size_t length, size_t height>
    class AsyncStack3DMatrix 
    : Stack3DMatrix<T, width, length, height>
    {
        using Super = Stack3DMatrix<T, width, length, height>;

        public:
            AsyncStack3DMatrix(const T& initValue = T());
            T& operator [] (const size_t& i);
            T& operator [] (const XYZ_Indices& idx);
            T& operator () (const size_t& x, const size_t& y, const size_t& z);

        private:
            std::mutex _mutex;
    };
}

#include "Async3DMatrix.cpp"
