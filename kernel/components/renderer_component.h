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

/// @file: render_component.h

#ifndef NGIND_RENDERER_COMPONENT_H
#define NGIND_RENDERER_COMPONENT_H

#include "component.h"
#include "resources/program_resource.h"
#include "rendering/rgba.h"
#include "glm/glm.hpp"
#include "script/lua_registration.h"

namespace ngind::components {

/**
 * Basic class of all rendering component. This class is a abstract class so you can't
 * create an instance unless you implement the draw function.
 * If your component will not show anything on the screen, use simple Component class
 * instead.
 */
class RendererComponent : public Component {
public:
    RendererComponent() : _color("#FFFFFFFF"), _program(nullptr) {

    };
    virtual ~RendererComponent() {}
    RendererComponent(const RendererComponent&) = delete;
    RendererComponent& operator= (const RendererComponent&) = delete;

    /**
     * @see kernel/objects/updatable_object.h
     */
    virtual void update(const float&) {};

    /**
     * Initialization function of this class used by configuration creating method.
     * @param data: the configuration data this component initialization process requires.
     */
    virtual void init(const typename resources::ConfigResource::JsonObject& data) {};

    /**
     * Set the color mask of this sprite. The default color is pure white(#FFFFFFFF).
     * @param color: the color
     */
    inline void setColor(const rendering::RGBA& color) {
        _color = color;
    }

    /**
     * Get the color mask of this sprite. The default color is pure white(#FFFFFFFF).
     * @return RGBA, the color
     */
    inline rendering::RGBA getColor() const {
        return _color;
    }

    /**
     * Set alpha to this component
     * @param alpha: the new alpha value
     */
    inline void setAlpha(const int& alpha) {
        _color.a = alpha;
        _dirty = true;
    }

protected:
    /**
     * Create some rendering command and send them to the rendering queue in order to show
     * something on the screen. This method should be called in update.
     */
    virtual void draw() = 0;

    rendering::RGBA _color;
    resources::ProgramResource* _program;
};

NGIND_LUA_BRIDGE_REGISTRATION(RendererComponent) {
    luabridge::getGlobalNamespace(script::LuaState::getInstance()->getState())
        .beginNamespace("engine")
        .deriveClass<RendererComponent, Component>("RendererComponent")
            .addFunction("setColor", &RendererComponent::setColor)
            .addFunction("getColor", &RendererComponent::getColor)
        .endClass()
        .endNamespace();
};

} // namespace ngind::components

#endif //NGIND_RENDERER_COMPONENT_H
