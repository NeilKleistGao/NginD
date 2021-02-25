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

/// @file animation_resource.h

#ifndef NGIND_ANIMATION_RESOURCE_H
#define NGIND_ANIMATION_RESOURCE_H

#include "resource.h"
#include "animation/aseprite.h"

namespace ngind::resources {

class AnimationResource : public Resource {
public:
    AnimationResource() : Resource() {
    }
    ~AnimationResource() override = default;

    virtual void load(const std::string&);

    inline animation::Aseprite* getAseprite() {
        return _ase;
    }
private:
    animation::Aseprite* _ase;
};

} // namespace ngind::resources

#endif //NGIND_ANIMATION_RESOURCE_H
