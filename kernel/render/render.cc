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

/// @file render.cc
/// @date 2020/11/1

#include "GL/glew.h"

#include "render.h"
#include "perspective.h"

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

    glfwTerminate();
}

Render::Render()
    : _window(nullptr), _queue(nullptr) {
    _queue = new RenderQueue();
}

Render::~Render() {
    delete _window;
    _window = nullptr;
}

bool Render::startRenderLoopOnce() {
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

void Render::createWindow(const int& width,
                  const int& height,
                  const std::string& title,
                  const std::string& icon,
                  const bool& is_full) {
    this->_window = new Window(width, height, title, is_full);
    this->_window->setIcon(icon);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        //TODO: init error
        exit(-1);
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    Perspective::getInstance()->init({width / 2.0f, height / 2.0f}, width, height);
}

void Render::execute(RenderCommand* cmd) {
    switch (cmd->type) {
        case RenderCommandType::QUAD_COMMAND:
            drawQuad(static_cast<QuadRenderCommand*>(cmd));
            break;
        default:
            break;
    }
}

void Render::drawQuad(QuadRenderCommand* cmd) {
    glBindTexture(GL_TEXTURE_2D, cmd->texture_id);
    cmd->program->use();
    glBindVertexArray(cmd->quad->getVAO());
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

} // namespace ngind