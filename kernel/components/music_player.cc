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

/// @file music_player.cc

#include "music_player.h"

#include "resources/resources_manager.h"
#include "memory/memory_pool.h"
#include "log/logger_factory.h"

namespace ngind::components {
MusicPlayer::MusicPlayer() : Component(), _music(nullptr), _auto(false) {
}

MusicPlayer::~MusicPlayer() {
    if (_music != nullptr) {
        resources::ResourcesManager::getInstance()->release(_music);
    }
}

void MusicPlayer::update(const float& delta) {
    Component::update(delta);

    if (_auto && _music != nullptr) {
        audio::AudioManager::getInstance()->playMusic(_music);
        _auto = false;
    }
}

void MusicPlayer::init(const typename resources::ConfigResource::JsonObject& data) {
    try {
        _component_name = data["type"].GetString();
        std::string name = data["filename"].GetString();
        if (!name.empty()) {
            _music = resources::ResourcesManager::getInstance()->load<resources::MusicResource>(name);
        }

        _auto = data["auto-play"].GetBool();
        this->setVolume(data["volume"].GetFloat());
        this->setLooping(data["looping"].GetBool());

        auto point = data["looping-point"].GetDouble();
        if (point >= 0.0) {
            this->setLoopPoint(point);
        }
    }
    catch (...) {
        auto logger = log::LoggerFactory::getInstance()->getLogger("crash.log", log::LogLevel::LOG_LEVEL_ERROR);
        logger->log("Can't create music player.");
        logger->flush();
    }
}

MusicPlayer* MusicPlayer::create(const typename resources::ConfigResource::JsonObject& data) {
    auto player = memory::MemoryPool::getInstance()->create<MusicPlayer>();
    player->init(data);
    return player;
}

void MusicPlayer::setVolume(const float& vol) {
    if (_music) {
        _music->setVolume(vol);
    }
}

float MusicPlayer::getVolume() const {
    if (_music) {
        return _music->getVolume();
    }

    return 0.0f;
}

void MusicPlayer::setLooping(const bool& loop) {
    if (_music != nullptr) {
        _music->setLooping(loop);
    }
}

bool MusicPlayer::isLooping() {
    if (_music != nullptr) {
        return _music->isLooping();
    }

    return false;
}

void MusicPlayer::setLoopPoint(const double& point) {
    if (_music) {
        _music->setLoopPoint(point);
    }
}

double MusicPlayer::getLoopPoint() {
    if (_music) {
        return _music->getLoopPoint();
    }

    return -1.0;
}

} // namespace ngind::components