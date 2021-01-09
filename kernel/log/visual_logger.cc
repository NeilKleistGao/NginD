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

/// @file visual_logger.cc

#include "visual_logger.h"

namespace ngind::log {
VisualLogger* VisualLogger::_instance = nullptr;

VisualLogger::VisualLogger() : _enable(false), _entity{nullptr}, _label{nullptr}, _text("") {
}

VisualLogger::~VisualLogger() {
    if (_entity != nullptr) {
        _entity->removeReference();
    }

    _entity = nullptr;
    _label = nullptr;

    _var.clear();
}

VisualLogger* VisualLogger::getInstance() {
    if (_instance == nullptr) {
        _instance = new(std::nothrow) VisualLogger();
    }

    return _instance;
}

void VisualLogger::destroyInstance() {
    if (_instance != nullptr) {
        delete _instance;
        _instance = nullptr;
    }
}

void VisualLogger::enable() {
    _enable = true;

    if (_entity == nullptr) {
        _entity = new objects::EntityObject();
        _entity->addReference();
        _entity->setZOrder(999);
        _entity->setAnchor({0, 0});
        _entity->setPosition({0, 768});

        _label = new components::Label();
        _label->_color = rendering::RGBA{"#FFFFFFAA"};
        _label->_text = "Visual Logger\n";
        _label->_font = resources::ResourcesManager::getInstance()->load<resources::FontResource>("manaspc.ttf");
        _label->_size = 18;
        _label->_line_space = 5;
        _label->_program = resources::ResourcesManager::getInstance()->load<resources::ProgramResource>("text");

        _entity->addComponent("Label", _label);
    }
}

void VisualLogger::draw() {
    if (_enable) {
        _text = "Visual Logger\n";
        for (const auto& [key, value] : _var) {
            _text += key + ": " + value + "\n";
        }

        _label->setText(_text);
        _entity->update(0);
    }
}

void VisualLogger::registerVariable(const std::string& key, const std::string default_value) {
    if (_var.find(key) == _var.end()) {
        _var[key] = default_value;
    }
    else {
        // TODO:
    }
}

void VisualLogger::resignVariable(const std::string& key) {
    if (_var.find(key) != _var.end()) {
        _var.erase(key);
    }
}

} // namespace ngind::log