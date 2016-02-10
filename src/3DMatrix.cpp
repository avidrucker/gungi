#include "3DMatrix.hpp"

namespace Gungi
{
    template <class T>
    Heap3DMatrix<T>::Heap3DMatrix
        (const size_t& width, const size_t& length, const size_t& height)
    : _width  (width)
    , _length (length)
    , _height (height)
    , _matrix (new T[width * length * height])
    {}

    template <class T>
    Heap3DMatrix<T>::Heap3DMatrix
        (const size_t& width, const size_t& length, const size_t& height, const T& initValue)
    : _width  (width)
    , _length (length)
    , _height (height)
    , _matrix (new T[width * length * height])
    {
        for (size_t i = 0; i < getSize(); ++i)
            _matrix[i] = initValue;
    }

    template <class T>
    Heap3DMatrix<T>::~Heap3DMatrix()
    {
        if (_matrix != nullptr)
        {
            delete [] _matrix;
            _matrix = nullptr;
        }
    }

    template <class T>
    size_t Heap3DMatrix<T>::getWidth() const
    {
        return _width;
    }

    template <class T>
    size_t Heap3DMatrix<T>::getLength() const
    {
        return _length;
    }

    template <class T>
    size_t Heap3DMatrix<T>::getHeight() const
    {
        return _height;
    }

    template <class T>
    size_t Heap3DMatrix<T>::getSize() const
    {
        return _width * _length * _height;
    }

    template <class T>
    T& Heap3DMatrix<T>::operator [] (const size_t& i)
    {
        return _matrix[i];
    }

    template <class T>
    const T& Heap3DMatrix<T>::operator [] (const size_t& i) const
    {
        return _matrix[i];
    }

    template <class T>
    T& Heap3DMatrix<T>::operator [] (const XYZ_Indices& idx)
    {
        return _matrix[coorToIndex(idx,_width,_length)];
    }

    template <class T>
    const T& Heap3DMatrix<T>::operator [] (const XYZ_Indices& idx) const
    {
        return _matrix[coorToIndex(idx,_width,_length)];
    }

    template <class T>
    T& Heap3DMatrix<T>::operator () (const size_t& x, const size_t& y, const size_t& z)
    {
        return _matrix[coorToIndex(x,y,z,_width,_length)];
    }

    template <class T>
    const T& Heap3DMatrix<T>::operator ()  
        (const size_t& x, const size_t& y, const size_t& z) const
    {
        return _matrix[coorToIndex(x,y,z,_width,_length)];
    }

    template <class T, size_t width, size_t length, size_t height>
    Stack3DMatrix<T, width, length, height>::Stack3DMatrix (const T& initValue)
    {
        for (size_t i = 0; i < (width * length * height); ++i)
            _matrix[i] = initValue;
    }

    template <class T, size_t width, size_t length, size_t height>
    size_t Stack3DMatrix<T, width, length, height>::getWidth() const
    {
        return width;
    }

    template <class T, size_t width, size_t length, size_t height>
    size_t Stack3DMatrix<T, width, length, height>::getLength() const
    {
        return length;
    }

    template <class T, size_t width, size_t length, size_t height>
    size_t Stack3DMatrix<T, width, length, height>::getHeight() const
    {
        return height;
    }

    template <class T, size_t width, size_t length, size_t height>
    size_t Stack3DMatrix<T, width, length, height>::getSize() const
    {
        return width * length * height;
    }

    template <class T, size_t width, size_t length, size_t height>
    T& Stack3DMatrix<T, width, length, height>::operator []
        (const size_t& i)
    {
        return _matrix[i];
    }

    template <class T, size_t width, size_t length, size_t height>
    const T& Stack3DMatrix<T, width, length, height>::operator []
        (const size_t& i) const
    {
        return _matrix[i];
    }

    template <class T, size_t width, size_t length, size_t height>
    T& Stack3DMatrix<T, width, length, height>::operator []
        (const XYZ_Indices& idx)
    {
        return _matrix[coorToIndex(idx, width, length)];
    }

    template <class T, size_t width, size_t length, size_t height>
    const T& Stack3DMatrix<T, width, length, height>::operator [] 
        (const XYZ_Indices& idx) const
    {
        return _matrix[coorToIndex(idx, width, length)];
    }

    template <class T, size_t width, size_t length, size_t height>
    T& Stack3DMatrix<T, width, length, height>::operator ()
        (const size_t& x, const size_t& y, const size_t& z)
    {
        return _matrix[coorToIndex(x, y, z, width, length)];
    }

    template <class T, size_t width, size_t length, size_t height>
    const T& Stack3DMatrix<T, width, length, height>::operator ()
        (const size_t& x, const size_t& y, const size_t& z) const
    {
        return _matrix[coorToIndex(x, y, z, width, length)];
    }
}
