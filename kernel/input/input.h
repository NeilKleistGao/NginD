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

/// @file input.h

#ifndef NGIND_INPUT_H
#define NGIND_INPUT_H

#include "keyboard_input.h"
#include "mouse_input.h"
#include "text_input.h"

#include "rendering/window.h"

namespace ngind::input {
/**
 * This class is in duty to manage all kinds of input event. This is a singleton
 * class so you should use getInstance/destroyInstance rather than new/delete.
 */
class Input {
public:
    /**
     * Get Input instance. If the instance is null, create one.
     * @return Input*, the Input instance
     */
    static Input* getInstance();

    /**
     * Destroy the instance.
     */
    static void destroyInstance();

    /**
     * Get whether some key is being pressed.
     * @param code: the key's code that should be checked
     * @return bool, true if user keeps press
     */
    inline bool getKey(const KeyboardCode& code) {
        return !_text_mod && this->_keyboard->getKey(this->_window_handler, code);
    }

    /**
     * Get whether some key is pressed firstly.
     * @param code: the key's code that should be checked
     * @return bool, true if user firstly presses this key
     */
    inline bool getKeyPressed(const KeyboardCode& code) {
        return !_text_mod && this->_keyboard->getKeyPressed(this->_window_handler, code);
    }

    /**
     * Get whether some key is released.
     * @param code: the key's code that should be checked
     * @return bool, true if user releases this key
     */
    inline bool getKeyReleased(const KeyboardCode& code) {
        return !_text_mod && this->_keyboard->getKeyReleased(this->_window_handler, code);
    }

    /**
     * Get whether some mouse key is clicked firstly.
     * @param code: the mouse key's code
     * @return Vector2D, the mouse's position, Vector2D::INVALID if user never clicks
     */
    inline Vector2D getMousePressed(const MouseCode& code) {
        return this->_mouse->getMousePressed(_window_handler, code);
    }

    /**
     * Get whether some mouse key is being clicked.
     * @param code: the mouse key's code
     * @return Vector2D, the mouse's position, Vector2D::INVALID if user never clicks
     */
    inline Vector2D getMouse(const MouseCode& code) {
        return this->_mouse->getMouse(_window_handler, code);
    }

    /**
     * Get whether some mouse key is released.
     * @param code: the mouse key's code
     * @return Vector2D, the mouse's position, Vector2D::INVALID if user never clicks
     */
    inline Vector2D getMouseReleased(const MouseCode& code) {
        return this->_mouse->getMouseReleased(_window_handler, code);
    }

    /**
     * Get current mouse's position.
     * @return Vector2D, the mouse's position
     */
    inline Vector2D getMouseMoving() {
        return this->_mouse->getMouseMoving(_window_handler);
    }

    /**
     * Get user's text input
     * @param encoding: the encoding type of text
     * @return std::string, the text input
     */
    inline std::string getString(const EncodingType& encoding) {
        if (!_text_mod) {
            return "";
        }
        return this->_text->getString(encoding);
    }

    /**
     * set whether current manager should get text input or keyboard input
     * @param is_enable: true if manager should get text input
     */
    inline void switchTextMod(const bool& is_enable) {
        _text_mod = is_enable;
    }

    friend class ngind::rendering::Window;
private:
    /**
     * The instance object
     */
    static Input* _instance;

    /**
     * The instance of keyboard input
     */
    KeyboardInput* _keyboard;

    /**
     * The instance of mouse input
     */
    MouseInput* _mouse;

    /**
     * The instance of text input
     */
    TextInput* _text;

    /**
     * The handler of glfw window
     */
    GLFWwindow* _window_handler;

    /**
     * Is manager should get text input
     */
    bool _text_mod;

    /**
     * Set the glfw window's handler.
     * @param window: the pointer of window
     */
    inline void setWindowHandler(GLFWwindow* window) {
        _window_handler = window;
        this->_keyboard = new KeyboardInput(window);
        this->_mouse = new MouseInput(window);
        this->_text = new TextInput(window);
    }

    Input();

    ~Input();
};

} // namespace ngind::input

#endif //NGIND_INPUT_H
