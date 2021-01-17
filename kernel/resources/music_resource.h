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

/// @file music_resource.h

#ifndef NGIND_MUSIC_RESOURCE_H
#define NGIND_MUSIC_RESOURCE_H

#include "resource.h"
#include "soloud/soloud.h"
#include "soloud/soloud_wavstream.h"

namespace ngind::resources {

class MusicResource : public Resource {
public:
    const static std::string MUSIC_RESOURCE_PATH;

    MusicResource();
    ~MusicResource();
    void load(const std::string& name) override;

    inline void setVolume(const float& vol) {
        _stream->setVolume(vol);
    }

    inline float getVolume() const {
        return _stream->mVolume;
    }

    inline double getLength() const {
        return _length;
    }

    inline bool isLooping() const {
        return _is_looping;
    }

    inline void setLooping(const bool& loop) {
        _is_looping = loop;
        _stream->setLooping(loop);
    }

    inline void setLoopPoint(const double& point) {
        _stream->setLoopPoint(point);
    }

    inline double getLoopPoint() const {
        return _stream->getLoopPoint();
    }

    inline SoLoud::WavStream* getStream() {
        return _stream;
    }
private:
    SoLoud::WavStream* _stream;

    double _length;
    bool _is_looping;
};

} // namespace ngind::resources

#endif //NGIND_MUSIC_RESOURCE_H
