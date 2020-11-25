/** MIT License
Copyright (c) 2020 NeilKleistGao
    Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/// @file input.h
/// @date 2020/10/25

/**
@brief
    This file includes the class used to deal with all input from users. Use this
file directly rather than use some specific input class.
*/

#ifndef NGIND_INPUT_H
#define NGIND_INPUT_H

#include "keyboard_input.h"
#include "mouse_input.h"
#include "text_input.h"

#include "render/window.h"

namespace ngind {


/**
@class
    This class is in duty to manage all kinds of input event. This is a singleton
class so you should use getInstance/destroyInstance rather than new/delete.
*/
class Input {
public:
    /// @public
    /// @static
    /// @fn Get Input instance. If the instance is null, create one.
    /// @param void
    /// @return Input*, the Input instance
    static Input* getInstance();

    /// @public
    /// @static
    /// @fn Destroy the instance.
    /// @param void
    /// @return void
    static void destroyInstance();

    /// @public
    /// @fn Get whether some key is being pressed
    /// @param const KeyboardCode& code: the key's code that should be checked
    /// @return bool, true if user keeps press
    inline bool getKey(const KeyboardCode& code) {
        return !_text_mod && this->_keyboard->getKey(this->_window_handler, code);
    }

    /// @public
    /// @fn Get whether some key is pressed firstly
    /// @param const KeyboardCode& code: the key's code that should be checked
    /// @return bool, true if user firstly presses this key
    inline bool getKeyPressed(const KeyboardCode& code) {
        return !_text_mod && this->_keyboard->getKeyPressed(this->_window_handler, code);
    }

    /// @public
    /// @fn Get whether some key is released
    /// @param const KeyboardCode& code: the key's code that should be checked
    /// @return bool, true if user releases this key
    inline bool getKeyReleased(const KeyboardCode& code) {
        return !_text_mod && this->_keyboard->getKeyReleased(this->_window_handler, code);
    }

    /// @public
    /// @fn Get whether some mouse key is clicked firstly
    /// @param const MouseCode& code: the mouse key's code
    /// @return Vector2D, the mouse's position, Vector2D::INVALID if user never clicks
    inline Vector2D getMousePressed(const MouseCode& code) {
        return this->_mouse->getMousePressed(_window_handler, code);
    }

    /// @public
    /// @fn Get whether some mouse key is being clicked
    /// @param const MouseCode& code: the mouse key's code
    /// @return Vector2D, the mouse's position, Vector2D::INVALID if user never clicks
    inline Vector2D getMouse(const MouseCode& code) {
        return this->_mouse->getMouse(_window_handler, code);
    }

    /// @public
    /// @fn Get whether some mouse key is released
    /// @param const MouseCode& code: the mouse key's code
    /// @return Vector2D, the mouse's position, Vector2D::INVALID if user never clicks
    inline Vector2D getMouseReleased(const MouseCode& code) {
        return this->_mouse->getMouseReleased(_window_handler, code);
    }

    /// @public
    /// @fn Get current mouse's position
    /// @param void
    /// @return Vector2D, the mouse's position
    inline Vector2D getMouseMoving() {
        return this->_mouse->getMouseMoving(_window_handler);
    }

    /// @public
    /// @fn Get user's text input
    /// @param const EncodingType& encoding: the encoding type of text
    /// @return std::string, the text input
    inline std::string getString(const EncodingType& encoding) {
        if (!_text_mod) {
            return "";
        }
        return this->_text->getString(encoding);
    }

    /// @public
    /// @fn set whether current manager should get text input or keyboard input
    /// @param const bool& is_enable: true if manager should get text input
    /// @return void
    inline void switchTextMod(const bool& is_enable) {
        _text_mod = is_enable;
    }

    /// Allow Window class access to function setWindowHandler
    /// @see kernel/render/window.h
    friend class Window;
private:
    /// @private
    /// @static
    /// @property The instance object
    static Input* _instance;

    /// @private
    /// @property The instance of keyboard input
    KeyboardInput* _keyboard;

    /// @private
    /// @property The instance of mouse input
    MouseInput* _mouse;

    /// @private
    /// @property The instance of text input
    TextInput* _text;

    /// @private
    /// @property The handler of glfw window
    GLFWwindow* _window_handler;

    /// @private
    /// @property Is manager should get text input
    bool _text_mod;

    /// @private
    /// @fn Set the glfw window's handler
    /// @param GLFWwindow* window: the pointer of window
    /// @return void
    inline void setWindowHandler(GLFWwindow* window) {
        _window_handler = window;
        this->_keyboard = new KeyboardInput(window);
        this->_mouse = new MouseInput(window);
        this->_text = new TextInput(window);
    }

    /// @private
    /// @note Newing a input instance is not allowed outside the getInstance function
    Input();

    /// @private
    /// @note Deleting a input instance is not allowed outside the getInstance function
    ~Input();
};

} // namespace ngind

#endif //NGIND_INPUT_H
