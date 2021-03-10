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

/// @file edge.h

#ifndef NGIND_CLICKABLE_RECEIVER_H
#define NGIND_CLICKABLE_RECEIVER_H

#include <vector>
#include <string>

#include "glm/glm.hpp"
#include "input/mouse_input.h"

namespace ngind::components {
class Button;
} // namespace ngind::components

namespace ngind::ui {

/**
 * Clickable area data set.
 */
struct ClickableReceiver {
    /**
     * Set of vertex comprise constituting the polygon.
     */
    std::vector<glm::vec2> vertex;

    /**
     * Rendering order.
     */
    unsigned int z_order;

    /**
     * Reference to button component.
     */
    components::Button* button;

    /**
     * Compare two ClickableReceiver object.
     * @param other: another object
     * @return bool, true if they are equal
     */
    bool operator== (const ClickableReceiver& other) {
        if (z_order != other.z_order) {
            return false;
        }
        if (vertex.size() != other.vertex.size()) {
            return false;
        }

        for (int i = 0; i < vertex.size(); i++) {
            if (vertex[i] != other.vertex[i]) {
                return false;
            }
        }

        return true;
    }
};

} // namespace ngind::ui

#endif //NGIND_CLICKABLE_RECEIVER_H