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

/// @file: render_component.h
/// @date: 2020/10/26

/**
@brief
    This file includes the basic render component class declaration. Include this
file if you need to create your own render component.
 */

#ifndef NGIND_RENDER_COMPONENT_H
#define NGIND_RENDER_COMPONENT_H

#include "component.h"

namespace ngind {

/**
@class
    Basic class of all render component. This class is a abstract class so you can't
create an instance unless you implement the draw function.
    If your component will not show anything on the screen, use simple Component class
instead.

@see kernel/components/component.h
*/
class RenderComponent : public Component {
public:
    /// @public
    RenderComponent() = default;
    /// @public
    virtual ~RenderComponent() = default;
    RenderComponent(const RenderComponent&) = delete;
    RenderComponent& operator= (const RenderComponent&) = delete;

    /// @public
    /// @fn Update the state of this component. This function is inherited from UpdatableObject
    /// @see kernel/objects/updatable_object.h
    virtual void update(const float&) {};

    /// @public
    /// @fn Initialization function of this class used by configuration creating method.
    /// @param const typename ConfigResource::JsonObject& : the configuration data
    /// this component initialization process requires.
    /// @return void
    virtual void init(const typename ConfigResource::JsonObject&) {};
protected:
    /// @protected
    /// @fn Create some render command and send them to the render queue in order to show
    /// something on the screen. This method should be called in update.
    /// @param void
    /// @return void
    virtual void draw() = 0;
};

} // namespace ngind

#endif //NGIND_RENDER_COMPONENT_H
