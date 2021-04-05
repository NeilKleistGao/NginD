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

/// @file object.cc

#include "object.h"
#include "entity_object.h"

namespace ngind::objects {

Object::Object() : AutoCollectionObject(), _parent(nullptr) {
    this->_children.clear();
    this->_components.clear();
}

Object::~Object() {
    for (auto it : this->_children) {
        it.second->removeReference();
    }

    for (auto it : this->_components) {
        it.second->removeReference();
    }

    this->_children.clear();
    this->_components.clear();
}

void Object::addChild(const std::string& name, EntityObject* object) {
    this->_children.emplace(name, object);
    object->addReference();
    object->setParent(this);
}

void Object::removeChild(const std::string& name) {
    auto it = this->_children.find(name);
    Object* object = nullptr;
    if (it != this->_children.end()) {
        object = it->second;
        this->_children.erase(it);
    }

    if (object != nullptr) {
        object->removeReference();
        object->setParent(nullptr);
    }
}

EntityObject* Object::getChildByName(const std::string& name) {
    EntityObject* object = nullptr;
    auto it = this->_children.find(name);
    if (it != this->_children.end()) {
        object = it->second;
    }

    return object;
}

void Object::update(const float& delta) {
    for (auto component : this->_components) {
        component.second->update(delta);
    }

    for (auto child : this->_children) {
        child.second->update(delta);
    }
}

void Object::removeAllChildren(const std::string& name) {
    for (auto it = this->_children.find(name); it != this->_children.end(); it = this->_children.find(name)) {
        Object* object =it->second;
        if (object != nullptr) {
            object->setParent(nullptr);
            object->removeReference();
        }
    }

    this->_children.erase(name);
}

std::vector<EntityObject*> Object::getChildrenByName(const std::string& name) {
    std::vector<EntityObject*> res;
    for (auto it = this->_children.find(name); it != this->_children.end(); it = this->_children.find(name)) {
        res.push_back(it->second);
    }

    return res;
}

void Object::getChildrenByName(luabridge::LuaRef ref, const std::string& name) {
    if (!ref.isTable()) {
        // TODO:
    }

    auto vec = this->getChildrenByName(name);
    for (int i = 0; i < vec.size(); i++) {
        ref[i] = vec[i];
    }
}

std::vector<EntityObject*> Object::getChildren() {
    std::vector<EntityObject*> children;
    for (auto [name, child] : _children) {
        children.push_back(child);
    }

    return children;
}

} // namespace ngind::objects