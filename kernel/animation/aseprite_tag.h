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

/// @file aseprite_tag.h

#ifndef NGIND_ASEPRITE_TAG_H
#define NGIND_ASEPRITE_TAG_H

#include <string>

#include "resources/config_resource.h"

namespace ngind::animation {

class AsepriteTag {
public:
    AsepriteTag(const typename resources::ConfigResource::JsonObject& data);
    ~AsepriteTag() = default;

    enum class AnimationDirection {
        DIRECTION_FORWARD = 0,
        DIRECTION_REVERSE,
        DIRECTION_PING_PONG
    };

    inline std::string getName() const {
        return _name;
    }

    inline unsigned int begin() const {
        return _from;
    }

    inline unsigned int end() const {
        return _to;
    }

    inline AnimationDirection getDirection() const {
        return _direction;
    }

private:
    std::string _name;
    unsigned int _from;
    unsigned int _to;
    AnimationDirection _direction;
};

} // namespace ngind::animation

#endif //NGIND_ASEPRITE_TAG_H
