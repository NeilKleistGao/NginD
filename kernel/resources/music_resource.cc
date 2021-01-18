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

/// @file music_resource.cc

#include "music_resource.h"

#include "audio/audio_manager.h"

namespace ngind::resources {
const std::string MusicResource::MUSIC_RESOURCE_PATH = "resources/music";

MusicResource::MusicResource() : _length(0.0), _is_looping(false) {
    _stream = new SoLoud::WavStream{};
}

MusicResource::~MusicResource() {
    if (_stream) {
        audio::AudioManager::getInstance()->stopMusic(this);
        delete _stream;
        _stream = nullptr;
    }
}

void MusicResource::load(const std::string& name) {
    auto err = _stream->load((MUSIC_RESOURCE_PATH + "/" + name).c_str());
    if (err) {
        // TODO:
    }

    _length = _stream->getLength();
    this->_path = name;
}
} // namespace ngind::resources
