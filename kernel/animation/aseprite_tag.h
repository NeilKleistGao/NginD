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

/**
 * Animation tag object in Aseprite.
 */
class AsepriteTag {
public:
    /**
     * @param data: Tag object in json format.
     */
    AsepriteTag(const typename resources::ConfigResource::JsonObject& data);
    ~AsepriteTag() = default;

    /**
     * Animation playing direction
     */
    enum class AnimationDirection {
        DIRECTION_FORWARD = 0, /// Play animation forward
        DIRECTION_REVERSE, /// Play animation in reverse
        DIRECTION_PING_PONG /// Play animation back and forth
    };

    /**
     * Get tag's name.
     * @return std::string, name of tag
     */
    inline std::string getName() const {
        return _name;
    }

    /**
     * Get the beginning frame's index of tag
     * @return unsigned int, index of beginning frame
     */
    inline unsigned int begin() const {
        return _from;
    }

    /**
     * Get the ending frame's index + 1 of tag
     * @return unsigned int, index of ending frame + 1
     */
    inline unsigned int end() const {
        return _to;
    }

    /**
     * Get the animation's direction of tag
     * @return AnimationDirection, animation's direction
     */
    inline AnimationDirection getDirection() const {
        return _direction;
    }

private:
    /**
     * Tag's name
     */
    std::string _name;

    /**
     * Beginning frame's index
     */
    unsigned int _from;

    /**
     * Ending frame's index
     */
    unsigned int _to;

    /**
     * Animation playing direction
     */
    AnimationDirection _direction;
};

} // namespace ngind::animation

#endif //NGIND_ASEPRITE_TAG_H
