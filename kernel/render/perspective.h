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
// FILENAME: perspective.h
// LAST MODIFY: 2020/10/29

#ifndef NGIND_PERSPECTIVE_H
#define NGIND_PERSPECTIVE_H

#include "math/vector.h"

namespace ngind {

class Perspective {
public:
    static Perspective* getInstance();
    static void destroyInstance();

    Perspective(const Perspective&) = delete;
    Perspective& operator= (const Perspective&) = delete;

    void init(const Vector2D&, const size_t&, const size_t&);
    inline void moveTo(const Vector2D& center) {
        _center = center;
    }

    inline bool checkVisibility(const Vector2D& lt, const Vector2D& lb, const Vector2D& rt, const Vector2D& rb) {
        return checkSingleVector(lt) || checkSingleVector(lb)
            || checkSingleVector(rt) || checkSingleVector(rb);
    }
private:
    Perspective();
    ~Perspective() = default;

    static Perspective* _instance;
    Vector2D _center, _left, _right, _top, _bottom;

    bool checkSingleVector(const Vector2D&);
};

} // namespace

#endif //NGIND_PERSPECTIVE_H
