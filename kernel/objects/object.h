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

/// @file object.h

#ifndef NGIND_OBJECT_H
#define NGIND_OBJECT_H

#include <map>
#include <iostream>

#include "memory/auto_collection_object.h"
#include "updatable_object.h"
#include "components/component.h"
#include "script/lua_registration.h"

namespace ngind::objects {

class EntityObject;

/**
 * This class is base of all objects in the game world. It can be serialized, auto collected
 * and update itself in each frame.
 */
class Object : public memory::AutoCollectionObject, public UpdatableObject {
public:
    Object();

    ~Object() override;

    /**
     * Add a child object
     * @param name: the name of child
     * @param object: the pointer to child object
     */
    virtual void addChild(const std::string& name, EntityObject* object);

    /**
     * Remove a reference of a child. If child is not found, nothing
     * @param name: the name of child
     */
    void removeChild(const std::string& name);

    /**
     * Remove all children by given name.
     * @param name: the given name
     */
    void removeAllChildren(const std::string& name);

    /**
     * Get the child. If child doesn't exist, it returns a null pointer
     * @param name: the name of child
     * @return Object*, the pointer to child
     */
    EntityObject* getChildByName(const std::string& name);

    /**
     * Get children by given name.
     * @param name: the given name
     * @return std::vector<EntityObject*>, the list of children
     */
    std::vector<EntityObject*> getChildrenByName(const std::string& name);

    /**
     * Get children by given name, and save it in the lua ref object.
     * @param ref: where the object would be saved
     * @param name: name of children
     */
    void getChildrenByName(luabridge::LuaRef ref, const std::string& name);

    /**
     * Get all children objects.
     * @return std::vector<EntityObject*>, all children
     */
    std::vector<EntityObject*> getChildren();

    /**
     * Set parent object of this one
     * @param object: the parent object
     */
    inline void setParent(Object* object) {
        this->_parent = object;
    }

    /**
     * Get parent object of this one
     * @return Object*, the pointer to parent
     */
    inline Object* getParent() {
        return this->_parent;
    }

    /**
     * @see kernel/objects/updatable_object.h
     */
    void update(const float&) override;

    /**
     * Add a component. If component exists, nothing will happen.
     * @param name: name of component
     * @param component: component pointer
     */
    virtual void addComponent(const std::string& name, components::Component* component);

    /**
     * Get the component by name. If the component doesn't exist, it will return a null pointer.
     * @tparam Type: the actual type of component
     * @param name: the name of component
     * @return Type*, the pointer of component
     */
    template<typename Type>
    Type* getComponent(const std::string& name) {
        if (_components.find(name) == _components.end()) {
            return nullptr;
        }

        return dynamic_cast<Type*>(_components[name]);
    }

    /**
     * Get all components by given type
     * @tparam Type: given component type
     * @param type: name of type
     * @return std::vector<Type*>, list of components
     */
    template<typename Type>
    std::vector<Type*> getComponents(const std::string& type) {
        std::vector<Type*> res;
        for (auto [name, com] : _components) {
            if (com->getComponentName() == type) {
                res.push_back(dynamic_cast<Type*>(com));
            }
        }

        return res;
    }

    /**
     * Remove a component by name. If the component doesn't exist, nothing will happen.
     * @tparam Type: the actual type of component
     * @param name: the name of component
     */
    template<typename Type, typename std::enable_if_t<std::is_base_of_v<components::Component, Type>> N = 0>
    void removeComponent(const std::string& name) {
        if (_components.find(name) == _components.end()) {
            return;
        }

        _components[name]->removeReference();
        _components.erase(name);
    }

protected:
    /**
     * A RB-tree maintaining all children
     */
    std::multimap<std::string, EntityObject*> _children;

    /**
     * A RB-tree maintaining all components
     */
    std::map<std::string, components::Component*> _components;

    /**
     * Parent object
     */
    Object* _parent;
};

NGIND_LUA_BRIDGE_REGISTRATION(Object) {
    luabridge::getGlobalNamespace(script::LuaState::getInstance()->getState())
    .beginNamespace("engine")
        .deriveClass<Object, memory::AutoCollectionObject>("Object")
            .addFunction("addChild", &Object::addChild)
            .addFunction("removeChild", &Object::removeChild)
            .addFunction("removeAllChildren", &Object::removeAllChildren)
            .addFunction("getChildByName", &Object::getChildByName)
            .addFunction<void>("getChildrenByName", &Object::getChildrenByName)
            .addFunction("addComponent", &Object::addComponent)
            .addFunction("setParent", &Object::setParent)
            .addFunction("getParent", &Object::getParent)
        .endClass()
    .endNamespace();
}

} // namespace ngind::objects

#endif //NGIND_OBJECT_H
