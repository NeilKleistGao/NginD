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

/// @file mouse_input.cc

#include "mouse_input.h"

namespace ngind::input {

MouseInput::MouseInput(GLFWwindow*& window) {
    glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);
    _pressed.clear();
}

Vector2D MouseInput::getMousePressed(GLFWwindow*& window, const MouseCode& code) {
    int state = glfwGetMouseButton(window, code);
    if (state == GLFW_PRESS) {
        if (_pressed.find(code) == _pressed.end()) {
            _pressed.insert(code);
            return getMouseMoving(window);
        }
    }
    else {
        if (_pressed.find(code) != _pressed.end()) {
            _pressed.erase(code);
        }
    }

    return Vector2D::INVALID;
}

Vector2D MouseInput::getMouse(GLFWwindow*& window, const MouseCode& code) {
    int state = glfwGetMouseButton(window, code);
    if (state == GLFW_PRESS) {
        if (_pressed.find(code) != _pressed.end()) {
            return getMouseMoving(window);
        }
        else {
            _pressed.insert(code);
        }
    }
    else {
        if (_pressed.find(code) != _pressed.end()) {
            _pressed.erase(code);
        }
    }

    return Vector2D::INVALID;
}

Vector2D MouseInput::getMouseReleased(GLFWwindow*& window, const MouseCode& code) {
    int state = glfwGetMouseButton(window, code);
    if (state == GLFW_PRESS) {
        if (_pressed.find(code) == _pressed.end()) {
            _pressed.insert(code);
        }
    }
    else {
        if (_pressed.find(code) != _pressed.end()) {
            _pressed.erase(code);
            return getMouseMoving(window);
        }
    }

    return Vector2D::INVALID;
}

Vector2D MouseInput::getMouseMoving(GLFWwindow*& window) {
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    return Vector2D(static_cast<float>(x), static_cast<float>(y));
}

} // namespace ngind::input