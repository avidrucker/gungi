#include "Async2DMatrix.hpp"

namespace Gungi
{
    template <class T>
    AsyncHeap2DMatrix<T>::AsyncHeap2DMatrix(const size_t& width, const size_t& length)
    : Heap2DMatrix<T>(width,length)
    {}

    template <class T>
    AsyncHeap2DMatrix<T>::AsyncHeap2DMatrix
        (const size_t& width, const size_t& length, const T& initValue)
    : Heap2DMatrix<T>(width,length, initValue)
    {}

    template <class T>
    T& AsyncHeap2DMatrix<T>::operator [] (const size_t& i)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        return Super::_matrix[i];
    }

    template <class T>
    T& AsyncHeap2DMatrix<T>::operator [] (const XY_Indices& idx)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        return Super::_matrix[coorToIndex(idx, Super::_length)];
    }

    template <class T>
    T& AsyncHeap2DMatrix<T>::operator () (const size_t& x, const size_t& y)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        return Super::_matrix[coorToIndex(x, y, Super::_length)];
    }


    template <class T, size_t width, size_t length>
    AsyncStack2DMatrix<T,width,length>::AsyncStack2DMatrix (const T& initValue)
    : Stack2DMatrix<T,width,length>(initValue)
    {}

    template <class T, size_t width, size_t length>
    T& AsyncStack2DMatrix<T,width,length>::operator [] (const size_t& i)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        return Super::_matrix[i];
    }

    template <class T, size_t width, size_t length>
    T& AsyncStack2DMatrix<T,width,length>::operator [] (const XY_Indices& idx)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        return Super::_matrix[coorToIndex(idx, length)];
    }

    template <class T, size_t width, size_t length>
    T& AsyncStack2DMatrix<T,width,length>::operator () 
        (const size_t& x, const size_t& y)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        return Super::_matrix[coorToIndex(x, y, length)];
    }
}
