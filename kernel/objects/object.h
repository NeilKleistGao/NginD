/** MIT License
Copyright (c) 2020 NeilKleistGao
    Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/// @file object.h
/// @date 2020/10/31

/**
@brief This file define the most basic object class. Don't let your class inherit
object unless you want to add some basic function. Add component to it instead.
*/

#ifndef NGIND_OBJECT_H
#define NGIND_OBJECT_H

#include <map>
#include <iostream>

#include "kernel/utils/serialization.h"
#include "memory/auto_collection_object.h"
#include "updatable_object.h"
#include "components/component.h"

namespace ngind {

/**
@class This class is base of all objects in the game world. It can be serialized, auto collected
and update itself in each frame.
*/
class Object : public Serializable, public AutoCollectionObject, public UpdatableObject {
public:
    /// @public
    Object();

    /// @public
    ~Object() override;

    /// @see kernel/utils/serialization.h
    void serialize(std::ostream&) const override;

    /// @see kernel/utils/serialization.h
    void deserialize(std::istream&) override;

    /// @public
    /// @fn Add a child object
    /// @param const std::string&: the name of child
    /// @param Object*: the pointer to child object
    /// @return void
    void addChild(const std::string&, Object*);

    /// @public
    /// @fn Remove a reference of a child. If child is not found, nothing
    /// will happen
    /// @param const std::string&: the name of child
    /// @return void
    void removeChild(const std::string&);

    /// @public
    /// @fn Get the child. If child doesn't exist, it returns a null pointer
    /// @param const std::string&: the name of child
    /// @return Object*, the pointer to child
    Object* getChildByName(const std::string&);

    /// @public
    /// @fn Set parent object of this one
    /// @param Object* object: the parent object
    /// @return void
    inline void setParent(Object* object) {
        this->_parent = object;
    }

    /// @public
    /// @fn Get parent object of this one
    /// @param void
    /// @return Object*, the pointer to parent
    inline Object* getParent() {
        return this->_parent;
    }

    /// @see kernel/objects/updatable_object.h
    virtual void update(const float&);

    /// @public
    /// @fn Add a component. If component exists, nothing will happen.
    /// @param const std::string& name: name of component
    /// @param Component* component: component pointer
    /// @return void
    virtual inline void addComponent(const std::string& name, Component* component) {
        if (_components.find(name) == _components.end()) {
            _components[name] = component;
            component->setParent(this);
        }
    }

    /// @public
    /// @fn Get the component by name. If the component doesn't exist, it will return a null pointer.
    /// @tparam Type: the actual type of component
    /// @param const std::string& name: the name of component
    /// @return Type*, the pointer of component
    template<typename Type, typename std::enable_if_t<std::is_base_of_v<Component, Type>> N = 0>
    Type* getComponent(const std::string& name) {
        if (_components.find(name) == _components.end()) {
            return nullptr;
        }

        return static_cast<Type>(_components[name]);
    }

    /// @public
    /// @fn Remove a component by name. If the component doesn't exist, nothing will happen.
    /// @tparam Type: the actual type of component
    /// @param const std::string& name: the name of component
    /// @return void
    template<typename Type, typename std::enable_if_t<std::is_base_of_v<Component, Type>> N = 0>
    void removeComponent(const std::string& name) {
        if (_components.find(name) == _components.end()) {
            return;
        }

        auto p = static_cast<Type>(_components[name]);
        delete p;
        p = _components[name] = nullptr;
        _components.erase(name);
    }

protected:
    /// @protected
    /// @property A RB-tree maintaining all children
    std::map<std::string, Object*> _children;

    /// @protected
    /// @property A RB-tree maintaining all components
    std::map<std::string, Component*> _components;

    /// @protected
    /// @property Parent object
    Object* _parent;
};
} // namespace ngind



#endif //NGIND_OBJECT_H
