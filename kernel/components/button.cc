/** MIT License
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

/// @file button.cc

#include "button.h"

#include "ui/event_system.h"

namespace ngind::components {

Button::Button() : _pressed(false), _highlighted(false), _available(true), _sprite(nullptr) {
}

Button::~Button() {
    _receiver.vertex.clear();
}

void Button::update(const float& delta) {
    if (_sprite == nullptr) {
        _sprite = _parent->getComponent<Sprite>("Sprite");
        if (_sprite == nullptr) {
            return;
        }
    }

    if (_pressed) {
        _sprite->setImage(_pressed_image);
    }
    else if (_highlighted) {
        _sprite->setImage(_highlight_image);
    }
    else if (!_available) {
        _sprite->setImage(_disable_image);
    }
    else {
        _sprite->setImage(_default_image);
    }
}

void Button::init(const typename resources::ConfigResource::JsonObject& data) {
    _component_name = data["type"].GetString();
    _available = data["available"].GetBool();
    _default_image = data["default"].GetString();
    _pressed_image = data["pressed"].GetString();
    _disable_image = data["disable"].GetString();
    _highlight_image = data["highlight"].GetString();
    _receiver.z_order = data["z"].GetInt();

    auto vertex = data["vertex"].GetArray();
    for (const auto& v : vertex) {
        auto d = v.GetObject();
        _receiver.vertex.emplace_back(d["x"].GetInt(), d["y"].GetInt());
    }
    _receiver.button = this;

    if (_available) {
        ui::EventSystem::getInstance()->registerEvent(_receiver);
    }
}

Button* Button::create(const typename resources::ConfigResource::JsonObject& data) {
    auto* com = memory::MemoryPool::getInstance()->create<Button>();
    com->init(data);
    return com;
}

void Button::setAvailable(const bool& av) {
    _available = av;

    if (!av) {
        ui::EventSystem::getInstance()->unregisterEvent(_receiver);
    }
    else if (!_available && av) {
        ui::EventSystem::getInstance()->registerEvent(_receiver);
    }
}

} // namespace ngind::components