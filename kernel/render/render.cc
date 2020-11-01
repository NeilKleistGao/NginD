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
// LAST MODIFY: 2020/11/1
// FILENAME: render.cc

#include "GL/glew.h"

#include "render.h"

#include <cassert>

unsigned char temp[958 * 943 * 3];

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

    glViewport(0, 0, width, height);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    Perspective::getInstance()->init({width / 2.0f, height / 2.0f}, width, height);Perspective::getInstance()->init({width / 2.0f, height / 2.0f}, width, height);

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
    cmd->program->use();

    glm::mat4 model;
    model = glm::translate(model, glm::vec3(cmd->position.getX(), cmd->position.getY(), 0));
    model = glm::translate(model, glm::vec3(0.5f * cmd->size.getX(), 0.5f * cmd->size.getY(), 0));
    model = glm::rotate(model, cmd->rotate, glm::vec3(0, 0, 1));
    model = glm::translate(model, glm::vec3(-0.5f * cmd->size.getX(), -0.5f * cmd->size.getY(), 0));
    model = glm::scale(model, glm::vec3(cmd->scale.getX(), cmd->scale.getY(), 1));

    cmd->program->setMatrix4("model", model);
    cmd->program->setVector4("spriteColor", glm::vec4(cmd->color.r / 255.0f,
                                                      cmd->color.g  / 255.0f,
                                                      cmd->color.b / 255.0f,
                                                      cmd->color.a / 255.0f));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, cmd->texture_id);
    glBindVertexArray(cmd->quad->getVAO());
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

} // namespace ngind