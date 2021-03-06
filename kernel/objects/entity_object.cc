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

/// @file entity_object.cc

#include "entity_object.h"

#include "game.h"

namespace ngind::objects {

EntityObject::EntityObject() : Object(), _position(), _scale(1, 1),
_rotation(0.0f), _z_order(0), _anchor(0.5f, 0.5f), _global_rotation(0.0f), _global_scale(), _global_position(), _id(-1) {

}

EntityObject::~EntityObject() {
    Game::getInstance()->getCurrentWorld()->unregisterEntity(_id);
}

void EntityObject::update(const float& delta) {
    Object::update(delta);
}

void EntityObject::adjustGlobalPosition() {
    auto p = dynamic_cast<EntityObject*>(_parent);
    if (p == nullptr) {
        _global_position = _position;
    }
    else {
        _global_position = p->_global_position + _position;
    }

    for (auto& [_, child] : _children) {
        child->_global_position = child->_position + _global_position;
        child->adjustGlobalPosition();
    }

    setDirtyComponents();
}

void EntityObject::adjustGlobalScale() {
    auto p = dynamic_cast<EntityObject*>(_parent);
    if (p == nullptr) {
        _global_scale = _scale;
    }
    else {
        _global_scale = p->_global_scale * _scale;
    }

    for (auto& [_, child] : _children) {
        child->_global_scale = child->_scale * _global_scale;
        child->adjustGlobalScale();
    }

    setDirtyComponents();
}

void EntityObject::adjustGlobalRotation() {
    auto p = dynamic_cast<EntityObject*>(_parent);
    if (p == nullptr) {
        _global_rotation = _rotation;
    }
    else {
        _global_rotation = p->_global_rotation + _rotation;
    }

    for (auto& [_, child] : _children) {
        child->_global_rotation = child->_rotation + _global_rotation;
        child->adjustGlobalRotation();
    }

    setDirtyComponents();
}

void EntityObject::setDirtyComponents() {
    for (auto& [_, com] : _components) {
        com->setDirty();
    }
}

void EntityObject::init(const typename resources::ConfigResource::JsonObject& data) {
    auto position = data["position"].GetObject();
    setPositionX(position["x"].GetFloat());
    setPositionY(position["y"].GetFloat());

    auto scale = data["scale"].GetObject();
    setScaleX(scale["x"].GetFloat());
    setScaleY(scale["y"].GetFloat());

    setRotation(data["rotate"].GetFloat());
    setZOrder(data["z-order"].GetInt());

    if (data.HasMember("id")) {
        _id = data["id"].GetInt();
    }
    else {
        _id = Game::getInstance()->getCurrentWorld()->getChildrenNumber() + 1;
    }
}

EntityObject* EntityObject::create(const typename resources::ConfigResource::JsonObject& data) {
    auto* entity = memory::MemoryPool::getInstance()->create<EntityObject>();
    if (entity == nullptr) {
        // TODO:
    }

    entity->init(data);
    Game::getInstance()->getCurrentWorld()->registerEntity(entity->_id, entity);
    return entity;
}

} // namespace ngind::objects