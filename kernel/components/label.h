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
#include "resources/program_resource.h"
#include "rendering/quad.h"
#include "rendering/render_command.h"

#include "rttr/registration.h"

namespace ngind::log {
class VisualLogger;
}

namespace ngind::components {

class Label : public RendererComponent {
public:
    Label();
    ~Label();

    Label(const Label&) = delete;
    Label& operator= (const Label&) = delete;

    void update(const float& delta) override;

    void init(const typename resources::ConfigResource::JsonObject& data) override;

    static Label* create(const typename resources::ConfigResource::JsonObject& data);

    inline void setText(const std::string& text) {
        _text = text;
        parseText();
    }

    inline std::string getText() {
        return _text;
    }

    friend class ngind::log::VisualLogger;
private:
    std::string _text;
    rendering::RGBA _color;
    resources::FontResource* _font;
    resources::ProgramResource* _program;
    size_t _size;
    std::vector<rendering::QuadRenderCommand*> _commands;
    std::vector<std::tuple<rendering::RGBA, unsigned int, unsigned int>> _colors;
    size_t _line_space;

    void parseText();
    void replaceEscape();
protected:
    virtual void draw();
};

RTTR_REGISTRATION {
    rttr::registration::class_<Label>("Label")
            .method("create", &Label::create);
}
} // namespace ngind::components

#endif //NGIND_LABEL_H
