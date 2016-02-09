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
    
    /**
     * State setters 
     */

    template <class Matrix, class Indices, class MatrixType>
    void setSingleState(Matrix& matrix, const Indices& idx, const MatrixType& state)
    {
        matrix[idx] = state;
    }

    template <class Matrix, class SizeType, class MatrixType>
    void setPartialLinearState(Matrix& matrix, const SizeType& lowerBound, const SizeType& upperBound, const MatrixType& state)
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

    /**
     * State transformers
     */

    template <class Matrix, class Indices, class Transformer>
    void transformSingleState(Matrix& matrix, const Indices& idx, const Transformer& transFunc)
    {
        transFunc(matrix[idx]);
    }

    template <class Matrix, class SizeType, class Transformer>
    void transformPartialLinearState(Matrix& matrix, const SizeType& lowerBound, const SizeType& upperBound, const Transformer& transFunc)
    {
        for (auto i = lowerBound; i < upperBound; ++i)
            transFunc(matrix[i]);
    }

    template <class Matrix,class IterableCollection, class Transformer>
    void transformPartialRandomState(Matrix& matrix, const IterableCollection& set, const Transformer& transFunc)
    {
        for (auto itr = set.cbegin(); itr != set.cend(); ++itr)
            transFunc(matrix[*itr]);
    }

    template <class Matrix, class Transformer>
    void transformCompleteState(Matrix& matrix, const Transformer& transFunc)
    {
        auto len = matrix.getSize();
        for (decltype(len) i = 0; i < len; ++i)
            transFunc(matrix[i]);
    }

    
    /**
     * State shifters ; Trail setters
     * Assuming 0,0 is top left corner
     */
    template <class Matrix, class Indices, class MatrixType>
    void shiftStateUp_N(Matrix& matrix, Indices idx, const size_t& n, const MatrixType& trailState = MatrixType())
    {
        auto state = matrix[idx];
        auto trailIdx = idx;
        idx.y = (idx.y - n) % matrix.getLength();
        setSingleState(matrix, idx, state); 
        setSingleState(matrix, trailIdx, trailState);
    }
    
    template <class Matrix, class Indices, class MatrixType>
    void shiftStateDown_N(Matrix& matrix, Indices idx, const size_t& n, const MatrixType& trailState = MatrixType())
    {
        auto state = matrix[idx];
        auto trailIdx = idx;
        idx.y = (idx.y + n) % matrix.getLength();
        setSingleState(matrix,idx, state); 
        setSingleState(matrix, trailIdx, trailState);
    }

    template <class Matrix, class Indices, class MatrixType>
    void shiftStateLeft_N(Matrix& matrix, Indices idx, const size_t& n, const MatrixType& trailState = MatrixType())
    {
        auto state = matrix[idx];
        auto trailIdx = idx;
        idx.x = (idx.x - n) % matrix.getWidth();
        setSingleState(matrix,idx, state); 
        setSingleState(matrix, trailIdx, trailState);
    }

    template <class Matrix, class Indices, class MatrixType>
    void shiftStateRight_N(Matrix& matrix, Indices idx, const size_t& n, const MatrixType& trailState = MatrixType())
    {
        auto state = matrix[idx];
        auto trailIdx = idx;
        idx.x = (idx.x + n) % matrix.getWidth();
        setSingleState(matrix,idx, state); 
        setSingleState(matrix, trailIdx, trailState);
    }

    template <class Matrix, class Indices, class Generator>
    decltype(auto) generate(const Matrix& matrix, const Indices& idx, Generator& genFunc)
    {
        return genFunc(matrix[idx]); 
    }
}
