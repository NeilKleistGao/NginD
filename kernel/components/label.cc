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

#include "resources/resources_manager.h"
#include "exceptions/game_exception.h"
#include "objects/entity_object.h"
#include "rendering/renderer.h"

namespace ngind::components {

Label::Label() : _text(""), _color("#FFFFFFFF"),
_program(nullptr), _font(nullptr), _size(12) {

}

Label::~Label() {
    if (_program != nullptr) {
        resources::ResourcesManager::getInstance()->release(_program->getResourcePath());
        _program = nullptr;
    }
    if (_font != nullptr) {
        resources::ResourcesManager::getInstance()->release(_font->getResourcePath());
        _font = nullptr;
    }
}

void Label::update(const float& delta) {
    RenderComponent::update(delta);
    this->draw();
}

void Label::init(const typename resources::ConfigResource::JsonObject& data) {
    _font = resources::ResourcesManager::getInstance()->load<resources::FontResource>(data["font"].GetString());
    _program = resources::ResourcesManager::getInstance()->load<resources::ProgramResource>("text");
    _size = data["size"].GetInt();
    _color = rendering::RGBA{data["color"].GetString()};
    _text = data["text"].GetString();

    // TODO: test
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(1024), 0.0f, static_cast<GLfloat>(768));
    _program->getProgram()->use();
    _program->getProgram()->setMatrix4("projection", projection);
}

Label* Label::create(const typename resources::ConfigResource::JsonObject& data) {
    auto com = new Label();
    com->init(data);
    return com;
}

void Label::draw() {
    if (_parent == nullptr) {
        throw exceptions::GameException("components::SpriteRenderer",
                                        "draw",
                                        "can't get parent object");
    }

    auto temp = static_cast<objects::EntityObject*>(_parent);
    auto pos = temp->getPosition();

    if (_commands.empty()) {
        for (const auto& c : _text) {
            _commands.push_back(new rendering::QuadRenderCommand{});
        }
    }

    float scale = static_cast<float>(_size) / rendering::TrueTypeFont::DEFAULT_FONT_SIZE;

    for (int i = 0; i < _commands.size(); i++) {
        auto& cmd = _commands[i];
        auto ch = _font->getCharacter(_text[i]);
        auto x = pos.getX() + ch.bearing.x * scale;
        auto y = pos.getY() - (ch.size.y - ch.bearing.y) * scale;
        auto width = ch.size.x * scale;
        auto height = ch.size.y * scale;

        if (cmd->quad == nullptr) {
            cmd->quad = new rendering::Quad{{
                x, y + height, 0.0f, 0.0f,
                x, y, 0.0f, 1.0f,
                x + width, y, 1.0f, 1.0f,

                x, y + height, 0.0f, 0.0f,
                x + width, y, 1.0f, 1.0f,
                x + width, y + height, 1.0f, 0.0f,
                }, 4, true};
        }

        cmd->texture_id = ch.texture;
        cmd->z_order = temp->getZOrder();
        cmd->transparent = false;
        cmd->program = _program->getProgram();

        rendering::Renderer::getInstance()->addRendererCommand(cmd);
        pos.setX(pos.getX() + (ch.advance >> 6) * scale);
    }
}

} // namespace ngind::components
