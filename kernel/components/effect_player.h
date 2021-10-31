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

/// @file effect_player.h

#ifndef NGIND_EFFECT_PLAYER_H
#define NGIND_EFFECT_PLAYER_H

#include "component.h"
#include "component_factory.h"
#include "resources/effect_resource.h"
#include "script/lua_registration.h"
#include "audio/audio_manager.h"
#include "objects/object.h"

namespace ngind::components {
/**
 * Sound effect player component.
 */
class EffectPlayer : public Component {
public:
    EffectPlayer();
    ~EffectPlayer();
    EffectPlayer(const EffectPlayer&) = delete;
    EffectPlayer& operator= (const EffectPlayer&) = delete;
    EffectPlayer(EffectPlayer&&) = delete;

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
     * Create a sound effect component instance.
     * @param data: the configuration data this component initialization process requires
     * @return EffectPlayer*, the instance of sound effect component
     */
    static EffectPlayer* create(const typename resources::ConfigResource::JsonObject& data);

    /**
     * Play this sound effect.
     */
    inline void play() {
        audio::AudioManager::getInstance()->playEffect(_effect);
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

    static EffectPlayer* getComponent(objects::Object* parent) {
        return parent->getComponent<EffectPlayer>("EffectPlayer");
    }
private:
    /**
     * Sound effect resource.
     */
    resources::EffectResource* _effect;
};

NGIND_LUA_BRIDGE_REGISTRATION(EffectPlayer) {
    luabridge::getGlobalNamespace(script::LuaState::getInstance()->getState())
    .beginNamespace("engine")
        .deriveClass<EffectPlayer, Component>("EffectPlayer")
            .addFunction("play", &EffectPlayer::play)
            .addFunction("setVolume", &EffectPlayer::setVolume)
            .addFunction("getVolume", &EffectPlayer::getVolume)
            .addStaticFunction("getComponent", &EffectPlayer::getComponent)
        .endClass()
    .endNamespace();

    ComponentFactory::getInstance()->registerComponent<EffectPlayer>("EffectPlayer");
}

} // namespace ngind::components

#endif //NGIND_EFFECT_PLAYER_H
