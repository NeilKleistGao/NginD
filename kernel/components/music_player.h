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

/// @file music_player.h

#ifndef NGIND_MUSIC_PLAYER_H
#define NGIND_MUSIC_PLAYER_H

#include "component.h"
#include "component_factory.h"
#include "resources/music_resource.h"
#include "script/lua_registration.h"
#include "audio/audio_manager.h"

namespace ngind::components {

class MusicPlayer : public Component {
public:
    MusicPlayer();
    ~MusicPlayer() override;
    MusicPlayer(const MusicPlayer&) = delete;
    MusicPlayer& operator= (const MusicPlayer&) = delete;

    /**
     * @see objects/updatable_object.h
     */
    void update(const float& delta) override;

    /**
     * Initialization function of this class used by configuration creating method. This function
     * is inherited from Component
     * @param data: the configuration data this component initialization process requires.
     */
    void init(const typename resources::ConfigResource::JsonObject& data) override;

    /**
     * Create a music component instance.
     * @param data: the configuration data this component initialization process requires
     * @return MusicPlayer*, the instance of music component
     */
    static MusicPlayer* create(const typename resources::ConfigResource::JsonObject& data);

    /**
     * Pause music playing.
     */
    inline void pause() {
        audio::AudioManager::getInstance()->pauseMusic(_music);
    }

    /**
     * Resume music from pausing.
     */
    inline void resume() {
        audio::AudioManager::getInstance()->resumeMusic(_music);
    }

    /**
     * Play this music.
     */
    inline void play() {
        audio::AudioManager::getInstance()->playMusic(_music);
    }

    /**
     * Stop playing.
     */
    inline void stop() {
        audio::AudioManager::getInstance()->stopMusic(_music);
    }

    /**
     * Set volume of sound effect.
     * @param vol: new volume value
     */
    void setVolume(const float& vol);

    /**
     * Get the volume value.
     * @return float, the volume
     */
    float getVolume() const;

    /**
     * Set whether play music in loop.
     * @param loop: whether play music in loop
     */
    void setLooping(const bool& loop);

    /**
     * Get whether play music in loop.
     * @return bool, whether play music in loop
     */
    bool isLooping();

    /**
     * Set where music starts again.
     * @param point: where music starts again
     */
    void setLoopPoint(const double& point);

    /**
     * Get where music starts again.
     * @return where music starts again
     */
    double getLoopPoint();

    void dump(typename resources::ConfigResource::JsonObject& data) const override;
private:
    /**
     * Whether music starts automatically.
     */
    bool _auto;

    /**
     * Music resource.
     */
    resources::MusicResource* _music;
};

NGIND_LUA_BRIDGE_REGISTRATION(MusicPlayer) {
    luabridge::getGlobalNamespace(script::LuaState::getInstance()->getState())
    .beginNamespace("engine")
        .deriveClass<MusicPlayer, Component>("MusicPlayer")
            .addFunction("pause", &MusicPlayer::pause)
            .addFunction("resume", &MusicPlayer::resume)
            .addFunction("play", &MusicPlayer::play)
            .addFunction("stop", &MusicPlayer::stop)
            .addFunction("setVolume", &MusicPlayer::setVolume)
            .addFunction("getVolume", &MusicPlayer::getVolume)
            .addFunction("setLooping", &MusicPlayer::setLooping)
            .addFunction("isLooping", &MusicPlayer::isLooping)
            .addFunction("setLoopPoint", &MusicPlayer::setLoopPoint)
            .addFunction("getLoopPoint", &MusicPlayer::getLoopPoint)
        .endClass()
    .endNamespace();

    ComponentFactory::getInstance()->registerComponent<MusicPlayer>("MusicPlayer");
}

} // namespace ngind::components

#endif //NGIND_MUSIC_PLAYER_H
