/*
 * Copyright 2016 Fermin, Yaneury <fermin.yaneury@gmail.com>
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

namespace Gungi
{
    template <class Matrix, class AccessType>
    void swapState(Matrix& matrix, const AccessType& idx1, const AccessType& idx2)
    {
        auto tmp = matrix[idx1];
        matrix[idx1] = matrix[idx2];
        matrix[idx2] = tmp;
    }
    
    /**
     * State setters 
     */

    template <class Matrix, class AccessType, class MatrixType>
    void setSingleState(Matrix& matrix, const AccessType& idx, const MatrixType& state)
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
        auto len = matrix.getSize();
        for (decltype(len) i = 0; i < len; ++i)
            matrix[i] = state;
    }

    /**
     * State transformers
     */

    template <class Matrix, class AccessType, class Transformer>
    void transformSingleState(Matrix& matrix, const AccessType& idx, const Transformer& transFunc)
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
    template <class Matrix, class AccessType, class MatrixType>
    void shiftStateUp_N(Matrix& matrix, AccessType idx, const size_t& n, const MatrixType& trailState = MatrixType())
    {
        auto state = matrix[idx];
        auto trailIdx = idx;
        idx.y = (idx.y - n) % matrix.getLength();
        setSingleState(matrix, idx, state); 
        setSingleState(matrix, trailIdx, trailState);
    }
    
    template <class Matrix, class AccessType, class MatrixType>
    void shiftStateDown_N(Matrix& matrix, AccessType idx, const size_t& n, const MatrixType& trailState = MatrixType())
    {
        auto state = matrix[idx];
        auto trailIdx = idx;
        idx.y = (idx.y + n) % matrix.getLength();
        setSingleState(matrix,idx, state); 
        setSingleState(matrix, trailIdx, trailState);
    }

    template <class Matrix, class AccessType, class MatrixType>
    void shiftStateLeft_N(Matrix& matrix, AccessType idx, const size_t& n, const MatrixType& trailState = MatrixType())
    {
        auto state = matrix[idx];
        auto trailIdx = idx;
        idx.x = (idx.x - n) % matrix.getWidth();
        setSingleState(matrix,idx, state); 
        setSingleState(matrix, trailIdx, trailState);
    }

    template <class Matrix, class AccessType, class MatrixType>
    void shiftStateRight_N(Matrix& matrix, AccessType idx, const size_t& n, const MatrixType& trailState = MatrixType())
    {
        auto state = matrix[idx];
        auto trailIdx = idx;
        idx.x = (idx.x + n) % matrix.getWidth();
        setSingleState(matrix,idx, state); 
        setSingleState(matrix, trailIdx, trailState);
    }

    template <class Matrix, class AccessType, class Generator>
    decltype(auto) generate(const Matrix& matrix, const AccessType& idx, Generator& genFunc)
    {
        return genFunc(matrix[idx]); 
    }
}
