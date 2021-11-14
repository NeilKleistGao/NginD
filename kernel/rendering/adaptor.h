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

/// @file adaptor.h

#ifndef NGIND_ADAPTOR_H
#define NGIND_ADAPTOR_H

#include "glm/glm.hpp"

namespace ngind::rendering {

/**
 * Adaptation Tactics.
 */
enum class ResolutionAdaptionTactic {
    EXACT_FIT,
    SHOW_ALL,
    NO_BORDER,
    FIXED_WIDTH,
    FIXED_HEIGHT
};

/**
 * Screen Adaptor.
 */
class Adaptor {
public:
    /**
     * Get the unique instance of adaptor. If it does not exist, this function will create one.
     * @return Adaptor*, the unique instance
     */
    static Adaptor* getInstance();

    /**
     * Destroy the unique instance if it exists.
     */
    static void destroyInstance();

    /**
     * Set adaptation tactic.
     * @param tactic: the given tactic.
     */
    inline void setResolutionAdaptionTactic(ResolutionAdaptionTactic tactic) {
        _tactic = tactic;
        update();
    }

    /**
     * Set the resolution of screen.
     * @param resolution: the screen's resolution.
     */
    inline void setResolution(const glm::vec2& resolution) {
        _resolution = resolution;
        update();
    }

    /**
     * Set the size of window
     * @param size: the size of window
     */
    inline void setWindowSize(const glm::vec2& size) {
        _screen = size;
        update();

    }

    /**
     * Initialize adaptor.
     * @param size: window's size
     * @param resolution: screen's resolution
     * @param tactic: adaptation tactic
     */
    inline void init(const glm::vec2& size, const glm::vec2& resolution,
                     ResolutionAdaptionTactic tactic = ResolutionAdaptionTactic::EXACT_FIT) {
        _tactic = tactic; _resolution = resolution; _screen = size;
        update();
    }

    glm::vec2 screenToWorldSpace(const glm::vec2& pos);
private:
    /**
     * The unique instance.
     */
    static Adaptor* _instance;

    /**
     * Current adaptation tactic.
     */
    ResolutionAdaptionTactic _tactic;

    /**
     * Screen's resolution.
     */
    glm::vec2 _resolution;

    /**
     * Screen's size.
     */
    glm::vec2 _screen;

    Adaptor() : _tactic(ResolutionAdaptionTactic::EXACT_FIT), _screen(), _resolution() {}
    ~Adaptor() = default;

    /**
     * Update OpenGL context.
     */
    void update();
};

} // namespace ngind::rendering

#endif //NGIND_ADAPTOR_H
