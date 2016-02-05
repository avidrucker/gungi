#pragma once

namespace Gungi
{
    template <class Matrix, class Indices>
    void swapState(Matrix& matrix, const Indices& idx1, const Indices& idx2)
    {
        auto tmp = matrix[idx1];
        matrix[idx1] = matrix[idx2];
        matrix[idx2] = tmp;
    }

    template <class Matrix, class MatrixType, class Indices>
    void setSingleState(Matrix& matrix, const Indices& idx, const MatrixType& state)
    {
        matrix[idx] = state;
    }

    template <class Matrix, class MatrixType>
    void setPartialLinearState(Matrix& matrix, const size_t& lowerBound, const size_t& upperBound, const MatrixType& state)
    {
        for (auto i = lowerBound; i < upperBound; ++i)
            matrix[i] = state;
    }

    template <class Matrix, class MatrixType, class IterableCollection>
    void setPartialRandomState(Matrix& matrix, const IterableCollection& set, const MatrixType& state)
    {
        for (auto itr = set.cbegin(); itr != set.cend(); ++itr)
            matrix[*itr] = state;
    }

    template <class Matrix, class MatrixType>
    void setCompleteState(Matrix& matrix, const MatrixType& state)
    {
        auto len = matrix.volume();
        for ( decltype(len) i = 0; i < len; ++i)
            matrix[i] = state;
    }

    template <class Matrix, class MatrixType, class Indices>
    void shiftStateUp_N(Matrix& matrix, Indices idx, const size_t& n, const MatrixType& state)
    {
        idx.y = (idx.y - n) % matrix.getLength();
        setSingleState(matrix, idx, state); 
    }
    
    template <class Matrix, class MatrixType, class Indices>
    void shiftStateDown_N(Matrix& matrix, Indices idx, const size_t& n, const MatrixType& state)
    {
        idx.y = (idx.y + n) % matrix.getLength();
        setSingleState(matrix,idx, state); 
    }

    template <class Matrix, class MatrixType, class Indices>
    void shiftStateLeft_N(Matrix& matrix, Indices idx, const size_t& n, const MatrixType& state)
    {
        idx.x = (idx.x - n) % matrix.getWidth();
        setSingleState(matrix,idx, state); 
    }

    template <class Matrix, class MatrixType, class Indices>
    void shiftStateRight_N(Matrix& matrix, Indices idx, const size_t& n, const MatrixType& state)
    {
        idx.x = (idx.x + n) % matrix.getWidth();
        setSingleState(matrix,idx, state); 
    }
}
