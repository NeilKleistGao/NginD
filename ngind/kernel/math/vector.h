/** MIT License
Copyright (c) 2020 NeilKleistGao
    Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/// @file vector.h
/// @date 2020/11/16

/**
@brief This file includes the declaration of vectors in 2D space and their
operations.
*/

#ifndef NGIND_VECTOR_H
#define NGIND_VECTOR_H

#include <cmath>

namespace ngind {

/**
@class
    This class declares the presentation of vectors in 2D space and override
their operators.
*/
class Vector2D {
public:

    /// @public
    Vector2D();

    /// @public
    /// @param const float&: x component of vector
    /// @param const float&: y component of vector
    Vector2D(const float&, const float&);

    /// @public
    /// @param const Vector2D&: reference of another vector to be copied
    Vector2D(const Vector2D&);

    /// @public
    /// @fn Get the x component of vector
    /// @param void
    /// @return float, x component
    inline float getX() const {
        return _x;
    }

    /// @public
    /// @fn Get the y component of vector
    /// @param void
    /// @return float, y component
    inline float getY() const {
        return _y;
    }

    /// @public
    /// @fn Set the x component of vector
    /// @param const float& x: x component
    /// @return void
    inline void setX(const float& x) {
        this->_x = x;
    }

    /// @public
    /// @fn Set the y component of vector
    /// @param const float& y: y component
    /// @return void
    inline void setY(const float& y) {
        this->_y = y;
    }

    /// @public
    /// @overload Multiply this vector by a real number
    /// @param const float&: the real number
    /// @return Vector2D, the calculation result
    Vector2D operator* (const float&) const;

    /// @public
    /// @overload Multiply this vector by a real number in place
    /// @param const float&: the real number
    /// @return Vector2D&, the reference of this
    Vector2D& operator*= (const float&);

    /// @public
    /// @overload Add these two vectors
    /// @param const Vector2D&: another vector
    /// @return Vector2D, the calculation result
    Vector2D operator+ (const Vector2D&) const;

    /// @public
    /// @overload Add these two vectors in place
    /// @param const Vector2D&: another vector
    /// @return Vector2D&, the reference of this
    Vector2D& operator+= (const Vector2D&);

    /// @public
    /// @overload Subtract a vector
    /// @param const Vector2D&: the vector
    /// @return Vector2D, the calculation result
    Vector2D operator- (const Vector2D&) const;

    /// @public
    /// @overload Subtract a vector in place
    /// @param const Vector2D&: the vector
    /// @return Vector2D&, the reference of this
    Vector2D& operator-= (const Vector2D&);

    /// @public
    /// @overload Check if these two vector are equal
    /// @param const Vector2D&: another vector
    /// @return bool, true if their components are equal
    bool operator== (const Vector2D&) const;

    /// @public
    /// @overload Check if these two vector are not equal
    /// @param const Vector2D&: another vector
    /// @return bool, true if their components are not equal
    bool operator!= (const Vector2D&) const;

    /// @public
    /// @overload Copy from another vector
    /// @param const Vector2D&: another vector
    /// @return Vector2D&, the reference of this
    Vector2D& operator= (const Vector2D&);

    /// @public
    /// @overload Calculate the dot production
    /// @param const Vector2D&: another vector
    /// @return Vector2D, the calculation result
    float operator* (const Vector2D&) const;

    /// @public
    /// @fn Get the magnitude of this vector
    /// @param void
    /// @return float, the magnitude
    float getMagnitude() const;

    /// @public
    /// @fn Get the square of magnitude of this vector
    /// @param void
    /// @return float, the square of magnitude
    float getMagnitude2() const;

    /// @public
    /// @fn Normalize this vector
    /// @param void
    /// @return Vector2D, the normal vector
    Vector2D normalize() const;

    /// @public
    /// @fn Get the normal orthogonal vector of this
    /// @param void
    /// @return Vector2D, the normal orthogonal vector of this
    Vector2D getNormalOrthogonalVector() const;

    /// @public
    /// @fn Calculate the projection to another vector
    /// @param const Vector2D&: another vector
    /// @return Vector2D, the projection vector
    Vector2D project(const Vector2D&) const;

    /// @public
    /// @fn Get the angle between two vectors
    /// @param const Vector2D&: another vector
    /// @return float, the angle in radian
    float getAngle(const Vector2D&) const;

    /// @public
    /// @fn Check if two vectors are collinear
    /// @param const Vector2D&: another vector
    /// @return bool, true if these are collinear
    bool isCollinear(const Vector2D&) const;

    /// @public
    /// @fn Check if two vectors' directions are reverse
    /// @param const Vector2D&: another vector
    /// @return bool, true if this vector has a reverse direction
    bool isReverse(const Vector2D&) const;

    /// @public
    /// @fn Check if two vectors are orthogonal
    /// @param const Vector2D&: another vector
    /// @return bool, true if these are orthogonal
    bool isOrthogonal(const Vector2D&) const;

    /// @public
    /// @static
    /// @property Two special constant vectors to represent for invalid value and original point
    static const Vector2D INVALID, ORIGIN;

    /// @public
    /// @fn Check if this is an invalid vector
    /// @param void
    /// @return bool, true if invalid
    inline bool isValid() const {
        return !std::isnan(_x) && !std::isnan(_y);
    }

    /// @public
    /// @fn Get cross production of two vectors
    /// @param const Vector2D& v: another vector
    /// @return Vector2D, the calculation result
    inline float cross(const Vector2D& v) const {
        return _x * v._y - _y * v._x;
    }

private:
    /// @private
    /// @property Epsilon value defined to deal with the precision problem
    constexpr static float EPSILON = 1e-6;

    /// @private
    /// @property Components of this vector
    float _x, _y;
};

/// @see Vector2D Vector2D::operator* (const float&);
inline Vector2D operator* (const float& s, const Vector2D& v) {
    return v * s;
}

} // namespace ngind

#endif //NGIND_VECTOR_H
