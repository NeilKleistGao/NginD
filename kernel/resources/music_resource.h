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
/**
 * Music resource.
 */
class MusicResource : public Resource {
public:
    /**
     * Path of music resources.
     */
    const static std::string MUSIC_RESOURCE_PATH;

    MusicResource();
    ~MusicResource() override;

    /**
     * @see kernel/resources/resource.h
     */
    void load(const std::string& name) override;

    /**
     * Set volume of sound effect.
     * @param vol: new volume value
     */
    inline void setVolume(const float& vol) {
        _stream->setVolume(vol);
    }

    /**
     * Get the volume value.
     * @return float, the volume
     */
    inline float getVolume() const {
        return _stream->mVolume;
    }

    /**
     * Get the length of music.
     * @return double, the length in seconds
     */
    inline double getLength() const {
        return _length;
    }

    /**
     * Get whether play music in loop.
     * @return bool, whether play music in loop
     */
    inline bool isLooping() const {
        return _is_looping;
    }

    /**
     * Set whether play music in loop.
     * @param loop: whether play music in loop
     */
    inline void setLooping(const bool& loop) {
        _is_looping = loop;
        _stream->setLooping(loop);
    }

    /**
     * Set where music starts again.
     * @param point: where music starts again
     */
    inline void setLoopPoint(const double& point) {
        _stream->setLoopPoint(point);
    }

    /**
     * Get where music starts again.
     * @return where music starts again
     */
    inline double getLoopPoint() const {
        return _stream->getLoopPoint();
    }

    /**
     * Get SoLoud Wav Stream object.
     * @return SoLoud::WavStream*, SoLoud Wav Stream object
     */
    inline SoLoud::WavStream* operator-> () {
        return _stream;
    }

    /**
     * Get SoLoud Wav Stream reference.
     * @return SoLoud::WavStream&, SoLoud Wav Stream reference
     */
    inline SoLoud::WavStream& operator* () {
        return *_stream;
    }
private:
    /**
     * SoLoud wave stream object.
     */
    SoLoud::WavStream* _stream;

    /**
     * Length of music.
     */
    double _length;

    /**
     * Is this music playing in loop.
     */
    bool _is_looping;
};

} // namespace ngind::resources

#endif //NGIND_MUSIC_RESOURCE_H
