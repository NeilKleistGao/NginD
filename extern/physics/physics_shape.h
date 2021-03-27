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

/// @file physics_shape.h

#ifndef NGIND_PHYSICS_SHAPE_H
#define NGIND_PHYSICS_SHAPE_H

#include "box2d/box2d.h"
#include "resources/config_resource.h"

namespace ngind::physics {

struct PhysicsShape {
    b2Shape* shape;
    PhysicsShape() : shape(nullptr) {}
    virtual ~PhysicsShape(){};
};

struct CircleShape : public PhysicsShape {
    float radius;
    explicit CircleShape(const typename resources::ConfigResource::JsonObject& data);
    ~CircleShape() override;
};

struct PolygonShape : public PhysicsShape {
    int length;
    b2Vec2* vertex;
    explicit PolygonShape(const typename resources::ConfigResource::JsonObject& data);
    ~PolygonShape() override;
};

} // namespace ngind::physics

#endif //NGIND_PHYSICS_SHAPE_H
