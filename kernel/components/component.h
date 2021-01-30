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

/// @file: component.h

#ifndef NGIND_COMPONENT_H
#define NGIND_COMPONENT_H

#include <string>
#include <vector>

#include "objects/updatable_object.h"
#include "resources/config_resource.h"
#include "resources/resource.h"
#include "resources/resources_manager.h"
#include "script/lua_registration.h"
#include "memory/auto_collection_object.h"

namespace ngind {

namespace objects {
class Object;
} // namespace objects
namespace components {
using Object = objects::Object;
/**
 * Basic class of all components. You can create an instance either by newing or
 * by create/init functions. We do not allow user to create a basic component in
 * configuration files so create function is not declared.
 */
class Component :  public memory::AutoCollectionObject, public objects::UpdatableObject {
public:
    Component() : AutoCollectionObject(), _parent(nullptr), _dirty(false) {};
    virtual ~Component() = default;

    Component(const Component&) = delete;
    Component& operator= (const Component&) = delete;

    /**
     * @see kernel/objects/updatable_object.h
     */
    virtual void update(const float&) {}

    /**
     * Initialization function of this class used by configuration creating method.
     * @param object: the configuration data
     * this component initialization process requires.
     */
    virtual void init(const typename resources::ConfigResource::JsonObject& object) {}

    /**
     * Get the parent object of this component.
     * @return Object*, the parent object's pointer
     */
    inline Object* getParent() const {
        return _parent;
    }

    /**
     * Set the parent object of this component.
     * @param parent : the parent object's pointer
     * @return void
     */
    inline virtual void setParent(Object* parent) {
        _parent = parent;
    }

    /**
     * Make this component dirty, which means this component need
     * to recalculate some properties.
     */
    inline void setDirty() {
        _dirty = true;
    }

protected:
    /**
     * Parent object of this component
     */
    Object* _parent;

    /**
     * Is this component need to be updated
     */
    bool _dirty;
};

NGIND_LUA_BRIDGE_REGISTRATION(Component) {
    luabridge::getGlobalNamespace(script::LuaState::getInstance()->getState())
        .beginNamespace("engine")
            .beginClass<Component>("Component")
            .endClass()
        .endNamespace();
}

} // namespace components
} // namespace ngind

#endif //NGIND_COMPONENT_H
