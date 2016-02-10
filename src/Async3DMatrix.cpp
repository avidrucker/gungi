#include "Async3DMatrix.hpp"

namespace Gungi
{
    template <class T>
    AsyncHeap3DMatrix<T>::AsyncHeap3DMatrix
        (const size_t& width, const size_t& length, const size_t& height)
    : Heap3DMatrix<T>(width,length,height)
    {}

    template <class T>
    AsyncHeap3DMatrix<T>::AsyncHeap3DMatrix
        (const size_t& width, const size_t& length, const size_t& height, const T& initValue)
    : Heap3DMatrix<T>(width,length,height, initValue)
    {}

    template <class T>
    T& AsyncHeap3DMatrix<T>::operator [] (const size_t& i)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        return Super::_matrix[i];
    }

    template <class T>
    T& AsyncHeap3DMatrix<T>::operator [] (const XYZ_Indices& idx)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        return Super::_matrix[coorToIndex(idx, Super::_width, Super::_length)];
    }

    template <class T>
    T& AsyncHeap3DMatrix<T>::operator ()
        (const size_t& x, const size_t& y, const size_t& z)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        return Super::matrix[coorToIndex(x, y, z, Super::_width, Super::_length)];
    }

    template <class T, size_t width, size_t length, size_t height>
    AsyncStack3DMatrix<T,width,length,height>::AsyncStack3DMatrix
        (const T& initValue)
    : Stack3DMatrix <T,width,length,height>(initValue)
    {}

    template <class T, size_t width, size_t length, size_t height>
    T& AsyncStack3DMatrix<T,width,length,height>::operator []
        (const size_t& i)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        return Super::_matrix[i];
    }

    template <class T, size_t width, size_t length, size_t height>
    T& AsyncStack3DMatrix<T,width,length,height>::operator []
        (const XYZ_Indices& idx)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        return Super::_matrix[coorToIndex(idx, width, length)];
    }

    template <class T, size_t width, size_t length, size_t height>
    T& AsyncStack3DMatrix<T,width,length,height>::operator ()
        (const size_t& x, const size_t& y, const size_t& z)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        return Super::_matrix[coorToIndex(x, y, z, width, length)];
    }
}
