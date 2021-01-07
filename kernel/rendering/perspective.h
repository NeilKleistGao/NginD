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

/// @file perspective.h

#ifndef NGIND_PERSPECTIVE_H
#define NGIND_PERSPECTIVE_H

#include "include/glm/glm.hpp"

namespace ngind::rendering {
/**
 * Player's perspective in game. It can project rendered objects to
 * screen.
 */
class Perspective {
public:
    /**
     * Get the instance of unique perspective in game
     * @return Perspective*, pointer of instance
     */
    static Perspective* getInstance();

    /**
     * Destroy the instance of unique perspective in game
     */
    static void destroyInstance();

    Perspective(const Perspective&) = delete;
    Perspective& operator= (const Perspective&) = delete;

    /**
     * Initialize perspective with position and size
     * @param center: the position of perspective
     * @param width: the width of perspective
     * @param height: the height of perspective
     */
    void init(const glm::vec2& center, const size_t& width, const size_t& height);

    /**
     * Move perspective to specified position
     * @param center: the center position of
     */
    inline void moveTo(const glm::vec2& center) {
        init(center, _width, _height);
    }

    /**
     * Get the view projection matrix
     * @return glm::mat4, the projection matrix
     */
    inline glm::mat4 getProjection() const {
        return _projection;
    }

    /**
     * Get perspective's size
     * @return Vector2D, the size
     */
    inline glm::vec2 getPerspectiveSize() const {
        return glm::vec2{_width, _height};
    }
private:
    Perspective();
    ~Perspective() = default;

    /**
     * The instance
     */
    static Perspective* _instance;

    /**
     * The size
     */
    size_t _width, _height;

    /**
     * Projection matrix
     */
    glm::mat4 _projection;
};

} // namespace ngind::rendering

#endif //NGIND_PERSPECTIVE_H
