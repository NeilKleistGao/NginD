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

    static Button* create(const typename resources::ConfigResource::JsonObject& data);

    void setAvailable(const bool& av);

    inline bool isAvailable() const {
        return _available;
    }

    inline void setPressed(const bool& pr) {
        _pressed = pr;
    }

    inline bool isPressed() const {
        return _pressed;
    }

    inline void setHighlighted(const bool& hl) {
        _highlighted = hl;
    }

    inline bool isHighlighted() const {
        return _highlighted;
    }
private:
    bool _available;
    bool _pressed;
    bool _highlighted;
    ui::ClickableReceiver _receiver;

    std::string _default_image;
    std::string _pressed_image;
    std::string _disable_image;
    std::string _highlight_image;

    Sprite* _sprite{};
};

NGIND_LUA_BRIDGE_REGISTRATION(Button) {
    ComponentFactory::getInstance()->registerComponent<Button>("Button");
}

} // namespace ngind::components

#endif //NGIND_BUTTON_H
