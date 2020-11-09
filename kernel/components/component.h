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

/// @file component.h
/// @date 2020/11/3

/**
@brief
    This file includes the basic component class. Include this file if you need to
create your own component classes.
    This file also includes a forward declaration. If you modified the object class,
you may need to clean and recompile this part.
*/

#ifndef NGIND_COMPONENT_H
#define NGIND_COMPONENT_H

#include <string>

#include "objects/updatable_object.h"
#include "resources/config_resource.h"

namespace ngind {

/// @note A forward declaration to prevent from circle including.
class Object;

/**
@class
    Basic class of all components. You can create an instance either by newing or
by create/init functions. We do not allow user to create a basic component in
configuration files so create function is not declared.
 */
class Component : public UpdatableObject {
public:
    /// @public
    Component() = default;
    /// @public
    virtual ~Component() = default;
    Component(const Component&) = delete;
    Component& operator= (const Component&) = delete;

    /// @public
    /// @fn Update the state of this component. This function is inherited from UpdatableObject
    /// @see kernel/objects/updatable_object.h
    virtual void update(const float&) {}

    /// @public
    /// @fn Initialization function of this class used by configuration creating method.
    /// @param const typename ConfigResource::JsonObject& : the configuration data
    /// this component initialization process requires.
    /// @return void
    virtual void init(const typename ConfigResource::JsonObject&) {}

    /// @public
    /// @fn Get the parent object of this component.
    /// @param void
    /// @return Object*, the parent object's pointer
    inline Object* getParent() const {
        return _parent;
    }

    /// @public
    /// @fn Set the parent object of this component.
    /// @param Object* parent : the parent object's pointer
    /// @return void
    inline void setParent(Object* parent) {
        _parent = parent;
    }

protected:
    /// @protected
    /// @property Parent object of this component
    Object* _parent;
};

} // namespace ngind

#endif //NGIND_COMPONENT_H
