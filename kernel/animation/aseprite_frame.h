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

class AsepriteFrame {
public:
    AsepriteFrame() = default;
    AsepriteFrame(const typename resources::ConfigResource::JsonObject& data);
    ~AsepriteFrame() = default;

    inline glm::vec4 getRect() const {
        return _rect;
    }

    inline glm::vec2 getPosition() const {
        return _position;
    }

    inline glm::vec2 getSize() const {
        return _original_size;
    }

    inline std::chrono::milliseconds getDuration() const {
        return _duration;
    }
private:
    bool _trimmed;
    glm::vec4 _rect{};
    glm::vec2 _position{};
    glm::vec2 _original_size{};
    std::chrono::milliseconds _duration{};
};

} // namespace ngind::animation

#endif //NGIND_ASEPRITE_FRAME_H
