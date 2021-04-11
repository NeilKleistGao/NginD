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

/// @file physics_joint.cc

#include "physics_joint.h"

namespace ngind::physics {

PhysicsJoint::~PhysicsJoint() {
    if (_def != nullptr) {
        delete _def;
        _def = nullptr;
    }
}

glm::vec2 PhysicsJoint::getAnchorA() const {
    if (_joint == nullptr) {
        // TODO: warning
        return glm::vec2 {};
    }

    auto b2vec = _joint->GetAnchorA();
    return glm::vec2 {b2vec.x, b2vec.y};
}

glm::vec2 PhysicsJoint::getAnchorB() const {
    if (_joint == nullptr) {
        // TODO: warning
        return glm::vec2 {};
    }

    auto b2vec = _joint->GetAnchorB();
    return glm::vec2 {b2vec.x, b2vec.y};
}

} // namespace ngind::physics
