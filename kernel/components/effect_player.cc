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

/// @file effect_player.cc

#include "effect_player.h"

namespace ngind::components {
EffectPlayer::EffectPlayer() : _effect(nullptr) {

}

EffectPlayer::~EffectPlayer() {
    if (_effect) {
        resources::ResourcesManager::getInstance()->release(_effect);
        _effect = nullptr;
    }
}

void EffectPlayer::update(const float& delta) {
    Component::update(delta);
}

void EffectPlayer::init(const typename resources::ConfigResource::JsonObject& data) {
    std::string name = data["filename"].GetString();
    if (!name.empty()) {
        _effect = resources::ResourcesManager::getInstance()->load<resources::EffectResource>(name);
    }
}

EffectPlayer* EffectPlayer::create(const typename resources::ConfigResource::JsonObject& data) {
    auto player = memory::MemoryPool::getInstance()->create<EffectPlayer>();
    player->init(data);
    return player;
}

void EffectPlayer::setVolume(const float& vol) {
    if (_effect) {
        _effect->setVolume(vol);
    }
}

float EffectPlayer::getVolume() const {
    if (_effect) {
        return _effect->getVolume();
    }

    return 0.0f;
}
} // namespace ngind::components
