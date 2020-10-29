// MIT License
//
// Copyright (c) 2020 NeilKleistGao
//
//        Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
//        to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//        copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
//        copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//        AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// LAST MODIFY: 2020/10/29
// FILENAME: vector.h

#ifndef NGIND_VECTOR_H
#define NGIND_VECTOR_H

#include <cmath>

namespace ngind {

class Vector2D {
public:
    Vector2D();
    Vector2D(const float&, const float&);
    Vector2D(const Vector2D&);

    inline float getX() const {
        return _x;
    }

    inline float getY() const {
        return _y;
    }

    inline void setX(const float& x) {
        this->_x = x;
    }

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

    Vector2D& operator= (const Vector2D&);

    float operator* (const Vector2D&) const;

    float getMagnitude() const;
    float getMagnitude2() const;

    Vector2D normalize() const;
    Vector2D getNormalVector() const;

    Vector2D project(const Vector2D&) const;

    float getAngle(const Vector2D&) const;

    bool isCollinear(const Vector2D&) const;
    bool isReverse(const Vector2D&) const;
    bool isVertical(const Vector2D&) const;

    static const Vector2D INVALID, ORIGIN;

    inline bool isValid() const {
        return !std::isnan(_x) && !std::isnan(_y);
    }

    inline float cross(const Vector2D& v) const {
        return _x * v._y - _y * v._x;
    }

private:
    constexpr static float EPSILON = 1e-6;
    float _x, _y;
};

inline Vector2D operator* (const float& s, const Vector2D& v) {
    return v * s;
}

} // namespace ngind

#endif //NGIND_VECTOR_H
