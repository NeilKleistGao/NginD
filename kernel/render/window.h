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
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/// @file window.h

#ifndef NGIND_WINDOW_H
#define NGIND_WINDOW_H

#include <iostream>
#include <cstdio>

#include "include/opengl/glfw3.h"

namespace ngind {

/**
 * Window management class. It's an encapsulation for glfw window.
 */
class Window {
public:
    /**
     * @param width: width of window
     * @param height: height of window
     * @param title: title of window
     * @param is_full: true if window should be fullscreen and default is false
     */
    Window(const size_t& width, const size_t& height, const std::string& title, const bool& is_full = false);

    ~Window();

    /**
     * Set an icon for this window.
     * @param path: path of icon file
     */
    void setIcon(const std::string& path);

    /**
     * Test if user closed this window.
     * @return bool, true if window was closed
     */
    inline bool isLoopEnd() {
        return glfwWindowShouldClose(this->_window);
    }

    /**
     * Swap render buffers.
     */
    inline void swapBuffer() {
        glfwSwapBuffers(this->_window);
    }

    /**
     * Get the scale of window.
     * @return std::pair<float, float>, scale vector
     */
    inline std::pair<float, float> getContentScale() {
        float x_scale, y_scale;
        glfwGetWindowContentScale(this->_window, &x_scale, &y_scale);
        return {x_scale, y_scale};
    }

    /**
     * Set title of window.
     * @param title: title of window
     */
    inline void setTitle(const std::string& title) {
        glfwSetWindowTitle(this->_window, title.c_str());
    }

    /**
     * Set fullscreen state of window.
     * @param is_full: true if window should be fullscreen
     */
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

    /**
     * Resize window,
     * @param width: width of window
     * @param height: height of window
     */
    inline void resize(const size_t& width, const size_t& height) {
        glfwSetWindowSize(this->_window, width, height);
    }

private:
    /**
     * Pointer to GLFWwindow.
     */
    GLFWwindow *_window;

    /**
     * Icon data.
     */
    GLFWimage* _icon;
};
} // namespace ngind

#endif //NGIND_WINDOW_H
