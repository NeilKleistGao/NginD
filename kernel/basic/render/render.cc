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
// FILENAME: render.cc

#include "glad/glad.h"

#include "render.h"

#include "display_settings.h"

namespace ngind {
Render* Render::_instance = nullptr;

Render* Render::getInstance() {
    if (_instance == nullptr) {
        _instance = new Render();
    }

    return _instance;
}

void Render::destroyInstance() {
    if (_instance != nullptr) {
        delete _instance;
        _instance = nullptr;
    }
}

Render::Render() :
_window(new Window(settings::WINDOW_WIDTH,
        settings::WINDOW_HEIGHT,
        settings::WINDOW_TITLE)) {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        glfwTerminate();
        exit(-1);
    }

    glad_glEnable(GL_TEXTURE_2D);

    this->_window->setIcon(settings::WINDOW_ICON);
}

Render::~Render() {
}

bool Render::startRenderLoopOnce() {
    if (this->_window->isLoopEnd()) {
        return false;
    }

    //TODO: render here

    this->_window->swapBuffer();
    return true;
}

} // namespace ngind