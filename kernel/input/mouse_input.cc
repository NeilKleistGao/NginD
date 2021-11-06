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

MouseInput::MouseInput(GLFWwindow*& window) : _buffer0(&_pressed[0]), _buffer1(&_pressed[1]) {
    glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);
    glfwSetMouseButtonCallback(window, GLFWMouseCallback);
}

glm::vec2 MouseInput::getMousePressed(GLFWwindow*& window, const MouseCode& code) {
    if (_buffer1->find(code) != _buffer1->end() && _buffer0->find(code) == _buffer0->end()) {
        return getMouseMoving(window);
    }

    return glm::vec2{NAN, NAN};
}

glm::vec2 MouseInput::getMouse(GLFWwindow*& window, const MouseCode& code) {
    if (_buffer1->find(code) != _buffer1->end()) {
        return getMouseMoving(window);
    }

    return glm::vec2{NAN, NAN};
}

glm::vec2 MouseInput::getMouseReleased(GLFWwindow*& window, const MouseCode& code) {
    if (_buffer1->find(code) == _buffer1->end() && _buffer0->find(code) != _buffer0->end()) {
        return getMouseMoving(window);
    }

    return glm::vec2{NAN, NAN};
}

glm::vec2 MouseInput::getMouseMoving(GLFWwindow*& window) {
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    return {static_cast<float>(x), static_cast<float>(y)};
}

void MouseInput::update() {
    (*_buffer0) = (*_buffer1);
    auto* temp = _buffer0;
    _buffer0 = _buffer1;
    _buffer1 = temp;
}

} // namespace ngind::input