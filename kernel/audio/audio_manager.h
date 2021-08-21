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

/// @file audio_manager.h

#ifndef NGIND_AUDIO_MANAGER_H
#define NGIND_AUDIO_MANAGER_H

#include <map>

#include "soloud/soloud.h"
#include "resources/music_resource.h"
#include "resources/effect_resource.h"

namespace ngind::audio {
/**
 * Management for audio process.
 */
class AudioManager {
public:
    /**
     * Get the unique instance of audio manager.
     * @return AudioManager*, the unique instance
     */
    static AudioManager* getInstance();

    /**
     * Destroy the unique instance.
     */
    static void destroyInstance();

    /**
     * Start playing given music.
     * @param music: music that will be played.
     */
    void playMusic(resources::MusicResource* music);

    /**
     * Stop playing given music.
     * @param music: music that will be stopped.
     */
    void stopMusic(resources::MusicResource* music);

    /**
     * Stop all music.
     */
    inline void stopAll() {
        _engine.stopAll();
    }

    /**
     * Pause given music.
     * @param music: music that should be paused.
     */
    void pauseMusic(resources::MusicResource* music);

    /**
     * Resume music that was stopped before.
     * @param music: music that will be resumed to play.
     */
    void resumeMusic(resources::MusicResource* music);

    /**
     * Pause all music.
     */
    inline void pauseAll() {
        _engine.setPauseAll(true);
    }

    /**
     * Resume all music from stopping.
     */
    inline void resumeAll() {
        _engine.setPauseAll(false);
    }

    /**
     * Play given effect audio.
     * @param effect: given effect audio.
     */
    inline void playEffect(resources::EffectResource* effect) {
        _engine.play(**effect);
    }

private:
    /**
     * The unique instance.
     */
    static AudioManager* _instance;

    /**
     * SoLoud engine object.
     */
    SoLoud::Soloud _engine;

    AudioManager();
    ~AudioManager();

    /**
     * Music playing handlers.
     */
    std::map<std::string, SoLoud::handle> _handles;
};
} // namespace ngind::audio

#endif //NGIND_AUDIO_MANAGER_H
