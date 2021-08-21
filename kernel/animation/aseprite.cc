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

/// @file Aseprite.cc

#include "aseprite.h"

#include "resources/resources_manager.h"

namespace ngind::animation {

Aseprite::Aseprite(const std::string& name) : _current_index(), _current_tag(nullptr) {
    _config = resources::ResourcesManager::getInstance()->load<resources::ConfigResource>("animations/" + name + ".json");

    auto frames = (*_config)["frames"].GetArray();
    for (const auto& frame : frames) {
        _frames.emplace_back(frame);
    }

    auto meta = (*_config)["meta"].GetObject();
    _image_path = meta["image"].GetString();

    auto tags = meta["frameTags"].GetArray();
    for (const auto& tag : tags) {
        _tags.emplace_back(tag);
    }
}

Aseprite::~Aseprite() {
    _frames.clear();
    _tags.clear();

    resources::ResourcesManager::getInstance()->release(_config);
    _config = nullptr;
}

AsepriteFrame Aseprite::play(const std::string& name) {
    _current_tag = nullptr;
    for (auto& tag : _tags) {
        if (tag.getName() == name) {
            _current_tag = &tag;
            _current_index = tag.begin();
            break;
        }
    }

    if (_current_tag == nullptr) {
        _current_index = 0;
    }

    return _frames[_current_index];
}

AsepriteFrame Aseprite::next() {
    if (_current_tag == nullptr && _current_index < _frames.size()) {
        _current_index++;
    }
    else if (_current_index < _current_tag->end()) {
        _current_index++;
    }

    return _frames[_current_index];
}

bool Aseprite::isEnd() const {
    if (_current_tag == nullptr) {
        return _current_index + 1 == _frames.size();
    }
    else {
        return _current_index + 1 == _current_tag->end();
    }
}

} // namespace ngind::animation