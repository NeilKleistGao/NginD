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

/// @file label.h

#ifndef NGIND_LABEL_H
#define NGIND_LABEL_H

#include <string>
#include <vector>
#include <tuple>

#include "renderer_component.h"
#include "rendering/rgba.h"
#include "resources/font_resource.h"
#include "rendering/quad.h"
#include "rendering/batch_quad_rendering_command.h"

#include "component_factory.h"
#include "script/lua_registration.h"

namespace ngind::log {
class VisualLogger;
}

namespace ngind::components {

/**
 * Label used to show text on the screen.
 */
class Label : public RendererComponent {
public:
    Label();
    ~Label();

    /**
     * Alignment method the label uses.
     * It works only if there are more than one lines text.
     */
    enum Alignment {
        ALIGNMENT_LEFT = 0,
        ALIGNMENT_RIGHT = 1,
        ALIGNMENT_CENTER = 2
    };

    Label(const Label&) = delete;
    Label& operator= (const Label&) = delete;

    /**
     * @see kernel/objects/updatable_object.h
     */
    void update(const float& delta) override;

    /**
     * @see kernel/components/component.h
     */
    void init(const typename resources::ConfigResource::JsonObject& data) override;

    /**
     * Create a label.
     * @param data: the configuration data this component initialization process requires.
     * @return Label*, a new label
     */
    static Label* create(const typename resources::ConfigResource::JsonObject& data);

    /**
     * Get label component from an object.
     * @param parent: the parent object
     * @return Label*, the label component
     */
    static Label* getComponent(Object* parent);

    /**
     * Set new text of label.
     * @param text: new text
     */
    inline void setText(const std::string& text) {
        _text = text;
        parseText();
    }

    /**
     * Get the text this label holds
     * @return std::string, the text
     */
    inline std::string getText() {
        return _text;
    }

    friend class ngind::log::VisualLogger;
private:
    /**
     * Text of label
     */
    std::string _text;

    /**
     * Font resource the label uses
     */
    resources::FontResource* _font;

    /**
     * Text size
     */
    size_t _size;

    /**
     * Quads data of label
     */
    std::vector<rendering::Quad*> _quads;

    /**
     * Rendering commands of label
     */
    std::vector<rendering::BatchQuadRenderingCommand*> _commands;

    /**
     * Colors each segment uses
     */
    std::vector<std::tuple<rendering::RGBA, unsigned int, unsigned int>> _colors;

    /**
     * Additional space between two lines
     */
    size_t _line_space;

    /**
     * Alignment method
     */
    Alignment _alignment;

    /**
     * Parse the text to determine rendering commands
     */
    void parseText();

    /**
     * Replace all <color></color>
     */
    void replaceEscape();

    /**
     * Calculate the model matrix
     * @param max_width: the width of the whole label
     * @param width: the width of current line
     * @param max_height: the height of the whole label
     * @return glm::mat4, the model matrix
     */
    glm::mat4 getModelMatrix(const float& max_width, const float& width, const float& max_height);
protected:
    /**
     * @see components/render_component.h
     */
    void draw() override;
};

NGIND_LUA_BRIDGE_REGISTRATION(Label) {
    luabridge::getGlobalNamespace(script::LuaState::getInstance()->getState())
    .beginNamespace("engine")
        .deriveClass<Label, RendererComponent>("Label")
            .addStaticFunction("getComponent", &Label::getComponent)
            .addFunction("setText", &Label::setText)
            .addFunction("getText", &Label::getText)
        .endClass()
    .endNamespace();

    ComponentFactory::getInstance()->registerComponent<Label>("Label");
};
} // namespace ngind::components

#endif //NGIND_LABEL_H
