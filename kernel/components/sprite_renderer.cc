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

#include "sprite_renderer.h"

#include <vector>

#include "rendering/renderer.h"
#include "rendering/perspective.h"
#include "resources/resources_manager.h"
#include "exceptions/game_exception.h"

namespace ngind::components {

SpriteRenderer::SpriteRenderer()
        : _color("#FFFFFFFF"), _command(nullptr),
        _quad(nullptr), _program(nullptr),
        _texture(nullptr), _lb(), _rt() {
}

SpriteRenderer::~SpriteRenderer() {
    if (_texture != nullptr) {
        resources::ResourcesManager::getInstance()->release(_texture->getResourcePath());
        delete _texture;
        _texture = nullptr;
    }

    if (_program != nullptr) {
        resources::ResourcesManager::getInstance()->release(_program->getResourcePath());
        delete _program;
        _program = nullptr;
    }

    if (_quad != nullptr) {
        delete _quad;
        _quad = nullptr;
    }
}

void SpriteRenderer::update(const float& delta) {
    RenderComponent::update(delta);
    this->draw();
}

void SpriteRenderer::setImage(const std::string& filename) {
    if (_texture->getResourcePath() == filename) {
        return;
    }

    if (_texture != nullptr) {
        resources::ResourcesManager::getInstance()->release(_texture->getResourcePath());
    }
    _texture = resources::ResourcesManager::getInstance()->load<resources::TextureResource>(filename);
}

void SpriteRenderer::setImage(const std::string& filename, const Vector2D& lb, const Vector2D& rt) {
    this->setImage(filename);
    setBound(lb, rt);
}

void SpriteRenderer::draw() {
    if (_parent == nullptr) {
        throw exceptions::GameException("components::SpriteRenderer",
                                        "draw",
                                        "can't get parent object");
    }

    auto temp = static_cast<objects::EntityObject*>(_parent);
    auto pos = temp->getPosition();
    auto sz = _texture->getTextureSize();

    if (_command == nullptr) {
        _command = new rendering::QuadRenderCommand();
    }

    if (_quad == nullptr) {
        auto color_size = (_texture->getTextureColorMode() == rendering::TextureColorMode::MODE_RGB) ? 3 : 4;
        auto bound = rendering::Perspective::getInstance()->getPerspectiveSize() * 0.5f;
        auto texture_size = _texture->getTextureSize();

        _quad = new rendering::Quad({
                (pos.getX() + texture_size.getX() / 2 - bound.getX()) / bound.getX(), (pos.getY() + texture_size.getY() / 2 - bound.getY()) / bound.getY(), 0.0f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // Top Right
                (pos.getX() + texture_size.getX() / 2 - bound.getX()) / bound.getX(), (pos.getY() - texture_size.getY() / 2 - bound.getY()) / bound.getY(), 0.0f,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f, // Bottom Right
                (pos.getX() - texture_size.getX() / 2 - bound.getX()) / bound.getX(), (pos.getY() - texture_size.getY() / 2 - bound.getY()) / bound.getY(), 0.0f,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f, // Bottom Left
                (pos.getX() - texture_size.getX() / 2 - bound.getX()) / bound.getX(), (pos.getY() + texture_size.getY() / 2 - bound.getY()) / bound.getY(), 0.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f  // Top Left
        }, color_size);
    }

    _command->quad = _quad;
    _command->texture_id = _texture->getTextureID();
    _command->z_order = temp->getZOrder();
    _command->transparent = false;
    _command->program = _program->getProgram();

    rendering::Renderer::getInstance()->addRendererCommand(_command);
}

void SpriteRenderer::init(const typename resources::ConfigResource::JsonObject& data) {
    std::string name = data["filename"].GetString();
    if (!name.empty()) {
        _texture = resources::ResourcesManager::getInstance()->load<resources::TextureResource>(name);
    }
    if (_program == nullptr) {
        _program = resources::ResourcesManager::getInstance()->load<resources::ProgramResource>("sprite"); // default sprite shader
    }
}

SpriteRenderer* SpriteRenderer::create(const typename resources::ConfigResource::JsonObject& data) {
    auto* com = new SpriteRenderer();
    com->init(data);
    return com;
}

} // namespace ngind::components