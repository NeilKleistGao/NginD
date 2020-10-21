// MIT License
//
// Copyright (c) 2020 NeilKleistGao
//
//        Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
//        to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//        copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
//        copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//        AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// LAST MODIFY: 2020/10/21
// FILENAME: keyboard_input.cc

#include "keyboard_input.h"

namespace ngind {

KeyboardInput::KeyboardInput(GLFWwindow* window) {
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
}

KeyboardInput::~KeyboardInput() {
    this->_map.clear();
    this->_pressed.clear();
}

bool KeyboardInput::getKey(GLFWwindow *window, const std::string& name) {
    KeyboardCode code = this->getCode(name);
    int state = glfwGetKey(window, code);

    if (state == GLFW_PRESS) {
        if (this->_pressed.find(code) == this->_pressed.end()) {
            this->_pressed.insert(code);
        }
        else {
            return true;
        }
    }
    else if (this->_pressed.find(code) != this->_pressed.end()) {
        this->_pressed.erase(code);
    }

    return false;
}

bool KeyboardInput::getKeyPressed(GLFWwindow* window, const std::string& name) {
    KeyboardCode code = this->getCode(name);
    int state = glfwGetKey(window, code);

    if (state == GLFW_PRESS) {
        if (this->_pressed.find(code) == this->_pressed.end()) {
            this->_pressed.insert(code);
            return true;
        }
    }
    else if (this->_pressed.find(code) != this->_pressed.end()) {
        this->_pressed.erase(code);
    }

    return false;
}

bool KeyboardInput::getKeyReleased(GLFWwindow* window, const std::string& name) {
    KeyboardCode code = this->getCode(name);
    int state = glfwGetKey(window, code);

    if (state == GLFW_RELEASE) {
        if (this->_pressed.find(code) != this->_pressed.end()) {
            this->_pressed.erase(code);
            return true;
        }
    }
    else if (this->_pressed.find(code) == this->_pressed.end()) {
        this->_pressed.insert(code);
    }

    return false;
}

} // namespace ngind