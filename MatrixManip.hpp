#pragma once

#include "3DMatrix.hpp"

namespace Gungi
{
    template <class 3DMatrixType, class T>
    void swapState(3DMatrixType<T>& matrix, const indices& idx1, const indices& idx2)
    {
        auto tmp = matrix[idx1];
        matrix[idx1] = matrix[idx2];
        matrix[idx2] = tmp;
    }

    template <class 3DMatrixType, class T>
    void setSingleState(3DMatrixType<T>& matrix, const indices& idx, const T& state)
    {
        matrix[idx] = state;
    }

    template <class 3DMatrixType, class T>
    void setPartialLinearState(3DMatrixType<T>& matrix, const size_t& lowerBound, const size_t& upperBound, const T& state)
    {
        for (auto i = lowerBound; i < upperBound; ++i)
            matrix[i] = state;
    }

    template <class 3DMatrixType, class IterableCollection, class T>
    void setPartialRandomState(3DMatrixType<T>& matrix, const IterableCollection<indices>& set, const T& state)
    {
        for (auto itr = set.cbegin(); itr != cend(); ++itr)
            matrix[*itr] = state;
    }

    template <class 3DMatrixType, class T>
    void setCompleteState(3DMatrixType<T>& matrix, const T& state)
    {
        auto len = matrix.volume();
        for ( decltype(len) i = 0; i < len; ++i)
            matrix[i] = state;
    }
}
