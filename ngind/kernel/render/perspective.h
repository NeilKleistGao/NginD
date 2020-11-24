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

/// @file perspective.h
/// @date 2020/11/1

/// @brief This file includes the declaration of perspective class.

#ifndef NGIND_PERSPECTIVE_H
#define NGIND_PERSPECTIVE_H

#include "math/vector.h"
#include "include/glm/glm.hpp"

namespace ngind {

/**
@class
    Player's perspective in game. It can project rendered objects to
screen.
*/
class Perspective {
public:
    /// @public
    /// @static
    /// @fn Get the instance of unique perspective in game
    /// @param void
    /// @return Perspective*, pointer of instance
    static Perspective* getInstance();

    /// @public
    /// @static
    /// @fn Destroy the instance of unique perspective in game
    /// @param void
    /// @return void
    static void destroyInstance();

    Perspective(const Perspective&) = delete;
    Perspective& operator= (const Perspective&) = delete;

    /// @public
    /// @fn Initialize perspective with position and size
    /// @param const Vector2D&: the position of perspective
    /// @param const size_t&: the width of perspective
    /// @param const size_t&: the height of perspective
    /// @return void
    void init(const Vector2D&, const size_t&, const size_t&);

    /// @public
    /// @fn Move perspective to specified position
    /// @param const Vector2D& center: the center position of
    /// perspective
    /// @return void
    inline void moveTo(const Vector2D& center) {
        init(center, _width, _height);
    }

    /// @public
    /// @fn Get the view projection matrix
    /// @param void
    /// @return glm::mat4, the projection matrix
    inline glm::mat4 getProjection() const {
        return _projection;
    }

    /// @public
    /// @fn Get perspective's size
    /// @param void
    /// @return Vector2D, the size
    inline Vector2D getPerspectiveSize() const {
        return Vector2D{_width, _height};
    }
private:
    /// @private
    Perspective();

    /// @private
    ~Perspective() = default;

    /// @private
    /// @property The instance
    static Perspective* _instance;

    /// @private
    /// @property The size
    size_t _width, _height;

    /// @private
    /// @property Projection matrix
    glm::mat4 _projection;
};

} // namespace

#endif //NGIND_PERSPECTIVE_H
