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

/// @file audio_manager.cc

#include "audio_manager.h"

#include "log/logger_factory.h"

namespace ngind::audio {
AudioManager* AudioManager::_instance = nullptr;

AudioManager::AudioManager() {
    _engine.init();
}

AudioManager::~AudioManager() {
    _engine.deinit();
}

AudioManager* AudioManager::getInstance() {
    if (_instance == nullptr) {
        _instance = new(std::nothrow) AudioManager();

        if (_instance == nullptr) {
            auto logger = log::LoggerFactory::getInstance()->getLogger("crash.log", log::LogLevel::LOG_LEVEL_ERROR);
            logger->log("Can't create audio manager instance.");
            logger->close();
        }
    }

    return _instance;
}

void AudioManager::destroyInstance() {
    if (_instance != nullptr) {
        delete _instance;
        _instance = nullptr;
    }
}

void AudioManager::playMusic(resources::MusicResource* music) {
    auto name = music->getResourcePath();
    if (_handles.find(name) != _handles.end()) {
        return;
    }

    _handles[name] = _engine.play(**music);
}

void AudioManager::stopMusic(resources::MusicResource* music) {
    auto name = music->getResourcePath();
    if (_handles.find(name) == _handles.end()) {
        return;
    }

    _engine.stop(_handles[name]);
    _handles.erase(name);
}

void AudioManager::pauseMusic(resources::MusicResource* music) {
    auto name = music->getResourcePath();
    if (_handles.find(name) == _handles.end()) {
        return;
    }

    _engine.setPause(_handles[name], true);
}

void AudioManager::resumeMusic(resources::MusicResource* music) {
    auto name = music->getResourcePath();
    if (_handles.find(name) == _handles.end()) {
        return;
    }

    _engine.setPause(_handles[name], false);
}

} // namespace ngind::audio