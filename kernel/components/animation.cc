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

/// @file animation.h

#include "animation.h"

#include "resources/resources_manager.h"

namespace ngind::components {

Animation::Animation() : _loop(), _playing(), _auto_play(), _anim(nullptr), _sprite(nullptr), _timer(0.0f) {
}

Animation::~Animation() {
    if (_anim != nullptr) {
        resources::ResourcesManager::getInstance()->release(_anim);
        _anim = nullptr;
    }
}

void Animation::update(const float& delta) {
    if (_sprite == nullptr) {
        _sprite = _parent->getComponent<Sprite>("Sprite");
        if (_sprite == nullptr) {
            return;
        }

        if (_auto_play) {
            this->play(_tag);
        }
    }

    if (!_playing) {
        return;
    }

    _timer += delta * 1000.0f;
    auto duration = _frame.getDuration().count();
    if (_timer >= duration) {
        _timer -= duration;
        auto ase = _anim->getAseprite();
        if (ase->isEnd()) {
            if (_loop) {
                this->play(_tag);
            }
            else {
                _playing = false;
                _timer = 0.0f;
            }
        }
        else {
            _frame = ase->next();
        }
        auto bound = _frame.getRect();
        _sprite->setBound({bound.x, bound.y}, {bound.z, bound.w});
    }
}

void Animation::init(const typename resources::ConfigResource::JsonObject& data) {
    std::string name = data["anim-name"].GetString();
    _anim = resources::ResourcesManager::getInstance()->load<resources::AnimationResource>(name);

    _loop = data["loop"].GetBool();
    _auto_play = data["auto-play"].GetBool();
    _tag = data["start"].GetString();
}

Animation* Animation::create(const typename resources::ConfigResource::JsonObject& data) {
    auto* com = memory::MemoryPool::getInstance()->create<Animation>();
    com->init(data);
    return com;
}

void Animation::play(const std::string& name) {
    auto ase = _anim->getAseprite();
    _tag = name;
    _frame = ase->play(name);
    _playing = true;
    _timer = 0.0f;

    auto bound = _frame.getRect();
    _sprite->setImage(ase->getFilename(), {bound.x, bound.y}, {bound.z, bound.w});
}

void Animation::stop() {
    _tag = "";
    _frame = animation::AsepriteFrame{};
    _playing = false;
    _timer = 0.0f;
}

} // namespace ngind::components