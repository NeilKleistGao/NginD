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
// LAST MODIFY: 2020/8/29
// FILENAME: input.h

#ifndef NGIND_INPUT_H
#define NGIND_INPUT_H

#include "keyboard_input.h"

#include "render/window.h"

namespace ngind {

class Input {
public:
    static Input* getInstance();
    static void destroyInstance();

    inline bool getKey(const std::string& name) {
        return this->_keyboard->getKey(this->_window_handler, name);
    }

    inline bool getKeyPressed(const std::string& name) {
        return this->_keyboard->getKeyPressed(this->_window_handler, name);
    }

    inline bool getKeyReleased(const std::string& name) {
        return this->_keyboard->getKeyReleased(this->_window_handler, name);
    }

    inline void registerKeyCodeName(const std::string& name, const KeyboardCode& code) {
        this->_keyboard->setCode(name, code);
    }

    inline KeyboardCode getKeyCodeByName(const std::string& name) {
        return this->_keyboard->getCode(name);
    }

    friend class Window;

private:
    static Input* _instance;
    KeyboardInput* _keyboard;
    GLFWwindow* _window_handler;

    inline void setWindowHandler(GLFWwindow* window) {
        _window_handler = window;
        this->_keyboard = new KeyboardInput(window);
    }

    Input();
    ~Input();
};

} // namespace ngind

#endif //NGIND_INPUT_H
