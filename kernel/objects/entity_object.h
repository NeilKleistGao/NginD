// MIT License
//
// Copyright (c) 2020 NeilKleistGao
//
//        Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
//        to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//        copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
//        copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//        AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// FILENAME: entity_object.h
// LAST MODIFY: 2020/10/31

#ifndef NGIND_ENTITY_OBJECT_H
#define NGIND_ENTITY_OBJECT_H

#include "object.h"

#include "math/vector.h"

namespace ngind {

class EntityObject : public Object {
public:
    EntityObject();
    ~EntityObject() = default;

    EntityObject(const EntityObject&) = delete;
    EntityObject& operator= (const EntityObject&) = delete;

    virtual void update(const float&);

    inline void setPosition(const Vector2D& v) {
        _position = v;
    }

    inline void setPositionX(const float& f) {
        _position.setX(f);
    }

    inline void setPositionY(const float& f) {
        _position.setY(f);
    }

    inline Vector2D getPosition() const {
        return _position;
    }

    inline float getPositionX() const {
        return _position.getX();
    }

    inline float getPositionY() const {
        return _position.getY();
    }

    inline void setScale(const Vector2D& v) {
        _scale = v;
    }

    inline void setScaleX(const float& f) {
        _scale.setX(f);
    }

    inline void setScaleY(const float& f) {
        _scale.setY(f);
    }

    inline Vector2D getScale() const {
        return _scale;
    }

    inline float getScaleX() const {
        return _scale.getX();
    }

    inline float getScaleY() const {
        return _scale.getY();
    }

    inline void setRotation(const float& f) {
        _rotation = f;
    }

    inline float getRotation() const {
        return _rotation;
    }

    inline int getZOrder() const {
        return _z_order;
    }

    inline void setZOrder(const int& z) {
        _z_order = z;
    }

    inline void addComponent(const std::string& name, Component* component) override {
        if (_components.find(name) == _components.end()) {
            _components[name] = component;
            component->setParent(this);
        }
    }

private:
    Vector2D _position, _scale;
    float _rotation;
    int _z_order;
};


} // namespace ngind

#endif //NGIND_ENTITY_OBJECT_H
