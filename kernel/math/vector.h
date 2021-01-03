/**
 * @copybrief
 * MIT License
 * Copyright (c) 2020 NeilKleistGao
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/// @file vector.h

#ifndef NGIND_VECTOR_H
#define NGIND_VECTOR_H

#include <cmath>

namespace ngind::math {

/**
 * This class declares the presentation of vectors in 2D space and override
 * their operators.
 */
class Vector2D {
public:
    Vector2D();

    /**
     * @param x: x component of vector
     * @param y: y component of vector
     */
    Vector2D(const float& x, const float& y);

    /**
     * @param v: reference of another vector to be copied
     */
    Vector2D(const Vector2D& v) = default;

    /**
     * Get the x component of vector
     * @return float, x component
     */
    inline float getX() const {
        return _x;
    }

    /**
     * Get the y component of vector
     * @return float, y component
     */
    inline float getY() const {
        return _y;
    }

    /**
     * Set the x component of vector
     * @param x: x component
     */
    inline void setX(const float& x) {
        this->_x = x;
    }

    /**
     * Set the y component of vector
     * @param y: y component
     */
    inline void setY(const float& y) {
        this->_y = y;
    }

    Vector2D operator* (const float&) const;
    Vector2D& operator*= (const float&);
    Vector2D operator+ (const Vector2D&) const;
    Vector2D& operator+= (const Vector2D&);
    Vector2D operator- (const Vector2D&) const;
    Vector2D& operator-= (const Vector2D&);
    bool operator== (const Vector2D&) const;
    bool operator!= (const Vector2D&) const;
    Vector2D& operator= (const Vector2D&) = default;
    float operator* (const Vector2D&) const;

    /**
     * Get the magnitude of this vector
     * @return float, the magnitude
     */
    float getMagnitude() const;

    /**
     * Get the square of magnitude of this vector
     * @return float, the square of magnitude
     */
    float getMagnitude2() const;

    /**
     * Normalize this vector
     * @return Vector2D, the normal vector
     */
    Vector2D normalize() const;

    /**
     * Get the normal orthogonal vector of this
     * @return Vector2D, the normal orthogonal vector of this
     */
    Vector2D getNormalOrthogonalVector() const;

    /**
     * Calculate the projection to another vector
     * @param v: another vector
     * @return Vector2D, the projection vector
     */
    Vector2D project(const Vector2D& v) const;

    /**
     * Get the angle between two vectors
     * @param v: another vector
     * @return float, the angle in radian
     */
    float getAngle(const Vector2D& v) const;

    /**
     * Check if two vectors are collinear
     * @param v: another vector
     * @return bool, true if these are collinear
     */
    bool isCollinear(const Vector2D& v) const;

    /**
     * Check if two vectors' directions are reverse
     * @param v: another vector
     * @return bool, true if this vector has a reverse direction
     */
    bool isReverse(const Vector2D& v) const;

    /**
     * Check if two vectors are orthogonal
     * @param v: another vector
     * @return bool, true if these are orthogonal
     */
    bool isOrthogonal(const Vector2D& v) const;

    /**
     * Two special constant vectors to represent for invalid value and original point
     */
    static const Vector2D INVALID, ORIGIN;

    /**
     * Check if this is an invalid vector
     * @return bool, true if invalid
     */
    inline bool isValid() const {
        return !std::isnan(_x) && !std::isnan(_y);
    }

    /**
     * Get cross production of two vectors
     * @param v: another vector
     * @return Vector2D, the calculation result
     */
    inline float cross(const Vector2D& v) const {
        return _x * v._y - _y * v._x;
    }

private:
    /**
     * Epsilon value defined to deal with the precision problem
     */
    constexpr static float EPSILON = 1e-6;

    /**
     * Components of this vector
     */
    float _x, _y;
};

inline Vector2D operator* (const float& s, const Vector2D& v) {
    return v * s;
}

} // namespace ngind::math

#endif //NGIND_VECTOR_H
