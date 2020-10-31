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
// FILENAME: sprite_render.cc
// LAST MODIFY: 2020/10/31

#include "sprite_render.h"
#include "render/render.h"
#include "render/perspective.h"
#include "resources/resources_manager.h"

#include <vector>

namespace ngind {

SpriteRender::SpriteRender()
        : _color("#FFFFFFFF"), _command(nullptr),
        _quad(nullptr), _program(nullptr),
        _texture(0), _lb(), _rt() {
}

SpriteRender::~SpriteRender() {
    if (_texture != nullptr) {
        ResourcesManager::getInstance()->release(_texture->getResourcePath());
    }

    delete _program;
    _program = nullptr;
}

void SpriteRender::update(const float& delta) {
    RenderComponent::update(delta);
    this->draw();
}

void SpriteRender::setImage(const std::string& filename) {
    if (_texture->getResourcePath() == filename) {
        return;
    }

    if (_texture != nullptr) {
        ResourcesManager::getInstance()->release(_texture->getResourcePath());
    }
    _texture = ResourcesManager::getInstance()->load<TextureResource>(filename);
}

void SpriteRender::setImage(const std::string& filename, const Vector2D& lb, const Vector2D& rt) {
    this->setImage(filename);
    setBound(lb, rt);
}

void SpriteRender::draw() {
    if (_parent == nullptr) {
        // TODO: error detected
    }

    auto temp = static_cast<EntityObject*>(_parent);
    auto pos = temp->getPosition();
    auto hs = _texture->getTextureSize() * 0.5f;
    if (!Perspective::getInstance()->checkVisibility(
            Vector2D{pos.getX() - hs.getX(), pos.getY() + hs.getY() },
            Vector2D{pos.getX() - hs.getX(), pos.getY() - hs.getY()},
            Vector2D{pos.getX() + hs.getX(), pos.getY() + hs.getY()},
            Vector2D{pos.getX() + hs.getX(), pos.getY() - hs.getY()})) {
        return;
    }

    if (_command == nullptr) {
        _command = new QuadRenderCommand();
    }

    _command->quad = _quad;
    _command->texture_id = _texture->getTextureID();
    _command->z_order = temp->getZOrder();
    _command->transparent = false;
    _command->program = _program;
    _command->color = _color;
    _command->position = pos;
    _command->scale = temp->getScale();
    _command->rotate = temp->getRotation();
    _command->size = hs * 2;

    Render::getInstance()->addRenderCommand(_command);
}

void SpriteRender::init(const typename ConfigResource::JsonObject& data) {
    std::string name = data["filename"].GetString();
    if (!name.empty()) {
        _texture = ResourcesManager::getInstance()->load<TextureResource>(name);
    }

    _program = new Program("sprite");
    _quad = new Quad({
            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f
    });

    _lb = Vector2D::ORIGIN;
    _rt = _texture->getTextureSize();
}

SpriteRender* SpriteRender::create(const typename ConfigResource::JsonObject& data) {
    auto* com = new SpriteRender();
    com->init(data);
    return com;
}

} // namespace ngind