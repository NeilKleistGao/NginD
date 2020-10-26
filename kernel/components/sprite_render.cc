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
// LAST MODIFY: 2020/10/26

#include "sprite_render.h"
#include "render/render_queue.h"
#include "resources/resources_manager.h"

namespace ngind {

SpriteRender::SpriteRender(const std::string& name) : SpriteRender(name, Vector2D::ORIGIN) {
}

SpriteRender::SpriteRender(const std::string& name, const Vector2D& pos) : _pos(pos) {
    _image = ResourcesManager::getInstance()->load<ImageResource>(name);
    auto img = _image->getPNGImage();
    setBound(Vector2D::ORIGIN, img->getImageSize());
}

SpriteRender::SpriteRender(const std::string& name, const Vector2D& lb, const Vector2D& rt) : SpriteRender(name) {
    setBound(lb, rt);
}

SpriteRender::SpriteRender(const std::string& name, const Vector2D& pos, const Vector2D& lb, const Vector2D& rt) : SpriteRender(name, pos) {
    setBound(lb, rt);
}

SpriteRender::~SpriteRender() {
    if (_image != nullptr) {
        ResourcesManager::getInstance()->release(_image->getResourcePath());
    }
}

void SpriteRender::update(const float& delta) {
    RenderComponent::update(delta);
    this->draw();
}

void SpriteRender::setImage(const std::string& filename) {
    if (_image->getResourcePath() == filename) {
        return;
    }

    ResourcesManager::getInstance()->release(_image->getResourcePath());
    _image = ResourcesManager::getInstance()->load<ImageResource>(filename);
    auto img = _image->getPNGImage();
    setBound(Vector2D::ORIGIN, img->getImageSize());
}

void SpriteRender::setImage(const std::string& filename, const Vector2D& lb, const Vector2D& rt) {
    this->setImage(filename);
    setBound(lb, rt);
}

void SpriteRender::draw() {
    // TODO: add command
}

} // namespace ngind