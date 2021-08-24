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

class Adaptor {
public:
    enum class ResolutionAdaptionTactic {
        EXACT_FIT,
        SHOW_ALL,
        NO_BORDER,
        FIXED_WIDTH,
        FIXED_HEIGHT
    };

    static Adaptor* getInstance();
    static void destroyInstance();

    inline void setResolutionAdaptionTactic(ResolutionAdaptionTactic tactic) {
        _tactic = tactic;
        update();
    }

    inline void setResolution(const glm::vec2& resolution) {
        _resolution = resolution;
        update();
    }

    inline void setWindowSize(const glm::vec2& size) {
        _screen = size;
        update();

    }

    inline void init(const glm::vec2& size, const glm::vec2& resolution,
                     ResolutionAdaptionTactic tactic = ResolutionAdaptionTactic::EXACT_FIT) {
        _tactic = tactic; _resolution = resolution; _screen = size;
        update();
    }
private:
    static Adaptor* _instance;

    ResolutionAdaptionTactic _tactic;
    glm::vec2 _resolution;
    glm::vec2 _screen;

    Adaptor() : _tactic(ResolutionAdaptionTactic::EXACT_FIT), _screen(), _resolution() {}
    ~Adaptor() = default;

    void update();
};

} // namespace ngind::rendering

#endif //NGIND_ADAPTOR_H
