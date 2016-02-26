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

#include <algorithm>

namespace Gungi
{
    template <class SizeType>
    struct Point3;

    /**
     * This struct holds two integral types for x,y coordinates.
     */
    template <class SizeType>
    struct Point2
    {
        /**
         * This constructor instantiates a Point2.
         * @param a the desired x value
         * @param b the desired y value
         */
        Point2(const SizeType& a, const SizeType& b)
        : x (a)
        , y (b)
        {}

        /**
         * This constructor instantiates a Point2 from a Point3 of the same
         * type by using its' x value and its' z value.
         */
        Point2(const Point3<SizeType>& pt3)
        : x (pt3.x)
        , y (pt3.z)
        {}

        SizeType x; /**< The x value of the point. */
        SizeType y; /**< The y value of the point. */
    };

    /**
     * This struct holds three integral types for x,z,y coordinates.
     */
    template <class SizeType>
    struct Point3
    {
        /**
         * This constructor instatiates a Point3.
         * @param a the desired x value
         * @param b the desired z value
         * @param c the desired y vaue
         */
        Point3(const SizeType& a, const SizeType& b, const SizeType& c)
        : x (a)
        , z (b)
        , y (c)
        {}

        /**
         * This constructor instantiates a Point3 from a Point2 of the same
         * type by using the Point2's x value as its' own, and its' y value as 
         * its z value. The y value will call the default constructor of the SizeType.
         */
        Point3(const Point2<SizeType>& pt)
        : x (pt.x)
        , z (pt.y)
        , y (SizeType())
        {}

        SizeType x; /**< The x value of the point. */
        SizeType z; /**< The z value of the point. */
        SizeType y; /**< The y value of the point. */
    };

    /**
     * This function converts a given x,y point on a matrix to 
     * a single-dimension array index using the matrix's length.
     * @param x the x value of the point
     * @param y the y value of the point
     * @param length the length of the matrix 
     * @return the single-dimension index
     */
    template <class SizeType>
    SizeType coorToIndex(const SizeType& x, const SizeType& y, const SizeType& length)
    {
        return y + x * length;
    }

    /**
     * This function converts a given Point2<SizeType> on a matrix to 
     * a single-dimension array index using the matrix's length.
     * @param idx a Point2 with valid x,y values
     * @param length the length of the matrix 
     * @return the single-dimension index
     */
    template <class SizeType>
    SizeType coorToIndex(const Point2<SizeType>& idx, const SizeType& length)
    {
        return idx.y + idx.x * length; 
    }

    /**
     * This function converts a given x,z,y point on a three-dimensional matrix to 
     * a single-dimension array index using the matrix's width and depth.
     * @param x the x value of the point
     * @param z the z value of the point
     * @param y the y value of the point
     * @param width the width of the matrix
     * @param depth the depth of the matrix
     * @return the single-dimension index
     */
    template <class SizeType>
    SizeType coorToIndex(const SizeType& x, const SizeType& z, const SizeType& y, 
            const SizeType& width, const SizeType& depth)
    {
        return (y * width * depth) + (z * width) + x;
    }

    /**
     * This function converts a given x,z,y point on a three-dimensional matrix to 
     * a single-dimension array index using the matrix's width and depth.
     * @idx a Point3 with valid x,z,y values
     * @param width the width of the matrix
     * @param depth the depth of the matrix
     * @return the single-dimension index
     */
    template <class SizeType>
    SizeType coorToIndex(const Point3<SizeType>& idx, const SizeType& width, const SizeType& depth)
    {
        return (idx.y * width * depth) + (idx.z * width) + idx.x;
    }
   
    /**
     * This comparison operator evalutes the x values of the points and then the y values
     * if the x values are equal.
     * @param lhs left hand side point to test
     * @param rhs right hand side point to test
     * @return true if lhs < rhs
     */
    template <class SizeType>
    bool operator < (const Point2<SizeType>& lhs, const Point2<SizeType>& rhs)
    {
        if (lhs.x < rhs.x)
            return true;

        if (rhs.x < lhs.x)
            return false;

        return lhs.y < rhs.y;
    }

    /**
     * This comparison operator evalutes the x values of the points, then the z values,  and then 
     * the y values if the both the x and z values are equal.
     * @param lhs left hand side point to test
     * @param rhs right hand side point to test
     * @return true if lhs < rhs
     */
    template <class SizeType>
    bool operator < (const Point3<SizeType>& lhs, const Point3<SizeType>& rhs)
    {
        if (lhs.x < rhs.x)
            return true;

        if (rhs.x < lhs.x)
            return false;
        
        if (lhs.z < rhs.z)
            return true;

        if (rhs.z < lhs.z)
            return false;

        return lhs.y < rhs.y;
    }

    /**
     * This equality operator checks if both points have all equivalent values.
     * @param lhs left hand side point to test
     * @param rhs right hand side point to test
     * @return true if lhs == rhs
     */
    template <class SizeType>
    bool operator == (const Point2<SizeType>& lhs, const Point2<SizeType>& rhs)
    {
        return lhs.x == rhs.x && lhs.y == rhs.y; 
    }

    /**
     * This equality operator checks if both points have all equivalent values.
     * @param lhs left hand side point to test
     * @param rhs right hand side point to test
     * @return true if lhs == rhs
     */
    template <class SizeType>
    bool operator == (const Point3<SizeType>& lhs, const Point3<SizeType>& rhs)
    {
        return lhs.x == rhs.x && lhs.z == rhs.z && lhs.y == rhs.y;
    }
}
