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

/// @file sprite_render.cc

#include "sprite.h"

#include <vector>

#include "rendering/renderer.h"
#include "rendering/camera.h"
#include "resources/resources_manager.h"
#include "memory/memory_pool.h"
#include "log/logger_factory.h"

namespace ngind::components {

Sprite::Sprite()
        : RendererComponent(),
        _command(nullptr), _quad(nullptr),
        _texture(nullptr), _lb(), _rt() {
}

Sprite::~Sprite() {
    if (_command != nullptr) {
        _quad->removeReference();
        _quad = nullptr;

        _command->removeReference();
        _command = nullptr;
    }

    if (_texture != nullptr) {
        resources::ResourcesManager::getInstance()->release(_texture);
        _texture = nullptr;
    }
}

void Sprite::update(const float& delta) {
    RendererComponent::update(delta);
    this->draw();
}

void Sprite::setImage(const std::string& filename) {
    if (_texture != nullptr && _texture->getResourcePath() == filename) {
        return;
    }

    if (_texture != nullptr) {
        resources::ResourcesManager::getInstance()->release(_texture->getResourcePath());
    }
    _texture = resources::ResourcesManager::getInstance()->load<resources::TextureResource>(filename);
    this->setBound({0, 0}, (*_texture)->getSize());
}

void Sprite::setImage(const std::string& filename, const glm::vec2& lb, const glm::vec2& rt) {
    this->setImage(filename);
    this->setBound(lb, rt);
}

void Sprite::draw() {
    if (_parent == nullptr || _texture == nullptr) {
        return;
    }

    auto temp = dynamic_cast<objects::EntityObject*>(_parent);

    if (_command == nullptr || _dirty) {
        if (_command != nullptr) {
            _quad->removeReference();
            _quad = nullptr;

            _command->removeReference();
            _command = nullptr;
        }

        auto texture_size = (*_texture)->getSize();
        _quad = memory::MemoryPool::getInstance()->create<rendering::Quad, std::initializer_list<GLfloat>>(
                {
                        _rt.x - _lb.x, _rt.y - _lb.y, static_cast<float>(_rt.x) / texture_size.x, static_cast<float>(_lb.y) / texture_size.y, // Top Right
                        _rt.x - _lb.x, 0.0f, static_cast<float>(_rt.x) / texture_size.x, static_cast<float>(_rt.y) / texture_size.y, // Bottom Right
                        0.0f, 0.0f, static_cast<float>(_lb.x) / texture_size.x, static_cast<float>(_rt.y) / texture_size.y, // Bottom Left
                        0.0f, _rt.y - _lb.y, static_cast<float>(_lb.x) / texture_size.x, static_cast<float>(_lb.y) / texture_size.y  // Top Left
                }
                );
        _quad->addReference();
        _command = memory::MemoryPool::getInstance()
                ->create<rendering::QuadRenderingCommand>(_quad, (*_texture)->getTextureID());
        _command->addReference();

        _command->setModel(getModelMatrix());
        _command->setColor(_color);
        _command->setZ(temp->getZOrder());
        _command->setProgram(_program->get());

        _dirty = false;
    }

    rendering::Renderer::getInstance()->addRendererCommand(_command);
}

void Sprite::init(const typename resources::ConfigResource::JsonObject& data) {
    try {
        _component_name = data["type"].GetString();
        std::string name = data["filename"].GetString();
        if (!name.empty()) {
            this->setImage(name);
        }
        _program = resources::ResourcesManager::getInstance()->load<resources::ProgramResource>(data["shader"].GetString());

        auto boundary = data["boundary"].GetObject();
        auto lb = boundary["left-bottom"].GetObject();
        auto rt = boundary["right-up"].GetObject();

        _lb.x = lb["x"].GetFloat(); _lb.y = lb["y"].GetFloat();
        _rt.x = rt["x"].GetFloat(); _rt.y = rt["y"].GetFloat();

        _color = rendering::Color{data["color"].GetString()};
    }
    catch (...) {
        auto logger = log::LoggerFactory::getInstance()->getLogger("crash.log", log::LogLevel::LOG_LEVEL_ERROR);
        logger->log("Can't create sprite component.");
        logger->flush();
    }
}

Sprite* Sprite::create(const typename resources::ConfigResource::JsonObject& data) {
    auto* com = memory::MemoryPool::getInstance()->create<Sprite>();
    com->init(data);
    return com;
}

glm::mat4 Sprite::getModelMatrix() {
    auto temp = dynamic_cast<objects::EntityObject*>(_parent);
    auto pos = temp->getPosition();
    auto rotate = temp->getRotation();
    auto scale = temp->getScale();
    auto anchor = temp->getAnchor();
    auto texture_size = (*_texture)->getSize();

    glm::mat4 model{1.0f};
    model = glm::translate(model, glm::vec3{pos.x - texture_size.x * scale.x * anchor.x,
                                            pos.y - texture_size.y * scale.y * anchor.y, 0.0f});
    model = glm::translate(model, glm::vec3{texture_size.x * scale.x * anchor.x,
                                            texture_size.y * scale.y * anchor.y, 0.0f});
    model = glm::rotate(model, rotate, glm::vec3{0.0f, 0.0f, 1.0f});
    model = glm::translate(model, glm::vec3{-texture_size.x * scale.x * anchor.x,
                                            -texture_size.y * scale.y * anchor.y, 0.0f});
    model = glm::scale(model, glm::vec3{scale, 1.0f});

    return model;
}

Sprite* Sprite::getComponent(Object* parent) {
    return parent->getComponent<Sprite>("Sprite");
}

} // namespace ngind::components