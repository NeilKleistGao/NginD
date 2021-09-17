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

/// @file keyboard_input.h

#ifndef NGIND_KEYBOARD_INPUT_H
#define NGIND_KEYBOARD_INPUT_H

#include <set>

#include "glfw3.h"

namespace ngind::input {

/**
* The keyboard code for keyboard input. It's a simple map for GLFW_KEY prefixing
* macros.
 */
enum class KeyboardCode {
    UNKNOWN = GLFW_KEY_UNKNOWN,
    SPACE = GLFW_KEY_SPACE,
    APOSTROPHE = GLFW_KEY_APOSTROPHE,
    COMMA = GLFW_KEY_COMMA,
    MINUS = GLFW_KEY_MINUS,
    PERIOD = GLFW_KEY_PERIOD,
    SLASH = GLFW_KEY_SLASH,
    NUM_0 = GLFW_KEY_0,
    NUM_1 = GLFW_KEY_1,
    NUM_2 = GLFW_KEY_2,
    NUM_3 = GLFW_KEY_3,
    NUM_4 = GLFW_KEY_4,
    NUM_5 = GLFW_KEY_5,
    NUM_6 = GLFW_KEY_6,
    NUM_7 = GLFW_KEY_7,
    NUM_8 = GLFW_KEY_8,
    NUM_9 = GLFW_KEY_9,
    SEMICOLON = GLFW_KEY_SEMICOLON,
    EQUAL = GLFW_KEY_EQUAL,
    ALP_A = GLFW_KEY_A,
    ALP_B = GLFW_KEY_B,
    ALP_C = GLFW_KEY_C,
    ALP_D = GLFW_KEY_D,
    ALP_E = GLFW_KEY_E,
    ALP_F = GLFW_KEY_F,
    ALP_G = GLFW_KEY_G,
    ALP_H = GLFW_KEY_H,
    ALP_I = GLFW_KEY_I,
    ALP_J = GLFW_KEY_J,
    ALP_K = GLFW_KEY_K,
    ALP_L = GLFW_KEY_L,
    ALP_M = GLFW_KEY_M,
    ALP_N = GLFW_KEY_N,
    ALP_O = GLFW_KEY_O,
    ALP_P = GLFW_KEY_P,
    ALP_Q = GLFW_KEY_Q,
    ALP_R = GLFW_KEY_R,
    ALP_S = GLFW_KEY_S,
    ALP_T = GLFW_KEY_T,
    ALP_U = GLFW_KEY_U,
    ALP_V = GLFW_KEY_V,
    ALP_W = GLFW_KEY_W,
    ALP_X = GLFW_KEY_X,
    ALP_Y = GLFW_KEY_Y,
    ALP_Z = GLFW_KEY_Z,
    LEFT_BRACKET = GLFW_KEY_LEFT_BRACKET,
    BACKSLASH = GLFW_KEY_BACKSLASH,
    RIGHT_BRACKET = GLFW_KEY_RIGHT_BRACKET,
    GRAVE_ACCENT = GLFW_KEY_GRAVE_ACCENT,
    ESCAPE = GLFW_KEY_ESCAPE,
    ENTER = GLFW_KEY_ENTER,
    TAB = GLFW_KEY_TAB,
    BACKSPACE = GLFW_KEY_BACKSPACE,
    INSERT = GLFW_KEY_INSERT,
    DELETE = GLFW_KEY_DELETE,
    RIGHT = GLFW_KEY_RIGHT,
    LEFT = GLFW_KEY_LEFT,
    DOWN = GLFW_KEY_DOWN,
    PAGE_UP = GLFW_KEY_PAGE_UP,
    PAGE_DOWN = GLFW_KEY_PAGE_DOWN,
    HOME = GLFW_KEY_HOME,
    END = GLFW_KEY_END,
    CAPS_LOCK = GLFW_KEY_CAPS_LOCK,
    SCROLL_LOCK = GLFW_KEY_SCROLL_LOCK,
    NUM_LOCK = GLFW_KEY_NUM_LOCK,
    PRINT_SCREEN = GLFW_KEY_PRINT_SCREEN,
    PAUSE = GLFW_KEY_PAUSE,
    KP_0 = GLFW_KEY_KP_0,
    KP_1 = GLFW_KEY_KP_1,
    KP_2 = GLFW_KEY_KP_2,
    KP_3 = GLFW_KEY_KP_3,
    KP_4 = GLFW_KEY_KP_4,
    KP_5 = GLFW_KEY_KP_5,
    KP_6 = GLFW_KEY_KP_6,
    KP_7 = GLFW_KEY_KP_7,
    KP_8 = GLFW_KEY_KP_8,
    KP_9 = GLFW_KEY_KP_9,
    KP_DECIMAL = GLFW_KEY_KP_DECIMAL,
    KP_DIVIDE = GLFW_KEY_KP_DIVIDE,
    KP_MULTIPLY = GLFW_KEY_KP_MULTIPLY,
    KP_SUBTRACT = GLFW_KEY_KP_SUBTRACT,
    KP_ADD = GLFW_KEY_KP_ADD,
    KP_ENTER = GLFW_KEY_KP_ENTER,
    KP_EQUAL = GLFW_KEY_KP_EQUAL,
    LEFT_SHIFT = GLFW_KEY_LEFT_SHIFT,
    LEFT_CONTROL = GLFW_KEY_LEFT_CONTROL,
    LEFT_ALT = GLFW_KEY_LEFT_ALT,
    LEFT_SUPER = GLFW_KEY_LEFT_SUPER,
    RIGHT_SHIFT = GLFW_KEY_RIGHT_SHIFT,
    RIGHT_CONTROL = GLFW_KEY_RIGHT_CONTROL,
    RIGHT_ALT = GLFW_KEY_RIGHT_ALT,
    RIGHT_SUPER = GLFW_KEY_RIGHT_SUPER
};

/**
 * The keyboard input manager. This is a more sophisticated interface with
 * GLFWwindow as a param. Use Input class instead.
 */
class KeyboardInput {
public:
    /**
     * @param window: the GLFW window that is the event listener
     */
    explicit KeyboardInput(GLFWwindow* window);

    ~KeyboardInput() = default;

    /**
     * @see kernel/input/input.h
     */
    bool getKeyPressed(GLFWwindow* window, const KeyboardCode& code);

    /**
     * @see kernel/input/input.h
     */
    bool getKey(GLFWwindow* window, const KeyboardCode& code);

    /**
     * @see kernel/input/input.h
     */
    bool getKeyReleased(GLFWwindow* window, const KeyboardCode& code);

private:
    /**
     * Record the press state of all keys
     */
    std::set<KeyboardCode> _pressed;
};

} // namespace ngind::input

#endif //NGIND_KEYBOARD_INPUT_H
