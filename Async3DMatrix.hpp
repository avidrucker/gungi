#pragma once

#include <mutex>

#include "3DMatrix.hpp"

namespace Gungi
{

    template <class T>
    class AsyncHeap3DMatrix 
    : Heap3DMatrix<T>
    {
        public:
            AsyncHeap3DMatrix(const size_t& width, const size_t& length, const size_t& height)
            : Heap3DMatrix(width,length,height)
            {}
            
            T& operator [] (const size_t& i)
            {
                std::lock_guard<std::mutex>(_mutex);
                return _matrix[i];
            }

            T& operator [] (const 3D_Indices& idx)
            {
                std::lock_guard<std::mutex>(_mutex);
                return _matrix[coorToIndex(x,y,z,_width,_length)];
            }

            T& operator () (const size_t& x, const size_t& y, const size_t& z)
            {
                std::lock_guard<std::mutex>(_mutex);
                return _matrix[coorToIndex(x,y,z,_width,_length)];
            }

        private:
            std::mutex _mutex;
    };

    template <class T, size_t width, size_t length, size_t height>
    class AsyncStack3DMatrix 
    : Stack3DMatrix<T, width, length, height>
    {
        public:
            AsyncStack3DMatrix(const T& initValue = T())
            : Stack3DMatrix (initValue)
            {}

            T& operator [] (const size_t& i)
            {
                std::lock_guard<std::mutex>(_mutex);
                return _matrix[i];
            }

            T& operator [] (const 3D_Indices& idx)
            {
                std::lock_guard<std::mutex>(_mutex);
                return _matrix[coorToIndex(x,y,z,_width,_length)];
            }

            T& operator () (const size_t& x, const size_t& y, const size_t& z)
            {
                std::lock_guard<std::mutex>(_mutex);
                return _matrix[coorToIndex(x,y,z,_width,_length)];
            }

        private:
            std::mutex _mutex;
    }
}
