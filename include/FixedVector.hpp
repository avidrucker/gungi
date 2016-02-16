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

#include <cstdint>
#include <algorithm>

/*
    Basic Idea:
    STACK [ 0 1 2 3 4 ] SZ = 5
    HEAP  [ 0 1 2 3 X ] USED = 4 SZ = 5

    i = 7;
*/

template <class T, size_t SZ>
class FixedVector
{
    public:
        FixedVector();
        ~FixedVector();
        T& operator [] (const size_t& i);
        const T& operator [] (const size_t& i) const;

    private:
        void _alloc(const size_t& n);
        void _free();

        T _stack[SZ];
        T* _heap;
        size_t _heapSz;
        size_t _heapUsed;
};

template <class T, size_t SZ>
FixedVector<T, SZ>::FixedVector()
: _heap     (nullptr)
, _heapSz   (0u)
, _heapUsed (0u)
{}


template <class T, size_t SZ>
FixedVector<T, SZ>::~FixedVector()
{
    _free();
}

/**
 * Find a way to remove the redundant code in both operator []
 */
template <class T, size_t SZ>
T& FixedVector<T, SZ>::operator [] (const size_t& i)
{
    if (i < SZ)
        return _stack[i];
    else
    {
        size_t heapIndex = i - _heapSz;

        if (_heap != nullptr && _heapUsed <= _heapSz && heapIndex < _heapUsed)
            return _heap[heapIndex];

        _alloc(_heapSz + i);
        heapIndex = i - _heapSz;
        _heapUsed = heapIndex + 1;
        return _heap[heapIndex];
    }
}

template <class T, size_t SZ>
const T& FixedVector<T, SZ>::operator [] (const size_t& i) const
{
    if (i < SZ)
        return _stack[i];
    else
    {
        size_t heapIndex = i - _heapSz;

        if (_heap != nullptr && _heapUsed <= _heapSz && heapIndex < _heapUsed)
            return _heap[heapIndex];

        _alloc(_heapSz + i);
        heapIndex = i - _heapSz;
        _heapUsed = heapIndex + 1;
        return _heap[heapIndex];
    }
}

template <class T, size_t SZ>
void FixedVector<T, SZ>::_alloc(const size_t& n)
{
    if (n == _heapSz)
        return;

    if (_heap == nullptr)
    {
        _heap = new T[n];
        _heapSz = n;
        _heapUsed = 0u;
    }
    else
    {
        T* tmp = new T[n];
        if (n < _heapSz)
            std::copy(_heap, _heap + n, tmp);
        else
            std::copy(_heap, _heap + SZ, tmp);
        _free();
        _heap = tmp;
        tmp = nullptr;
        _heapSz = n;
    }
}

template <class T, size_t SZ>
void FixedVector<T, SZ>::_free()
{
    if (_heap != nullptr)
        delete [] _heap;
}
