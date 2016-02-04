#pragma once

#include <mutex>

#include "2DMatrix.hpp"

namespace Gungi
{

    template <class T>
    class AsyncHeap2DMatrix 
    : Heap2DMatrix<T>
    {
        public:
            AsyncHeap2DMatrix(const size_t& width, const size_t& length)
            : Heap2DMatrix(width,length)
            {}
            
            T& operator [] (const size_t& i)
            {
                std::lock_guard<std::mutex>(_mutex);
                return _matrix[i];
            }

            T& operator [] (const 2D_Indices& idx)
            {
                std::lock_guard<std::mutex>(_mutex);
                return _matrix[coorToIndex(x,y,z,_width,_length)];
            }

            T& operator () (const size_t& x, const size_t& y)
            {
                std::lock_guard<std::mutex>(_mutex);
                return _matrix[coorToIndex(x,y,_width,_length)];
            }

        private:
            std::mutex _mutex;
    };

    template <class T, size_t width, size_t length>
    class AsyncStack2DMatrix 
    : Stack2DMatrix<T, width, length>
    {
        public:
            AsyncStack2DMatrix(const T& initValue = T())
            : Stack2DMatrix(initValue)
            {}

            T& operator [] (const size_t& i)
            {
                std::lock_guard<std::mutex>(_mutex);
                return _matrix[i];
            }

            T& operator [] (const 2D_Indices& idx)
            {
                std::lock_guard<std::mutex>(_mutex);
                return _matrix[coorToIndex(idx,_width,_length)];
            }
            
            T& operator () (const size_t& x, const size_t& y)
            {
                std::lock_guard<std::mutex>(_mutex);
                return _matrix[coorToIndex(x,y,_width,_length)];
            }

        private:
            std::mutex _mutex;
    }
}
