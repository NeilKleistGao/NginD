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

/// @file rendering.cc

#include "GL/glew.h"

#include "renderer.h"
#include "camera.h"
#include "log/logger_factory.h"

namespace ngind::rendering {
Renderer* Renderer::_instance = nullptr;

Renderer* Renderer::getInstance() {
    if (_instance == nullptr) {
        _instance = new(std::nothrow) Renderer();
        if (_instance == nullptr) {
            auto logger = log::LoggerFactory::getInstance()->getLogger("crash.log", log::LogLevel::LOG_LEVEL_ERROR);
            logger->log("Can't create renderer instance.");
            logger->flush();
        }
    }

    return _instance;
}

void Renderer::destroyInstance() {
    if (_instance != nullptr) {
        delete _instance;
        _instance = nullptr;
    }

    glfwTerminate();
}

Renderer::Renderer()
    : _window(nullptr), _queue(new RenderingQueue()), _multisampling(true) {
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}

Renderer::~Renderer() {
    delete _window;
    _window = nullptr;
}

bool Renderer::startRenderingLoopOnce() {
    if (this->_window->isLoopEnd()) {
        return false;
    }

    _queue->sort();
    for (auto cmd : (*_queue)) {
        this->execute(cmd);
    }

    _queue->clear();
    this->_window->swapBuffer();
    return true;
}

void Renderer::createWindow(int screen_width,
                            int screen_height,
                            int resolution_width,
                            int resolution_height,
                            const std::string& title,
                            const std::string& icon,
                            bool is_full) {
    this->_window = new Window(screen_width, screen_height, title, is_full);
    this->_window->setIcon(icon);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        auto logger = log::LoggerFactory::getInstance()->getLogger("crash.log", log::LogLevel::LOG_LEVEL_ERROR);
        logger->log("Can't create initialize OpenGL.");
        logger->flush();
    }

    glEnable(GL_BLEND);
    setBlendFactor(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_MULTISAMPLE);
    Camera::getInstance()->init({resolution_width / 2.0f, resolution_height / 2.0f},
                                resolution_width, resolution_height);
}

void Renderer::execute(RenderingCommand* cmd) {
    cmd->prepare();
    cmd->call();
}

void Renderer::enableMultisampling(const bool& en) {
    if (en) {
        glEnable(GL_MULTISAMPLE);
    }
    else {
        glDisable(GL_MULTISAMPLE);
    }

    _multisampling = en;
}

} // namespace ngind::rendering