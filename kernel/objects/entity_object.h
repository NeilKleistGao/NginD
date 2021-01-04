/**
 * @copybrief
 * MIT License
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

/// @file entity_object.h

#ifndef NGIND_ENTITY_OBJECT_H
#define NGIND_ENTITY_OBJECT_H

#include "object.h"
#include "math/vector.h"

namespace ngind::objects {

using Vector2D = math::Vector2D;

/**
 * This class is a special kind of object that you can specify its position,
 * rotation and scale. If it's no need for this properties, use normal object instead.
 */
class EntityObject : public Object {
public:
    EntityObject();

    ~EntityObject() = default;

    EntityObject(const EntityObject&) = delete;
    EntityObject& operator= (const EntityObject&) = delete;

    /// @see kernel/objects/object.h
    virtual void update(const float&);

    /**
     * Set position for this object
     * @param v: new position
     */
    inline void setPosition(const Vector2D& v) {
        _position = v;
    }

    /**
     * Set x component of position vector
     * @param f: x component
     */
    inline void setPositionX(const float& f) {
        _position.setX(f);
    }

    /**
     * Set y component of position vector
     * @param f: y component
     */
    inline void setPositionY(const float& f) {
        _position.setY(f);
    }

    /**
     * Get the position
     * @return Vector2D, the position
     */
    inline Vector2D getPosition() const {
        return _position;
    }

    /**
     * Get x component of position vector
     * @return float, x component
     */
    inline float getPositionX() const {
        return _position.getX();
    }

    /**
     * Get y component of position vector
     * @return float, y component
     */
    inline float getPositionY() const {
        return _position.getY();
    }

    /**
     * Set scale property of this object
     * @param v: new scale
     */
    inline void setScale(const Vector2D& v) {
        _scale = v;
    }

    /**
     * Set x component of scale vector
     * @param f: x component
     */
    inline void setScaleX(const float& f) {
        _scale.setX(f);
    }

    /**
     * Set y component of scale vector
     * @param f: y component
     */
    inline void setScaleY(const float& f) {
        _scale.setY(f);
    }

    /**
     * Get the scale
     * @return Vector2D, the scale
     */
    inline Vector2D getScale() const {
        return _scale;
    }

    /**
     * Get x component of scale vector
     * @return float, x component
     */
    inline float getScaleX() const {
        return _scale.getX();
    }

    /**
     * Get y component of scale vector
     * @return float, y component
     */
    inline float getScaleY() const {
        return _scale.getY();
    }

    /**
     * Set rotation for this object
     * @param f: new rotation angle
     */
    inline void setRotation(const float& f) {
        _rotation = f;
    }

    /**
     * Get rotation for this object
     * @return float, the angle of rotation
     */
    inline float getRotation() const {
        return _rotation;
    }

    /**
     * Get the order in z dim
     * @return int, z order
     */
    inline int getZOrder() const {
        return _z_order;
    }

    /**
     * Set the order in z dim
     * @param z: z order
     */
    inline void setZOrder(const int& z) {
        _z_order = z;
    }

    /**
     * @see kernel/objects/object.h
     */
    inline void addComponent(const std::string& name, components::Component* component) override {
        if (_components.find(name) == _components.end()) {
            _components[name] = component;
            component->setParent(this);
        }
    }

private:
    /**
     * The position of this object
     */
    Vector2D _position;

    /**
     * The scale of this object
     */
    Vector2D _scale;

    /**
     * The rotation angle of this object
     */
    float _rotation;

    /**
     * The z order of this object
     */
    int _z_order;
};


} // namespace ngind::objects

#endif //NGIND_ENTITY_OBJECT_H
