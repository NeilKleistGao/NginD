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
// LAST MODIFY: 2020/8/18
// FILENAME: display_settings.h

#ifndef NGIND_DISPLAY_SETTINGS_H
#define NGIND_DISPLAY_SETTINGS_H

#include <iostream>
#include <cstdio>

namespace ngind {
namespace settings {

// window size
const size_t WINDOW_WIDTH = 1024;
const size_t WINDOW_HEIGHT = 768;

// window title
const std::string WINDOW_TITLE = "Rolling With The Dice!";

// window icon
const std::string WINDOW_ICON = "images/dice.png";

} // namespace settings
} // namespace ngind

#endif //NGIND_DISPLAY_SETTINGS_H
