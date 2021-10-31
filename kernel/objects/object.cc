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
#include "log/logger_factory.h"

#ifdef ENABLE_PHYSICS
#include "extern/physics/physics_world.h"
#endif

namespace ngind::objects {

Object::Object() : AutoCollectionObject(), _parent(nullptr) {
    this->_children.clear();
    this->_components.clear();
}

Object::~Object() {
    for (auto [name, child] : this->_children) {
        child->removeReference();
    }

    for (auto [name, com] : this->_components) {
        com->removeReference();
#ifdef ENABLE_PHYSICS
        if (name == "PhysicsWorld") {
            auto world = dynamic_cast<physics::PhysicsWorld*>(com);
            if (world != nullptr) {
                world->clearRigidBody(this);
            }
        }
#endif
    }

    this->_children.clear();
    this->_components.clear();
}

void Object::addChild(const std::string& name, EntityObject* object) {
    this->_children.emplace(name, object);
    object->addReference();
    object->setParent(this);
}

void Object::removeChild(Object* child) {
    if (child != nullptr) {
        bool flag = false;
        for (auto it = _children.begin(); it != _children.end(); ++it) {
            if (it->second == child) {
                flag = true;
                it->second = nullptr;
                break;
            }
        }

        if (flag) {
            child->removeReference();
            child->setParent(nullptr);
        }
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
        if (child.second) {
            child.second->update(delta);
        }
    }

    for (auto it = this->_children.begin(); it != this->_children.end(); ++it) {
        if (!it->second) {
            it = _children.erase(it);
        }
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
        return;
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

void Object::addComponent(const std::string& name, components::Component* component) {
    if (_components.find(name) == _components.end()) {
        _components[name] = component;
        component->addReference();
        component->setParent(this);
    } else {
        auto logger = log::LoggerFactory::getInstance()->getLogger("warning.log", log::LogLevel::LOG_LEVEL_WARNING);
        logger->log("redundant component " + name + ".");
        logger->flush();
    }
}

} // namespace ngind::objects