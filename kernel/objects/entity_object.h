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
#include "glm/glm.hpp"

namespace ngind::objects {
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
    inline void setPosition(const glm::vec2& v) {
        _position = v;
    }

    /**
     * Set x component of position vector
     * @param f: x component
     */
    inline void setPositionX(const float& f) {
        _position.x = f;
    }

    /**
     * Set y component of position vector
     * @param f: y component
     */
    inline void setPositionY(const float& f) {
        _position.y = f;
    }

    /**
     * Get the position
     * @return Vector2D, the position
     */
    inline glm::vec2 getPosition() const {
        return _position;
    }

    /**
     * Get x component of position vector
     * @return float, x component
     */
    inline float getPositionX() const {
        return _position.x;
    }

    /**
     * Get y component of position vector
     * @return float, y component
     */
    inline float getPositionY() const {
        return _position.y;
    }

    /**
     * Set scale property of this object
     * @param v: new scale
     */
    inline void setScale(const glm::vec2& v) {
        _scale = v;
    }

    /**
     * Set x component of scale vector
     * @param f: x component
     */
    inline void setScaleX(const float& f) {
        _scale.x = f;
    }

    /**
     * Set y component of scale vector
     * @param f: y component
     */
    inline void setScaleY(const float& f) {
        _scale.y = f;
    }

    /**
     * Get the scale
     * @return Vector2D, the scale
     */
    inline glm::vec2 getScale() const {
        return _scale;
    }

    /**
     * Get x component of scale vector
     * @return float, x component
     */
    inline float getScaleX() const {
        return _scale.x;
    }

    /**
     * Get y component of scale vector
     * @return float, y component
     */
    inline float getScaleY() const {
        return _scale.y;
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

    inline void setAnchor(const glm::vec2& anchor) {
        _anchor = anchor;
    }

    inline void setAnchorX(const float& x) {
        _anchor.x = x;
    }

    inline void setAnchorY(const float& y) {
        _anchor.y = y;
    }

    inline glm::vec2 getAnchor() const {
        return _anchor;
    }

    inline float getAnchorX() const {
        return _anchor.x;
    }

    inline float getAnchorY() const {
        return _anchor.y;
    }
private:
    /**
     * The position of this object
     */
    glm::vec2 _position;

    /**
     * The scale of this object
     */
    glm::vec2 _scale;

    glm::vec2 _anchor;

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
