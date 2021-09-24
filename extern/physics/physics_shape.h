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

/**
 * General physics collision shape. Use a specified class rather than this.
 */
struct PhysicsShape {
    /**
     * b2 shape object.
     */
    b2Shape* shape;
    PhysicsShape() : shape(nullptr) {}
    virtual ~PhysicsShape() = default;
};

/**
 * Physics collision with circle shape.
 */
struct CircleShape : public PhysicsShape {
    /**
     * Radius of circle.
     */
    float radius;

    /**
     * @param data: the configuration data this component initialization process requires
     */
    explicit CircleShape(const typename resources::ConfigResource::JsonObject& data);
    ~CircleShape() override;
};

/**
 * Physics collision with polygon shape.
 */
struct PolygonShape : public PhysicsShape {
    /**
     * Length of vertices array.
     */
    int length;

    /**
     * Vertices list.
     */
    b2Vec2* vertex;

    /**
     * @param data: the configuration data this component initialization process requires
     */
    explicit PolygonShape(const typename resources::ConfigResource::JsonObject& data);
    ~PolygonShape() override;
};

/**
 * Physics collision with edge shape.
 */
struct EdgeShape : public PhysicsShape {
    /**
     * Length of vertices array.
     */
    int length;

    /**
     * Vertices list.
     */
    b2Vec2* vertex;

    /**
     * @param data: the configuration data this component initialization process requires
     */
    explicit EdgeShape(const typename resources::ConfigResource::JsonObject& data);
    ~EdgeShape() override;
};

/**
 * Physics collision with chain shape.
 */
struct ChainShape : public PhysicsShape {
    /**
     * Length of vertices array.
     */
    int length;

    /**
     * Vertices list.
     */
    b2Vec2* vertex;
    /**
     * @param data: the configuration data this component initialization process requires
     */
    explicit ChainShape(const typename resources::ConfigResource::JsonObject& data);
    ~ChainShape() override;
};

} // namespace ngind::physics

#endif //NGIND_PHYSICS_SHAPE_H
