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
#include "rendering/color.h"
#include "resources/font_resource.h"
#include "rendering/quad.h"
#include "rendering/quad_rendering_command.h"

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
    ~Label() override;

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

    /**
     * Set Text alignment.
     * @param alignment: alignment index: 0 -> left, 1 -> right, 2 -> center.
     */
    inline void setAlignment(int alignment) {
        _alignment = static_cast<Alignment>(alignment);
        _dirty = true;
    }

    /**
     * Set new line space for text
     * @param line_space: line space value
     */
    inline void setLineSpace(size_t line_space) {
        _line_space = line_space;
        _dirty = true;
    }

    /**
     * Set size of text
     * @param size: size of text
     */
    inline void setTextSize(size_t size) {
        _size = size;
        _dirty = true;
    }

    /**
     * Get the alignment of text
     * @return int, index of alignment
     */
    inline int getAlignment() const {
        return static_cast<int>(_alignment);
    }

    /**
     * Get the line space of this text
     * @return size_t, line space
     */
    inline size_t getLineSpace() const {
        return _line_space;
    }

    /**
     * Get the size of text
     * @return size_t, size of text
     */
    inline size_t getTextSize() const {
        return _size;
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
     * Rendering commands of label
     */
    std::vector<rendering::QuadRenderingCommand*> _commands;

    /**
     * Colors each segment uses
     */
    std::vector<std::tuple<rendering::Color, unsigned int, unsigned int>> _colors;

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
     * Parse the UTF8 text to determine rendering commands
     */
    void parseUTF8Text(const std::wstring& text);

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
            .addFunction("setAlignment", &Label::setAlignment)
            .addFunction("getAlignment", &Label::getAlignment)
            .addFunction("setLineSpace", &Label::setLineSpace)
            .addFunction("getLineSpace", &Label::getLineSpace)
            .addFunction("setTextSize", &Label::setTextSize)
            .addFunction("getTextSize", &Label::getTextSize)
        .endClass()
    .endNamespace();

    ComponentFactory::getInstance()->registerComponent<Label>("Label");
};
} // namespace ngind::components

#endif //NGIND_LABEL_H
