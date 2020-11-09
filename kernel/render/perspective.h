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
// FILENAME: perspective.h
// LAST MODIFY: 2020/11/1

#ifndef NGIND_PERSPECTIVE_H
#define NGIND_PERSPECTIVE_H

#include "math/vector.h"
#include "include/glm/glm.hpp"

namespace ngind {

class Perspective {
public:
    static Perspective* getInstance();
    static void destroyInstance();

    Perspective(const Perspective&) = delete;
    Perspective& operator= (const Perspective&) = delete;

    void init(const Vector2D&, const size_t&, const size_t&);
    inline void moveTo(const Vector2D& center) {
        init(center, _width, _height);
    }

    inline glm::mat4 getProjection() const {
        return _projection;
    }

    inline Vector2D getPerspectiveSize() const {
        return Vector2D{_width, _height};
    }
private:
    Perspective();
    ~Perspective() = default;

    static Perspective* _instance;
    size_t _width, _height;
    glm::mat4 _projection;
};

} // namespace

#endif //NGIND_PERSPECTIVE_H
