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
// LAST MODIFY: 2020/10/24
// FILENAME: input.h

#ifndef NGIND_INPUT_H
#define NGIND_INPUT_H

#include "keyboard_input.h"
#include "mouse_input.h"
#include "text_input.h"

#include "render/window.h"

namespace ngind {

class Input {
public:
    static Input* getInstance();
    static void destroyInstance();

    inline bool getKey(const KeyboardCode& code) {
        return this->_keyboard->getKey(this->_window_handler, code);
    }

    inline bool getKeyPressed(const KeyboardCode& code) {
        return this->_keyboard->getKeyPressed(this->_window_handler, code);
    }

    inline bool getKeyReleased(const KeyboardCode& code) {
        return this->_keyboard->getKeyReleased(this->_window_handler, code);
    }

    inline Vector2D getMousePressed(const MouseCode& code) {
        return this->_mouse->getMousePressed(_window_handler, code);
    }

    inline Vector2D getMouse(const MouseCode& code) {
        return this->_mouse->getMouse(_window_handler, code);
    }

    inline Vector2D getMouseReleased(const MouseCode& code) {
        return this->_mouse->getMouseReleased(_window_handler, code);
    }

    inline Vector2D getMouseMoving() {
        return this->_mouse->getMouseMoving(_window_handler);
    }

    inline std::string getString(const EncodingType& encoding) {
        return this->_text->getString(encoding);
    }

    friend class Window;
private:
    static Input* _instance;
    KeyboardInput* _keyboard;
    MouseInput* _mouse;
    TextInput* _text;
    GLFWwindow* _window_handler;

    inline void setWindowHandler(GLFWwindow* window) {
        _window_handler = window;
        this->_keyboard = new KeyboardInput(window);
        this->_mouse = new MouseInput(window);
        this->_text = new TextInput(window);
    }

    Input();
    ~Input();
};

} // namespace ngind

#endif //NGIND_INPUT_H
