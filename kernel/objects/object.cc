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

namespace ngind::objects {

Object::Object() : AutoCollectionObject(), _parent(nullptr) {
    this->_children.clear();
    this->_components.clear();
}

Object::~Object() {
    for (auto it : this->_children) {
        it.second->removeReference();

        if (it.second->getSustain() == 0) {
            delete it.second;
            it.second = nullptr;
        }
    }

    for (auto it : this->_components) {
        delete it.second;
        it.second = nullptr;
    }

    this->_children.clear();
    this->_components.clear();
}

void Object::serialize(std::ostream& stream) const {
}

void Object::deserialize(std::istream& stream) {
}

void Object::addChild(const std::string& name, Object* object) {
    auto it = this->_children.find(name);
    if (it == this->_children.end()) {
        this->_children[name] = object;
        object->addReference();
        object->setParent(this);
    }
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
        if (object->getSustain() == 0) {
            delete object;
            object = nullptr;
        }
    }
}

Object* Object::getChildByName(const std::string& name) {
    Object* object = nullptr;
    auto it = this->_children.find(name);
    if (it != this->_children.end()) {
        object = it->second;
    }

    return object;
}

void Object::update(const float& delta) {
    for (auto child : this->_children) {
        child.second->update(delta);
    }

    for (auto component : this->_components) {
        component.second->update(delta);
    }
}

} // namespace ngind::objects