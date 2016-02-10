#include "2DMatrix.hpp"

namespace Gungi
{
    template <class T>
    Heap2DMatrix<T>::Heap2DMatrix(const size_t& width, const size_t& length)
    : _width  (width)
    , _length (length)
    , _matrix (new T[width * length])
    {}

    template <class T>
    Heap2DMatrix<T>::Heap2DMatrix(const size_t& width, const size_t& length, const T& initValue)
    : _width  (width)
    , _length (length)
    , _matrix (new T[width * length])
    {
        for (size_t i = 0; i < getSize(); ++i)
            _matrix[i] = initValue;
    }

    template <class T>
    Heap2DMatrix<T>::~Heap2DMatrix()
    {
        if (_matrix != nullptr)
        {
            delete [] _matrix;
            _matrix = nullptr;
        }
    }

    template <class T>
    size_t Heap2DMatrix<T>::getWidth() const
    {
        return _width;
    }

    template <class T>
    size_t Heap2DMatrix<T>::getLength() const
    {
        return _length;
    }

    template <class T>
    size_t Heap2DMatrix<T>::getSize() const
    {
        return _width * _length;
    }
    
    template <class T>
    T& Heap2DMatrix<T>::operator [] (const size_t& i)
    {
        return _matrix[i];
    }

    template <class T>
    const T& Heap2DMatrix<T>::operator [] (const size_t& i) const
    {
        return _matrix[i];
    }

    template <class T>
    T& Heap2DMatrix<T>::operator [] (const XY_Indices& idx)
    {
        return _matrix[coorToIndex(idx, _length)];
    }

    template <class T>
    const T& Heap2DMatrix<T>::operator [] (const XY_Indices& idx) const
    {
        return _matrix[coorToIndex(idx , _length)];
    }
    
    template <class T>
    T& Heap2DMatrix<T>::operator () (const size_t& x, const size_t& y)
    {
        return _matrix[coorToIndex(x, y, _length)];
    }

    template <class T>
    const T& Heap2DMatrix<T>::operator () (const size_t& x, const size_t& y) const
    {
        return _matrix[coorToIndex(x, y, _length)];
    }
    
    template <class T, size_t width, size_t length>
    Stack2DMatrix<T,width,length>::Stack2DMatrix(const T& initValue)
    {
        for (size_t i = 0; i < (width * length); ++i)
            _matrix[i] = initValue;
    }

    template <class T, size_t width, size_t length>
    size_t Stack2DMatrix<T,width,length>::getWidth() const
    {
        return width;
    }

    template <class T, size_t width, size_t length>
    size_t Stack2DMatrix<T,width,length>::getLength() const
    {
        return length;
    }

    template <class T, size_t width, size_t length>
    size_t Stack2DMatrix<T,width,length>::getSize() const
    {
        return width * length;
    }

    template <class T, size_t width, size_t length>
    T& Stack2DMatrix<T,width,length>::operator [] (const size_t& i)
    {
        return _matrix[i];
    }

    template <class T, size_t width, size_t length>
    const T& Stack2DMatrix<T,width,length>::operator [] (const size_t& i) const
    {
        return _matrix[i];
    }

    template <class T, size_t width, size_t length>
    T& Stack2DMatrix<T,width,length>::operator [] (const XY_Indices& idx)
    {
        return _matrix[coorToIndex(idx, length)];
    }

    template <class T, size_t width, size_t length>
    const T& Stack2DMatrix<T,width,length>::operator [] 
        (const XY_Indices& idx) const
    {
        return _matrix[coorToIndex(idx,length)];
    }
    
    template <class T, size_t width, size_t length>
    T& Stack2DMatrix<T,width,length>::operator () 
        (const size_t& x, const size_t& y)
    {
        return _matrix[coorToIndex(x, y, length)];
    }

    template <class T, size_t width, size_t length>
    const T& Stack2DMatrix<T,width,length>::operator () 
        (const size_t& x, const size_t& y) const
    {
        return _matrix[coorToIndex(x, y, length)];
    }
}
