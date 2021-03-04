/** MIT License
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

/// @file aseprite_frame.h

#ifndef NGIND_ASEPRITE_FRAME_H
#define NGIND_ASEPRITE_FRAME_H

#include <chrono>

#include "glm/glm.hpp"
#include "resources/config_resource.h"

namespace ngind::animation {

/**
 * Animation frame data in Aseprite.
 */
class AsepriteFrame {
public:
    /**
     * @param data: Aseprite frame data in json format.
     */
    AsepriteFrame(const typename resources::ConfigResource::JsonObject& data);
    AsepriteFrame() = default;
    ~AsepriteFrame() = default;

    /**
     * Get Rectangular range of this frame in image
     * @return glm::vec4, rectangular range
     */
    inline glm::vec4 getRect() const {
        return _rect;
    }

    /**
     * Get relevant position of trimmed sprite.
     * @return glm::vec2, relevant position, zero vector if sprite is not trimmed.
     */
    inline glm::vec2 getPosition() const {
        return _position;
    }

    /**
     * Get the original size of a frame
     * @return glm::vec2, original size
     */
    inline glm::vec2 getSize() const {
        return _original_size;
    }

    /**
     * Get duration time of this frame
     * @return std::chrono::milliseconds, the duration
     */
    inline std::chrono::milliseconds getDuration() const {
        return _duration;
    }
private:
    /**
     * Has sprite been trimmed.
     */
    bool _trimmed;

    /**
     * Rectangular of frame in sprite.
     */
    glm::vec4 _rect{};

    /**
     * Relevant position for trimmed sprite.
     */
    glm::vec2 _position{};

    /**
     * Original size of frame.
     */
    glm::vec2 _original_size{};

    /**
     * How long should the sprite keep this frame in animation.
     */
    std::chrono::milliseconds _duration{};
};

} // namespace ngind::animation

#endif //NGIND_ASEPRITE_FRAME_H
