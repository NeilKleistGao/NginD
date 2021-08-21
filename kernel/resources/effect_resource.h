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

/// @file effect_resource.h

#ifndef NGIND_EFFECT_RESOURCE_H
#define NGIND_EFFECT_RESOURCE_H

#include "resource.h"
#include "soloud/soloud.h"
#include "soloud/soloud_sfxr.h"

namespace ngind::resources {
/**
 * Sound effect resource.
 */
class EffectResource : public Resource {
public:
    /**
     * Path of sound effect resources.
     */
    const static std::string EFFECT_RESOURCE_PATH;

    EffectResource();
    ~EffectResource() override;

    /**
     * @see kernel/resources/resource.h
     */
    void load(const std::string& name) override;

    /**
     * Set volume of sound effect.
     * @param vol: new volume value
     */
    inline void setVolume(const float& vol) {
        _effect->setVolume(vol);
    }

    /**
     * Get the volume value.
     * @return float, the volume
     */
    inline float getVolume() const {
        return _effect->mVolume;
    }

    inline SoLoud::Sfxr* operator-> () {
        return _effect;
    }

    inline SoLoud::Sfxr& operator* () {
        return *_effect;
    }
private:
    /**
     * SoLound Sfxr effect pointer.
     */
    SoLoud::Sfxr* _effect;
};

} // namespace ngind::resources

#endif //NGIND_EFFECT_RESOURCE_H
