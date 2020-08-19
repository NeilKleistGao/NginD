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
// LAST MODIFY: 2020/8/17
// FILENAME: window.h

#ifndef NGIND_WINDOW_H
#define NGIND_WINDOW_H

#include <iostream>
#include <cstdio>

#include "glfw3.h"

#include "png_image.h"

namespace ngind {
class Window {
public:
    Window(const size_t&, const size_t&, const std::string&);
    ~Window();

    inline bool isLoopEnd() {
        return glfwWindowShouldClose(this->_window);
    }

    inline void swapBuffer() {
        glfwSwapBuffers(this->_window);
    }

    void setIcon(const std::string&);
private:
    GLFWwindow *_window;
    PNGImage* _icon;
};
}

#endif //NGIND_WINDOW_H
