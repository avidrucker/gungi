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
            AsyncHeap2DMatrix(const size_t& width, const size_t& length)
            : Heap2DMatrix<T>(width,length)
            {}
            
            AsyncHeap2DMatrix(const size_t& width, const size_t& length, const T& initValue)
            : Heap2DMatrix<T>(width,length, initValue)
            {}

            T& operator [] (const size_t& i)
            {
                std::lock_guard<std::mutex> lock(_mutex);
                return Super::_matrix[i];
            }

            T& operator [] (const XY_Indices& idx)
            {
                std::lock_guard<std::mutex> lock(_mutex);
                return Super::_matrix[coorToIndex(idx, Super::_length)];
            }

            T& operator () (const size_t& x, const size_t& y)
            {
                std::lock_guard<std::mutex> lock(_mutex);
                return Super::_matrix[coorToIndex(x, y, Super::_length)];
            }
        private:
            std::mutex _mutex;
    };

    template <class T, size_t width, size_t length>
    class AsyncStack2DMatrix 
    : Stack2DMatrix<T, width, length>
    {
        using Super = Stack2DMatrix<T, width, length>;

        public:
            AsyncStack2DMatrix <T,width,length>(const T& initValue = T())
            : Stack2DMatrix<T,width,length>(initValue)
            {}

            T& operator [] (const size_t& i)
            {
                std::lock_guard<std::mutex> lock(_mutex);
                return Super::_matrix[i];
            }

            T& operator [] (const XY_Indices& idx)
            {
                std::lock_guard<std::mutex> lock(_mutex);
                return Super::_matrix[coorToIndex(idx, length)];
            }
            
            T& operator () (const size_t& x, const size_t& y)
            {
                std::lock_guard<std::mutex> lock(_mutex);
                return Super::_matrix[coorToIndex(x, y, length)];
            }
        private:
            std::mutex _mutex;
    };
}
