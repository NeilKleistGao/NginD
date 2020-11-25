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

/// @file input.cc
/// @date 2020/10/25

/// @brief This file includes the implementation of Input's functions.

#include "input.h"

namespace ngind {

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
    _text_mod(false){

}

Input::~Input() {
    delete _keyboard;
    _keyboard = nullptr;
    delete _mouse;
    _mouse = nullptr;
    delete _text;
    _text = nullptr;
}

} // namespace ngind