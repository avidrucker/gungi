#pragma once

#include "3DMatrix.hpp"

namespace Gungi
{
    template <class MatrixType, class IndicesType, class T>
    void swapState(MatrixType<T>& matrix, const IndicesType& idx1, const IndicesType& idx2)
    {
        auto tmp = matrix[idx1];
        matrix[idx1] = matrix[idx2];
        matrix[idx2] = tmp;
    }

    template <class MatrixType, class IndicesType, class T>
    void setSingleState(MatrixType<T>& matrix, const IndicesType& idx, const T& state)
    {
        matrix[idx] = state;
    }

    template <class MatrixType, class T>
    void setPartialLinearState(MatrixType<T>& matrix, const size_t& lowerBound, const size_t& upperBound, const T& state)
    {
        for (auto i = lowerBound; i < upperBound; ++i)
            matrix[i] = state;
    }

    template <class MatrixType, class IterableCollection, class IndicesType, class T>
    void setPartialRandomState(MatrixType<T>& matrix, const IterableCollection<IndicesType>& set, const T& state)
    {
        for (auto itr = set.cbegin(); itr != cend(); ++itr)
            matrix[*itr] = state;
    }

    template <class MatrixType, class T>
    void setCompleteState(MatrixType<T>& matrix, const T& state)
    {
        auto len = matrix.volume();
        for ( decltype(len) i = 0; i < len; ++i)
            matrix[i] = state;
    }
}
