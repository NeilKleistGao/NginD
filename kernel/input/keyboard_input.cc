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

/// @file: keyboard_input.cc

#include "keyboard_input.h"

namespace ngind::input {

KeyboardInput::KeyboardInput(GLFWwindow* window) : _buffer1(&_pressed[1]), _buffer0(&_pressed[0]) {
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
    glfwSetKeyCallback(window, GLFWKeyboardCallback);
}

bool KeyboardInput::getKey(GLFWwindow *window, const KeyboardCode& code) {
    return this->_buffer1->find(code) == this->_buffer1->end();
}

bool KeyboardInput::getKeyPressed(GLFWwindow* window, const KeyboardCode& code) {
    return this->_buffer1->find(code) != this->_buffer1->end() && this->_buffer0->find(code) == this->_buffer0->end();
}

bool KeyboardInput::getKeyReleased(GLFWwindow* window, const KeyboardCode& code) {
    return this->_buffer1->find(code) == this->_buffer1->end() && this->_buffer0->find(code) != this->_buffer0->end();
}

void KeyboardInput::update() {
    _buffer0->clear();
    auto* temp = _buffer0;
    _buffer0 = _buffer1;
    _buffer1 = temp;
}

} // namespace ngind::input