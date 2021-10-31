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

/// @file input.cc

#include "input.h"

namespace ngind::input {

Input* Input::_instance = nullptr;

Input* Input::getInstance() {
    if (_instance == nullptr) {
        _instance = new Input();
    }

    return _instance;
}

void Input::destroyInstance() {
    if (_instance != nullptr) {
        delete _instance;
        _instance = nullptr;
    }
}

Input::Input() :
    _keyboard(nullptr),
    _window_handler(nullptr),
    _mouse(nullptr),
    _text(nullptr),
    _text_mod(false),
    _interrupted(false) {
}

Input::~Input() {
    delete _keyboard;
    _keyboard = nullptr;
    delete _mouse;
    _mouse = nullptr;
    delete _text;
    _text = nullptr;
}

void Input::init() {
    auto state = script::LuaState::getInstance()->getState();
    auto key_code_table = luabridge::newTable(state);
    {
        key_code_table["UNKNOWN"] = static_cast<int>(KeyboardCode::UNKNOWN);
        key_code_table["SPACE"] = static_cast<int>(KeyboardCode::SPACE);
        key_code_table["APOSTROPHE"] = static_cast<int>(KeyboardCode::APOSTROPHE);
        key_code_table["COMMA"] = static_cast<int>(KeyboardCode::COMMA);
        key_code_table["MINUS"] = static_cast<int>(KeyboardCode::MINUS);
        key_code_table["PERIOD"] = static_cast<int>(KeyboardCode::PERIOD);
        key_code_table["SLASH"] = static_cast<int>(KeyboardCode::SLASH);
        key_code_table["NUM_0"] = static_cast<int>(KeyboardCode::NUM_0);
        key_code_table["NUM_1"] = static_cast<int>(KeyboardCode::NUM_1);
        key_code_table["NUM_2"] = static_cast<int>(KeyboardCode::NUM_2);
        key_code_table["NUM_3"] = static_cast<int>(KeyboardCode::NUM_3);
        key_code_table["NUM_4"] = static_cast<int>(KeyboardCode::NUM_4);
        key_code_table["NUM_5"] = static_cast<int>(KeyboardCode::NUM_5);
        key_code_table["NUM_6"] = static_cast<int>(KeyboardCode::NUM_6);
        key_code_table["NUM_7"] = static_cast<int>(KeyboardCode::NUM_7);
        key_code_table["NUM_8"] = static_cast<int>(KeyboardCode::NUM_8);
        key_code_table["NUM_9"] = static_cast<int>(KeyboardCode::NUM_9);
        key_code_table["SEMICOLON"] = static_cast<int>(KeyboardCode::SEMICOLON);
        key_code_table["EQUAL"] = static_cast<int>(KeyboardCode::EQUAL);
        key_code_table["ALP_A"] = static_cast<int>(KeyboardCode::ALP_A);
        key_code_table["ALP_B"] = static_cast<int>(KeyboardCode::ALP_B);
        key_code_table["ALP_C"] = static_cast<int>(KeyboardCode::ALP_C);
        key_code_table["ALP_D"] = static_cast<int>(KeyboardCode::ALP_D);
        key_code_table["ALP_E"] = static_cast<int>(KeyboardCode::ALP_E);
        key_code_table["ALP_F"] = static_cast<int>(KeyboardCode::ALP_F);
        key_code_table["ALP_G"] = static_cast<int>(KeyboardCode::ALP_G);
        key_code_table["ALP_H"] = static_cast<int>(KeyboardCode::ALP_H);
        key_code_table["ALP_I"] = static_cast<int>(KeyboardCode::ALP_I);
        key_code_table["ALP_J"] = static_cast<int>(KeyboardCode::ALP_J);
        key_code_table["ALP_K"] = static_cast<int>(KeyboardCode::ALP_K);
        key_code_table["ALP_L"] = static_cast<int>(KeyboardCode::ALP_L);
        key_code_table["ALP_M"] = static_cast<int>(KeyboardCode::ALP_M);
        key_code_table["ALP_N"] = static_cast<int>(KeyboardCode::ALP_N);
        key_code_table["ALP_O"] = static_cast<int>(KeyboardCode::ALP_O);
        key_code_table["ALP_P"] = static_cast<int>(KeyboardCode::ALP_P);
        key_code_table["ALP_Q"] = static_cast<int>(KeyboardCode::ALP_Q);
        key_code_table["ALP_R"] = static_cast<int>(KeyboardCode::ALP_R);
        key_code_table["ALP_S"] = static_cast<int>(KeyboardCode::ALP_S);
        key_code_table["ALP_T"] = static_cast<int>(KeyboardCode::ALP_T);
        key_code_table["ALP_U"] = static_cast<int>(KeyboardCode::ALP_U);
        key_code_table["ALP_V"] = static_cast<int>(KeyboardCode::ALP_V);
        key_code_table["ALP_W"] = static_cast<int>(KeyboardCode::ALP_W);
        key_code_table["ALP_X"] = static_cast<int>(KeyboardCode::ALP_X);
        key_code_table["ALP_Y"] = static_cast<int>(KeyboardCode::ALP_Y);
        key_code_table["ALP_Z"] = static_cast<int>(KeyboardCode::ALP_Z);
        key_code_table["LEFT_BRACKET"] = static_cast<int>(KeyboardCode::LEFT_BRACKET);
        key_code_table["BACKSLASH"] = static_cast<int>(KeyboardCode::BACKSLASH);
        key_code_table["RIGHT_BRACKET"] = static_cast<int>(KeyboardCode::RIGHT_BRACKET);
        key_code_table["GRAVE_ACCENT"] = static_cast<int>(KeyboardCode::GRAVE_ACCENT);
        key_code_table["ESCAPE"] = static_cast<int>(KeyboardCode::ESCAPE);
        key_code_table["ENTER"] = static_cast<int>(KeyboardCode::ENTER);
        key_code_table["TAB"] = static_cast<int>(KeyboardCode::TAB);
        key_code_table["BACKSPACE"] = static_cast<int>(KeyboardCode::BACKSPACE);
        key_code_table["INSERT"] = static_cast<int>(KeyboardCode::INSERT);
        key_code_table["DELETE"] = static_cast<int>(KeyboardCode::DELETE);
        key_code_table["RIGHT"] = static_cast<int>(KeyboardCode::RIGHT);
        key_code_table["LEFT"] = static_cast<int>(KeyboardCode::LEFT);
        key_code_table["DOWN"] = static_cast<int>(KeyboardCode::DOWN);
        key_code_table["PAGE_UP"] = static_cast<int>(KeyboardCode::PAGE_UP);
        key_code_table["PAGE_DOWN"] = static_cast<int>(KeyboardCode::PAGE_DOWN);
        key_code_table["HOME"] = static_cast<int>(KeyboardCode::HOME);
        key_code_table["END"] = static_cast<int>(KeyboardCode::END);
        key_code_table["CAPS_LOCK"] = static_cast<int>(KeyboardCode::CAPS_LOCK);
        key_code_table["SCROLL_LOCK"] = static_cast<int>(KeyboardCode::SCROLL_LOCK);
        key_code_table["NUM_LOCK"] = static_cast<int>(KeyboardCode::NUM_LOCK);
        key_code_table["PRINT_SCREEN"] = static_cast<int>(KeyboardCode::PRINT_SCREEN);
        key_code_table["PAUSE"] = static_cast<int>(KeyboardCode::PAUSE);
        key_code_table["KP_0"] = static_cast<int>(KeyboardCode::KP_0);
        key_code_table["KP_1"] = static_cast<int>(KeyboardCode::KP_1);
        key_code_table["KP_2"] = static_cast<int>(KeyboardCode::KP_2);
        key_code_table["KP_3"] = static_cast<int>(KeyboardCode::KP_3);
        key_code_table["KP_4"] = static_cast<int>(KeyboardCode::KP_4);
        key_code_table["KP_5"] = static_cast<int>(KeyboardCode::KP_5);
        key_code_table["KP_6"] = static_cast<int>(KeyboardCode::KP_6);
        key_code_table["KP_7"] = static_cast<int>(KeyboardCode::KP_7);
        key_code_table["KP_8"] = static_cast<int>(KeyboardCode::KP_8);
        key_code_table["KP_9"] = static_cast<int>(KeyboardCode::KP_9);
        key_code_table["KP_DECIMAL"] = static_cast<int>(KeyboardCode::KP_DECIMAL);
        key_code_table["KP_DIVIDE"] = static_cast<int>(KeyboardCode::KP_DIVIDE);
        key_code_table["KP_MULTIPLY"] = static_cast<int>(KeyboardCode::KP_MULTIPLY);
        key_code_table["KP_SUBTRACT"] = static_cast<int>(KeyboardCode::KP_SUBTRACT);
        key_code_table["KP_ADD"] = static_cast<int>(KeyboardCode::KP_ADD);
        key_code_table["KP_ENTER"] = static_cast<int>(KeyboardCode::KP_ENTER);
        key_code_table["KP_EQUAL"] = static_cast<int>(KeyboardCode::KP_EQUAL);
        key_code_table["LEFT_SHIFT"] = static_cast<int>(KeyboardCode::LEFT_SHIFT);
        key_code_table["LEFT_CONTROL"] = static_cast<int>(KeyboardCode::LEFT_CONTROL);
        key_code_table["LEFT_ALT"] = static_cast<int>(KeyboardCode::LEFT_ALT);
        key_code_table["LEFT_SUPER"] = static_cast<int>(KeyboardCode::LEFT_SUPER);
        key_code_table["RIGHT_SHIFT"] = static_cast<int>(KeyboardCode::RIGHT_SHIFT);
        key_code_table["RIGHT_CONTROL"] = static_cast<int>(KeyboardCode::RIGHT_CONTROL);
        key_code_table["RIGHT_ALT"] = static_cast<int>(KeyboardCode::RIGHT_ALT);
        key_code_table["RIGHT_SUPER"] = static_cast<int>(KeyboardCode::RIGHT_SUPER);
    }
    luabridge::setGlobal(state, key_code_table, "KEY_CODE");

    auto mouse_code_table = luabridge::newTable(state);
    {
        mouse_code_table["BUTTON_LEFT"] = static_cast<int>(MouseCode::BUTTON_LEFT);
        mouse_code_table["BUTTON_RIGHT"] = static_cast<int>(MouseCode::BUTTON_RIGHT);
        mouse_code_table["BUTTON_MIDDLE"] = static_cast<int>(MouseCode::BUTTON_MIDDLE);
    }
    luabridge::setGlobal(state, mouse_code_table, "MOUSE_CODE");
}

void Input::update() {
    _keyboard->update();
    _mouse->update();
}

void GLFWKeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    auto input = Input::getInstance();
    auto keyboard = input->_keyboard;
    auto key_code = static_cast<KeyboardCode>(key);

    if (action == GLFW_PRESS) {
        keyboard->_buffer1->insert(key_code);
    }
}

void GLFWMouseCallback(GLFWwindow* window, int key, int action, int mods) {
    auto input = Input::getInstance();
    auto mouse = input->_mouse;
    auto mouse_code = static_cast<MouseCode>(key);

    if (action == GLFW_PRESS) {
        mouse->_buffer1->insert(mouse_code);
    }
}

} // namespace ngind::input