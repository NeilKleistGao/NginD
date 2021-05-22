/** MIT License
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

/// @file button.h

#ifndef NGIND_BUTTON_H
#define NGIND_BUTTON_H

#include "component.h"
#include "sprite.h"
#include "component_factory.h"
#include "ui/clickable_receiver.h"
#include "script/lua_registration.h"

namespace ngind::components {

/**
 * Clickable component. Sprite sibling component is required.
 */
class Button : public Component {
public:
    Button();
    ~Button() override;

    Button(const Button&) = delete;
    Button& operator= (const Button&) = delete;

    /**
     * @see objects/updatable_object.h
     */
    void update(const float& delta) override;

    /**
     * Initialization function of this class used by configuration creating method. This function
     * is inherited from Component
     * @param data: the configuration data this component initialization process requires.
     */
    void init(const typename resources::ConfigResource::JsonObject& data) override;

    /**
     * Create a button component instance.
     * @param data: the configuration data this component initialization process requires
     * @return Button*, the instance of animation component
     */
    static Button* create(const typename resources::ConfigResource::JsonObject& data);

    /**
     * Set if this button is clickable.
     * @param av: true if button is clickable
     */
    void setAvailable(const bool& av);

    /**
     * Get if this button is clickable.
     * @return bool, true if button is clickable
     */
    inline bool isAvailable() const {
        return _available;
    }

    /**
     * Set if this button is pressed.
     * @param pr: true if button is pressed
     */
    inline void setPressed(const bool& pr) {
        _pressed = pr;
    }

    /**
     * Get if this button is pressed.
     * @return bool, true if button is pressed
     */
    inline bool isPressed() const {
        return _pressed;
    }

    /**
     * Set if this button is highlighted.
     * @param hl: true if button is highlighted
     */
    inline void setHighlighted(const bool& hl) {
        _highlighted = hl;
    }

    /**
     * Get if this button is highlighted.
     * @return bool, true if button is highlighted
     */
    inline bool isHighlighted() const {
        return _highlighted;
    }

    void dump(typename resources::ConfigResource::JsonObject& data) const override;
private:
    /**
     * If this button is clickable.
     */
    bool _available;

    /**
     * If this button is pressed.
     */
    bool _pressed;

    /**
     * If this button is highlighted.
     */
    bool _highlighted;

    /**
     * Clickable area data.
     */
    ui::ClickableReceiver _receiver;

    std::vector<glm::vec2> _vertex;

    /**
     * Default background image path.
     */
    std::string _default_image;

    /**
     * Background image path(pressed state).
     */
    std::string _pressed_image;

    /**
     * Background image path(disabled state).
     */
    std::string _disable_image;

    /**
     * Background image path(highlight state).
     */
    std::string _highlight_image;

    /**
     * Reference to sprite component.
     */
    Sprite* _sprite{};

    objects::EntityObject* _entity_parent;

    /**
     * Model projection matrix
     */
    glm::mat4 _model;

    bool _register;

    /**
    * Calculate the model matrix
    * @return glm::mat4, the model matrix
    */
    glm::mat4 getModelMatrix();

    void setReceiver();
};

NGIND_LUA_BRIDGE_REGISTRATION(Button) {
    luabridge::getGlobalNamespace(script::LuaState::getInstance()->getState())
        .beginNamespace("engine")
            .deriveClass<Button, Component>("Animation")
                .addFunction("setAvailable", &Button::setAvailable)
                .addFunction("isAvailable", &Button::isAvailable)
            .endClass()
        .endNamespace();

    ComponentFactory::getInstance()->registerComponent<Button>("Button");
}

} // namespace ngind::components

#endif //NGIND_BUTTON_H
