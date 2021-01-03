/** MIT License
Copyright (c) 2020 NeilKleistGao
    Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/// @file entity_object.h
/// @date 2020/10/31

/**
@brief This file includes the definition of entity object and lots of inline
function for position/scale operation.
*/

#ifndef NGIND_ENTITY_OBJECT_H
#define NGIND_ENTITY_OBJECT_H

#include "object.h"

#include "math/vector.h"

namespace ngind {

using Vector2D = math::Vector2D;

/**
@class
    This class is a special kind of object that you can specify its position,
rotation and scale. If it's no need for this properties, use normal object instead.
*/
class EntityObject : public Object {
public:
    /// @public
    EntityObject();

    /// @public
    ~EntityObject() = default;

    EntityObject(const EntityObject&) = delete;
    EntityObject& operator= (const EntityObject&) = delete;

    /// @see kernel/objects/object.h
    virtual void update(const float&);

    /// @public
    /// @fn Set position for this object
    /// @param const Vector2D& v: new position
    /// @return void
    inline void setPosition(const Vector2D& v) {
        _position = v;
    }

    /// @public
    /// @fn Set x component of position vector
    /// @param const float& f: x component
    /// @return void
    inline void setPositionX(const float& f) {
        _position.setX(f);
    }

    /// @public
    /// @fn Set y component of position vector
    /// @param const float& f: y component
    /// @return void
    inline void setPositionY(const float& f) {
        _position.setY(f);
    }

    /// @public
    /// @fn Get the position
    /// @param void
    /// @return Vector2D, the position
    inline Vector2D getPosition() const {
        return _position;
    }

    /// @public
    /// @fn Get x component of position vector
    /// @param void
    /// @return float, x component
    inline float getPositionX() const {
        return _position.getX();
    }

    /// @public
    /// @fn Get y component of position vector
    /// @param void
    /// @return float, y component
    inline float getPositionY() const {
        return _position.getY();
    }

    /// @public
    /// @fn Set scale property of this object
    /// @param const Vector2D& v: new scale
    /// @return void
    inline void setScale(const Vector2D& v) {
        _scale = v;
    }

    /// @public
    /// @fn Set x component of scale vector
    /// @param const float& f: x component
    /// @return void
    inline void setScaleX(const float& f) {
        _scale.setX(f);
    }

    /// @public
    /// @fn Set y component of scale vector
    /// @param const float& f: y component
    /// @return void
    inline void setScaleY(const float& f) {
        _scale.setY(f);
    }

    /// @public
    /// @fn Get the scale
    /// @param void
    /// @return Vector2D, the scale
    inline Vector2D getScale() const {
        return _scale;
    }

    /// @public
    /// @fn Get x component of scale vector
    /// @param void
    /// @return float, x component
    inline float getScaleX() const {
        return _scale.getX();
    }

    /// @public
    /// @fn Get y component of scale vector
    /// @param void
    /// @return float, y component
    inline float getScaleY() const {
        return _scale.getY();
    }

    /// @public
    /// @fn Set rotation for this object
    /// @param const float& f: new rotation angle
    /// @return void
    inline void setRotation(const float& f) {
        _rotation = f;
    }

    /// @public
    /// @fn Get rotation for this object
    /// @param void
    /// @return float, the angle of rotation
    inline float getRotation() const {
        return _rotation;
    }

    /// @public
    /// @fn Get the order in z dim
    /// @param void
    /// @return int, z order
    inline int getZOrder() const {
        return _z_order;
    }

    /// @public
    /// @fn Set the order in z dim
    /// @param const int& z: z order
    /// @return void
    inline void setZOrder(const int& z) {
        _z_order = z;
    }

    /// @see kernel/objects/object.h
    inline void addComponent(const std::string& name, components::Component* component) override {
        if (_components.find(name) == _components.end()) {
            _components[name] = component;
            component->setParent(this);
        }
    }

private:
    /// @private
    /// @property the position of this object
    Vector2D _position;

    /// @private
    /// @property the scale of this object
    Vector2D _scale;

    /// @private
    /// @property the rotation angle of this object
    float _rotation;

    /// @private
    /// @property the z order of this object
    int _z_order;
};


} // namespace ngind

#endif //NGIND_ENTITY_OBJECT_H
