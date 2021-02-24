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

/// @file label.cc

#include "label.h"

#include <regex>
#include <codecvt>

#include "resources/resources_manager.h"
#include "exceptions/game_exception.h"
#include "objects/entity_object.h"
#include "rendering/renderer.h"
#include "memory/memory_pool.h"

namespace ngind::components {

Label::Label() : RendererComponent(),
_font(nullptr), _size(12), _line_space{3}, _alignment{ALIGNMENT_LEFT} {

}

Label::~Label() {
    if (_font != nullptr) {
        resources::ResourcesManager::getInstance()->release(_font);
        _font = nullptr;
    }

    for (auto& cmd : _commands) {
        cmd->removeReference();
    }

    _commands.clear();
}

void Label::update(const float& delta) {
    RendererComponent::update(delta);
    this->draw();
}

void Label::init(const typename resources::ConfigResource::JsonObject& data) {
    _font = resources::ResourcesManager::getInstance()->load<resources::FontResource>(data["font"].GetString());
    _program = resources::ResourcesManager::getInstance()->load<resources::ProgramResource>("text");
    _size = data["size"].GetInt();
    _color = rendering::Color{data["color"].GetString()};
    _text = data["text"].GetString();
    _alignment = static_cast<Alignment>(data["alignment"].GetInt());
}

Label* Label::create(const typename resources::ConfigResource::JsonObject& data) {
    auto com = memory::MemoryPool::getInstance()->create<Label>();
    com->init(data);
    return com;
}

void Label::draw() {
    if (_parent == nullptr) {
        throw exceptions::GameException("components::SpriteRenderer",
                                        "draw",
                                        "can't get parent object");
    }
    if (_commands.empty() || _dirty) {
        parseText();
        _dirty = false;
    }

    for (auto & cmd : _commands) {
        rendering::Renderer::getInstance()->addRendererCommand(cmd);
    }
}

void Label::parseText() {
    if (_text.empty()) {
        return;
    }

    if (!_commands.empty()) {
        for (auto& c : _commands) {
            c->removeReference();
        }
        _commands.clear();

        for (auto& q : _quads) {
            q->removeReference();
        }
        _quads.clear();
    }

    this->replaceEscape();

    std::wstring w_text = L"";
    bool utf8 = false;
    for (const auto& c : _text) {
        if ((c & 0x80) != 0) {
            utf8 = true;
            std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
            w_text = conv.from_bytes(_text);
            break;
        }
    }

    if (utf8) {
        this->parseUTF8Text(w_text);
        return;
    }

    auto temp = dynamic_cast<objects::EntityObject*>(_parent);
    auto pos = temp->getGlobalPosition();

    float scale = static_cast<float>(_size) / rendering::TrueTypeFont::DEFAULT_FONT_SIZE;
    auto cl_it = _colors.begin();
    auto color = (cl_it == _colors.end()) ? _color : std::get<0>(*cl_it);
    auto left = (cl_it == _colors.end()) ? 0 : std::get<1>(*cl_it),
            right = (cl_it == _colors.end()) ? 0 : std::get<2>(*cl_it);

    float max_width = 0, max_height = 0, current_width = 0;
    std::vector<float> widths;

    for (int i = 0; i < _text.length(); i++) {
        auto c = _text[i];
        if (c == '\n') {
            max_width = std::max(max_width, current_width);
            widths.push_back(current_width);
            current_width = 0;
            continue;
        }

        auto ch = _font->getCharacter(c);
        current_width += (ch.advance.x >> 6) * scale;
    }

    max_width = std::max(max_width, current_width);
    widths.push_back(current_width);

    current_width = 0; max_height = 0;
    glm::mat4 model = getModelMatrix(max_width, widths[0], max_height);
    for (int i = 0, j = 0; i < _text.length(); i++) {
        if (_text[i] == '\n') {
            j++;
            current_width = 0;
            max_height += static_cast<float>(_font->getMaxHeight()) * scale * 2 + _line_space;
            model = getModelMatrix(max_width, widths[j], max_height);
        }

        if (_quads.empty() || (!_colors.empty() && (i == left || i == right)) || _text[i] == '\n') {
            auto quad = memory::MemoryPool::getInstance()->create<rendering::Quad>(24);
            quad->addReference();
            _quads.push_back(quad);

            auto command = memory::MemoryPool::getInstance()
                    ->create<rendering::BatchQuadRenderingCommand>(_quads.back(), 24);
            command->addReference();
            _commands.push_back(command);
            _commands.back()->setProgram(_program->getProgram());
            _commands.back()->setZ(temp->getZOrder());
            _commands.back()->setModel(model);

            if (!_colors.empty() && i >= left && i < right) {
                if (i == right && cl_it + 1 != _colors.end()) {
                    cl_it++;
                    color = std::get<0>(*cl_it);
                    left = std::get<1>(*cl_it), right = std::get<2>(*cl_it);
                }

                _commands.back()->setColor(color);
            }
            else {
                _commands.back()->setColor(_color);
            }
        }

        if (_text[i] == '\n') {
            continue;
        }

        auto& cmd = _commands.back();
        rendering::Character ch = _font->getCharacter(_text[i]);

        auto x = current_width + ch.bearing.x * scale;
        auto y = -max_height - (ch.size.y - ch.bearing.y) * scale;
        auto width = ch.size.x * scale;
        auto height = ch.size.y * scale;

        cmd->push({x, y + height, 0.0f, 0.0f,
                   x, y, 0.0f, 1.0f,
                   x + width, y, 1.0f, 1.0f,

                   x, y + height, 0.0f, 0.0f,
                   x + width, y, 1.0f, 1.0f,
                   x + width, y + height, 1.0f, 0.0f}, ch.texture);
        current_width += (ch.advance.x >> 6) * scale;
    }
}

void Label::replaceEscape() {
    _colors.clear();

    std::smatch res;
    std::regex reg{R"((\\)*\<color=(#[0123456789ABCDEF]{8})\>(.*)(\\)*\</color\>)"};
    while (std::regex_search(_text, res, reg)) {
        auto text = res.str(3);
        _colors.emplace_back(rendering::Color{res.str(2)}, res.position(), res.position() + text.length());
        _text = res.prefix().str() + text + res.suffix().str();
    }
}

glm::mat4 Label::getModelMatrix(const float& max_width, const float& width, const float& max_height) {
    auto temp = dynamic_cast<objects::EntityObject*>(_parent);
    auto pos = temp->getGlobalPosition();
    auto global_scale = temp->getGlobalScale();
    auto rotate = temp->getGlobalRotation();
    auto anchor = temp->getAnchor();

    float scale = static_cast<float>(_size) / rendering::TrueTypeFont::DEFAULT_FONT_SIZE;
    pos.y -= static_cast<float>(_font->getMaxHeight()) * scale;

    glm::mat4 model{1.0f};
    if (_alignment == ALIGNMENT_LEFT) {
        model = glm::translate(model, glm::vec3{pos.x - max_width * global_scale.x * anchor.x,
                                                pos.y - max_height * global_scale.y * anchor.y, 0.0f});
    }
    else if (_alignment == ALIGNMENT_RIGHT) {
        model = glm::translate(model, glm::vec3{pos.x - max_width * global_scale.x * anchor.x + max_width - width,
                                                pos.y - max_height * global_scale.y * anchor.y, 0.0f});
    }
    else {
        model = glm::translate(model, glm::vec3{pos.x - max_width * global_scale.x * anchor.x + (max_width - width) * 0.5f,
                                                pos.y - max_height * global_scale.y * anchor.y, 0.0f});
    }
    model = glm::translate(model, glm::vec3{max_width * global_scale.x * anchor.x,
                                            max_height * global_scale.y * anchor.y, 0.0f});
    model = glm::rotate(model, rotate, glm::vec3{0.0f, 0.0f, 1.0f});
    model = glm::translate(model, glm::vec3{-max_width * global_scale.x * anchor.x,
                                            max_height * global_scale.y * anchor.y, 0.0f});
    model = glm::scale(model, glm::vec3{global_scale, 1.0f});

    return model;
}

Label* Label::getComponent(Object* parent) {
    return parent->getComponent<Label>("Label");
}

void Label::parseUTF8Text(const std::wstring& text) {
    auto temp = dynamic_cast<objects::EntityObject*>(_parent);
    auto pos = temp->getGlobalPosition();

    float scale = static_cast<float>(_size) / rendering::TrueTypeFont::DEFAULT_FONT_SIZE;
    auto cl_it = _colors.begin();
    auto color = (cl_it == _colors.end()) ? _color : std::get<0>(*cl_it);
    auto left = (cl_it == _colors.end()) ? 0 : std::get<1>(*cl_it),
            right = (cl_it == _colors.end()) ? 0 : std::get<2>(*cl_it);

    float max_width = 0, max_height = 0, current_width = 0;
    std::vector<float> widths;

    for (int i = 0; i < text.length(); i++) {
        auto c = text[i];
        if (c == '\n') {
            max_width = std::max(max_width, current_width);
            widths.push_back(current_width);
            current_width = 0;
            continue;
        }

        auto ch = _font->getCharacter(c);
        current_width += (ch.advance.x >> 6) * scale;
    }

    max_width = std::max(max_width, current_width);
    widths.push_back(current_width);

    current_width = 0; max_height = 0;
    glm::mat4 model = getModelMatrix(max_width, widths[0], max_height);
    for (int i = 0, j = 0; i < text.length(); i++) {
        if (text[i] == L'\n') {
            j++;
            current_width = 0;
            max_height += static_cast<float>(_font->getMaxHeight()) * scale * 2 + _line_space;
            model = getModelMatrix(max_width, widths[j], max_height);
        }

        if (_quads.empty() || (!_colors.empty() && (i == left || i == right)) || text[i] == L'\n') {
            auto quad = memory::MemoryPool::getInstance()->create<rendering::Quad>(24);
            quad->addReference();
            _quads.push_back(quad);

            auto command = memory::MemoryPool::getInstance()
                    ->create<rendering::BatchQuadRenderingCommand>(_quads.back(), 24);
            command->addReference();
            _commands.push_back(command);
            _commands.back()->setProgram(_program->getProgram());
            _commands.back()->setZ(temp->getZOrder());
            _commands.back()->setModel(model);

            if (!_colors.empty() && i >= left && i < right) {
                if (i == right && cl_it + 1 != _colors.end()) {
                    cl_it++;
                    color = std::get<0>(*cl_it);
                    left = std::get<1>(*cl_it), right = std::get<2>(*cl_it);
                }

                _commands.back()->setColor(color);
            }
            else {
                _commands.back()->setColor(_color);
            }
        }

        if (text[i] == L'\n') {
            continue;
        }

        auto& cmd = _commands.back();
        rendering::Character ch = _font->getCharacter(text[i]);

        auto x = current_width + ch.bearing.x * scale;
        auto y = -max_height - (ch.size.y - ch.bearing.y) * scale;
        auto width = ch.size.x * scale;
        auto height = ch.size.y * scale;

        cmd->push({x, y + height, 0.0f, 0.0f,
                   x, y, 0.0f, 1.0f,
                   x + width, y, 1.0f, 1.0f,

                   x, y + height, 0.0f, 0.0f,
                   x + width, y, 1.0f, 1.0f,
                   x + width, y + height, 1.0f, 0.0f}, ch.texture);
        current_width += (ch.advance.x >> 6) * scale;
    }
}

} // namespace ngind::components
