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
#include "log/logger_factory.h"

namespace ngind::components {

Button::Button() : _pressed(false), _highlighted(false), _available(true),
    _sprite(nullptr), _model(1.0f), _entity_parent(nullptr), _register(false) {
}

Button::~Button() {
    _receiver.vertex.clear();
}

void Button::update(const float& delta) {
    if (_sprite == nullptr) {
        _sprite = _parent->getComponent<Sprite>("Sprite");
        _entity_parent = dynamic_cast<objects::EntityObject*>(_parent);
        if (_sprite == nullptr) {
            return;
        }
    }

    auto temp = getModelMatrix();
    if (temp != _model) {
        _model = temp;

        if (!_register && _available) {
            setReceiver();
            ui::EventSystem::getInstance()->registerEvent(_receiver);
        }
        else if (_register) {
            ui::EventSystem::getInstance()->unregisterEvent(_receiver);
            setReceiver();
            ui::EventSystem::getInstance()->registerEvent(_receiver);
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
    try {
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
            _vertex.emplace_back(d["x"].GetInt(), d["y"].GetInt());
        }
        _receiver.button = this;
    }
    catch (...) {
        auto logger = log::LoggerFactory::getInstance()->getLogger("crash.log", log::LogLevel::LOG_LEVEL_ERROR);
        logger->log("Can't create button component.");
        logger->flush();
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

glm::mat4 Button::getModelMatrix() {
    auto pos = _entity_parent->getPosition();
    auto rotate = _entity_parent->getRotation();

    glm::mat4 model{1.0f};
    model = glm::translate(model, glm::vec3{pos.x, pos.y, 0.0f});
    model = glm::rotate(model, rotate, glm::vec3{0.0f, 0.0f, 1.0f});

    return model;
}

void Button::setReceiver() {
    _receiver.vertex.clear();
    for (auto& v : _vertex) {
        auto v4 = glm::vec4 {v.x, v.y, 0, 1};
        v4 = _model * v4;
        _receiver.vertex.emplace_back(v4.x, v4.y);
    }
}

} // namespace ngind::components