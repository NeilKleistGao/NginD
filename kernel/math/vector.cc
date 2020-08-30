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
// LAST MODIFY: 2020/8/30
// FILENAME: vector.cc

#include "vector.h"

#include <cmath>

namespace ngind {

Vector2D::Vector2D() : Vector2D(0.0f, 0.0f) {
}

Vector2D::Vector2D(const float& x, const float& y) : _x(x), _y(y) {
}

Vector2D::Vector2D(const Vector2D& v) : Vector2D(v.getX(), v.getY()) {
}

Vector2D Vector2D::operator* (const float& s) const {
    auto vec = *this;
    vec *= s;
    return vec;
}

Vector2D& Vector2D::operator*= (const float& s) {
    this->_x *= s;
    this->_y *= s;
    return *this;
}

Vector2D Vector2D::operator+ (const Vector2D& v) const {
    auto vec = *this;
    vec += v;
    return vec;
}

Vector2D& Vector2D::operator+= (const Vector2D& v) {
    this->_x += v._x;
    this->_y += v._y;
    return *this;
}

Vector2D Vector2D::operator- (const Vector2D& v) const {
    Vector2D vec = *this;
    vec -= v;
    return vec;
}

Vector2D& Vector2D::operator-= (const Vector2D& v) {
    this->_x -= v._x;
    this->_y -= v._y;
    return *this;
}

bool Vector2D::operator== (const Vector2D& v) const {
    return this->_x == v._x && this->_y == v._y;
}

bool Vector2D::operator!= (const Vector2D& v) const {
    return !((*this) == v);
}

Vector2D& Vector2D::operator= (const Vector2D& v) {
    this->_x = v._x;
    this->_y = v._y;
    return *this;
}

float Vector2D::operator* (const Vector2D& v) const {
    return this->_x * v._x + this->_y * v._y;
}

float Vector2D::getMagnitude() const {
    return std::sqrt(this->getMagnitude2());
}

float Vector2D::getMagnitude2() const {
    float x2 = this->_x * this->_x,
            y2 = this->_y * this->_y;
    return x2 + y2;
}

Vector2D Vector2D::normalize() const {
    float mag = this->getMagnitude();
    Vector2D vec = *this;
    vec *= (1.0f / mag);
    return vec;
}

Vector2D Vector2D::getNormalVector() const {
    return Vector2D(this->_y, -this->_x).normalize();
}

Vector2D Vector2D::project(const Vector2D& v) const {
    Vector2D norm = v.normalize();
    float pro = (*this) * v;
    float cos_pro = pro / (this->getMagnitude() * v.getMagnitude());
    float len = this->getMagnitude() * cos_pro;
    return len * norm;
}

float Vector2D::getAngle(const Vector2D& v) const {
    float pro = (*this) * v;
    pro /= (this->getMagnitude() * v.getMagnitude());
    return std::acos(pro);
}

bool Vector2D::isCollinear(const Vector2D& v) const {
    float mag1 = this->getMagnitude2(),
          mag2 = v.getMagnitude2();
    return std::abs(mag1 * mag2 - (*this) * v) < EPSILON;
}

bool Vector2D::isReverse(const Vector2D& v) const {
    float mag1 = this->getMagnitude2(),
            mag2 = v.getMagnitude2();
    return mag1 * mag2 - (*this) * v < 0;
}

bool Vector2D::isVertical(const Vector2D& v) const {
    return std::abs((*this) * v) < EPSILON;
}

} // namespace ngind