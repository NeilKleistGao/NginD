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

#ifndef NGIND_ANIMATION_H
#define NGIND_ANIMATION_H

#include "component.h"
#include "script/lua_registration.h"
#include "resources/animation_resource.h"
#include "sprite.h"
#include "component_factory.h"

namespace ngind::components {

/**
 * Animation component. Sprite sibling component is required.
 */
class Animation : public Component {
public:
    Animation();
    ~Animation() override;
    Animation(const Animation&) = delete;
    Animation& operator= (const Animation&) = delete;

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
     * Create a animation component instance.
     * @param data: the configuration data this component initialization process requires
     * @return Animation*, the instance of animation component
     */
    static Animation* create(const typename resources::ConfigResource::JsonObject& data);

    /**
     * Play a clip of animation by given name.
     * @param name: name of animation clip
     */
    void play(const std::string& name);

    /**
     * Stop playing current clip.
     */
    void stop();

    /**
     * Pause current animation playing.
     */
    inline void pause() {
        _playing = false;
    }

    /**
     * Resume from pausing state.
     */
    inline void resume() {
        _playing = true;
    }

private:
    /**
     * Should animation be played automatically when ready.
     */
    bool _auto_play;

    /**
     * Should play the animation in loop.
     */
    bool _loop;

    /**
     * Is animation playing now.
     */
    bool _playing;

    /**
     * Local timer for frames exchanging.
     */
    float _timer;

    /**
     * Frame that is being played.
     */
    animation::AsepriteFrame _frame;

    /**
     * Tag of current animation clip.
     */
    std::string _tag;

    /**
     * Animation resources.
     */
    resources::AnimationResource* _anim;

    /**
     * Sprite component reference.
     */
    Sprite* _sprite;
};

NGIND_LUA_BRIDGE_REGISTRATION(Animation) {
    luabridge::getGlobalNamespace(script::LuaState::getInstance()->getState())
        .beginNamespace("engine")
            .deriveClass<Animation, Component>("Animation")
                .addFunction("play", &Animation::play)
                .addFunction("stop", &Animation::stop)
                .addFunction("pause", &Animation::pause)
                .addFunction("resume", &Animation::resume)
            .endClass()
        .endNamespace();

    ComponentFactory::getInstance()->registerComponent<Animation>("Animation");
}

} // namespace ngind::components

#endif //NGIND_ANIMATION_H
