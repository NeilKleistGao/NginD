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

/// @file window.cc
/// @date 2020/11/1

#include "window.h"

#include "input/input.h"

namespace ngind {

Window::Window(const size_t& width,
        const size_t& height,
        const std::string& title,
        const bool& is_full) : _window(nullptr), _icon(nullptr) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    if (is_full) {
        this->_window = glfwCreateWindow(width, height, title.c_str(), glfwGetPrimaryMonitor(), nullptr);
    }
    else {
        this->_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    }

    if (this->_window == nullptr) {
        glfwTerminate();
        exit(-1);
    }

    glfwMakeContextCurrent(this->_window);
    Input::getInstance()->setWindowHandler(this->_window);
}

Window::~Window() {
    glfwDestroyWindow(this->_window);
    this->_window = nullptr;

    delete this->_icon;
    this->_icon = nullptr;
}

void Window::setIcon(const std::string& path) {
    if (this->_icon != nullptr) {
        delete this->_icon;
        this->_icon = nullptr;
    }

    this->_icon = new PNGImage(PNGImage::IMAGE_RESOURCE_PATH + "/" + path);
    glfwSetWindowIcon(this->_window, 1, this->_icon->getImageData());
}

} // namespace ngind