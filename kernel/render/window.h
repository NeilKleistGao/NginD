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
// LAST MODIFY: 2020/10/31
// FILENAME: window.h

#ifndef NGIND_WINDOW_H
#define NGIND_WINDOW_H

#include <iostream>
#include <cstdio>

#include "include/opengl/glfw3.h"

#include "png_image.h"

namespace ngind {
class Window {
public:
    Window(const size_t&, const size_t&, const std::string&, const bool& is_full = false);
    ~Window();

    void setIcon(const std::string&);

    inline bool isLoopEnd() {
        return glfwWindowShouldClose(this->_window);
    }

    inline void swapBuffer() {
        glfwSwapBuffers(this->_window);
    }

    inline std::pair<float, float> getContentScale() {
        float x_scale, y_scale;
        glfwGetWindowContentScale(this->_window, &x_scale, &y_scale);
        return {x_scale, y_scale};
    }

    inline void setTitle(const std::string& title) {
        glfwSetWindowTitle(this->_window, title.c_str());
    }

    inline void setFullScreen(const bool& is_full) {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);

        if (is_full) {
            glfwSetWindowMonitor(this->_window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
        }
        else {
            glfwSetWindowMonitor(this->_window, nullptr, 0, 0, mode->width, mode->height, 0);
        }
    }

    inline void resize(const size_t& width, const size_t& height) {
        glfwSetWindowSize(this->_window, width, height);
    }

private:
    GLFWwindow *_window;
    PNGImage* _icon;
};
}

#endif //NGIND_WINDOW_H
