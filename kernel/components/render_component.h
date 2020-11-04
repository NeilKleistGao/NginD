// MIT License
//
// Copyright (c) 2020 NeilKleistGao
//
//        Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
//        to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//        copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
//        copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//        AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// FILENAME: render_component.h
// LAST MODIFY: 2020/10/26

// This file includes the basic render component class declaration. Include this
// file if you need to create your own render component.

#ifndef NGIND_RENDER_COMPONENT_H
#define NGIND_RENDER_COMPONENT_H

#include "component.h"

namespace ngind {

// Basic class of all render component. This class is a abstract class so you can't
// create an instance unless you implement the draw function.
// If your component will not show anything on the screen, use simple Component class
// instead.
class RenderComponent : public Component {
public:
    // Default constructor function
    RenderComponent() = default;
    // Default destructor function
    virtual ~RenderComponent() = default;

    // Copy behavior is not allowed. You can only maintain a pointer of a component
    RenderComponent(const RenderComponent&) = delete;
    // Copy behavior is not allowed. You can only maintain a pointer of a component
    RenderComponent& operator= (const RenderComponent&) = delete;

    // Update the state of this component. This function is inherited from UpdatableObject
    // @see objects/updatable_object.h
    virtual void update(const float&) {};

    // Initialization function of this class used by configuration creating method.
    // params:
    //      const typename ConfigResource::JsonObject& : the configuration data
    //      this component initialization process requires.
    // return: void
    virtual void init(const typename ConfigResource::JsonObject&) {};
protected:
    // Create some render command and send them to the render queue in order to show
    // something on the screen. This method should be called in update.
    // params: void
    // return: void
    virtual void draw() = 0;
};

} // namespace ngind

#endif //NGIND_RENDER_COMPONENT_H
