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
#include "rendering/perspective.h"
#include "resources/resources_manager.h"
#include "exceptions/game_exception.h"

namespace ngind::components {

Sprite::Sprite()
        : RendererComponent(),
        _command(nullptr), _quad(nullptr),
        _texture(nullptr), _lb(), _rt() {
}

Sprite::~Sprite() {
    if (_texture != nullptr) {
        resources::ResourcesManager::getInstance()->release(_texture->getResourcePath());
    }

    if (_program != nullptr) {
        resources::ResourcesManager::getInstance()->release(_program->getResourcePath());
    }

    if (_quad != nullptr) {
        delete _quad;
        _quad = nullptr;
    }
}

void Sprite::update(const float& delta) {
    RendererComponent::update(delta);
    this->draw();
}

void Sprite::setImage(const std::string& filename) {
    if (_texture->getResourcePath() == filename) {
        return;
    }

    if (_texture != nullptr) {
        resources::ResourcesManager::getInstance()->release(_texture->getResourcePath());
    }
    _texture = resources::ResourcesManager::getInstance()->load<resources::TextureResource>(filename);
}

void Sprite::setImage(const std::string& filename, const glm::vec2& lb, const glm::vec2& rt) {
    this->setImage(filename);
    setBound(lb, rt);
}

void Sprite::draw() {
    if (_parent == nullptr) {
        throw exceptions::GameException("components::Sprite",
                                        "draw",
                                        "can't get parent object");
    }

    auto temp = static_cast<objects::EntityObject*>(_parent);
    auto texture_size = _texture->getTextureSize();

    if (_command == nullptr) {
        _command = new rendering::QuadRenderCommand();
    }

    if (_quad == nullptr) {
        _quad = new rendering::Quad({
                texture_size.x, texture_size.y, 1.0f, 0.0f, // Top Right
                texture_size.x, 0.0f, 1.0f, 1.0f, // Bottom Right
                0.0f, 0.0f, 0.0f, 1.0f, // Bottom Left
                0.0f, texture_size.y, 0.0f, 0.0f  // Top Left
        });
        _quad->setColor(_color);
        _quad->setModel(getModelMatrix());
    }

    _command->quad = _quad;
    _command->texture_id = _texture->getTextureID();
    _command->z_order = temp->getZOrder();
    _command->program = _program->getProgram();

    rendering::Renderer::getInstance()->addRendererCommand(_command);
}

void Sprite::init(const typename resources::ConfigResource::JsonObject& data) {
    std::string name = data["filename"].GetString();
    if (!name.empty()) {
        _texture = resources::ResourcesManager::getInstance()->load<resources::TextureResource>(name);
    }
    if (_program == nullptr) {
        _program = resources::ResourcesManager::getInstance()->load<resources::ProgramResource>("sprite"); // default sprite shader
    }
}

Sprite* Sprite::create(const typename resources::ConfigResource::JsonObject& data) {
    auto* com = new Sprite();
    com->init(data);
    return com;
}

glm::mat4 Sprite::getModelMatrix() {
    auto temp = static_cast<objects::EntityObject*>(_parent);
    auto pos = temp->getPosition();
    auto rotate = temp->getRotation();
    auto scale = temp->getScale();
    auto anchor = temp->getAnchor();
    auto texture_size = _texture->getTextureSize();

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

} // namespace ngind::components