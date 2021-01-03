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

/// @file mouse_input.h

#ifndef NGIND_MOUSE_INPUT_H
#define NGIND_MOUSE_INPUT_H

#include "glfw3.h"

#include "math/vector.h"

#include <set>

namespace ngind::input {

using Vector2D = math::Vector2D;

/**
 * The keyboard code for keyboard input. It's a simple map for GLFW_MOUSE prefixing
 * macros.
 */
enum MouseCode {
    BUTTON_LEFT = GLFW_MOUSE_BUTTON_LEFT,
    BUTTON_RIGHT = GLFW_MOUSE_BUTTON_RIGHT,
    BUTTON_MIDDLE = GLFW_MOUSE_BUTTON_MIDDLE
};

/**
 * The mouse input manager. This is a more sophisticated interface with
 * GLFWwindow as a param. Use Input class instead.
*/
class MouseInput {
public:
    /**
     * @param window: the GLFW window that is the event listener
     */
    explicit MouseInput(GLFWwindow*& window);

    ~MouseInput() = default;

    /**
     * @see kernel/input/input.h
     */
    Vector2D getMousePressed(GLFWwindow*& window, const MouseCode& code);

    /**
     * @see kernel/input/input.h
     */
    Vector2D getMouse(GLFWwindow*& window, const MouseCode& code);

    /**
     * @see kernel/input/input.h
     */
    Vector2D getMouseReleased(GLFWwindow*& window, const MouseCode& code);

    /**
     * @see kernel/input/input.h
     */
    Vector2D getMouseMoving(GLFWwindow*& window);
private:
    /**
     * Record the press state of all mice
     */
    std::set<MouseCode> _pressed;
};

} // namespace ngind::input

#endif //NGIND_MOUSE_INPUT_H
