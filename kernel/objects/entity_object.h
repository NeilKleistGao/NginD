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
#include "script/lua_registration.h"

namespace ngind::objects {
/**
 * This class is a special kind of object that you can specify its position, rotation and scale.
 */
class EntityObject : public Object {
public:
    EntityObject();

    ~EntityObject() override;

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
        adjustGlobalPosition();
    }

    /**
     * Set x component of position vector
     * @param f: x component
     */
    inline void setPositionX(const float& f) {
        _position.x = f;
        adjustGlobalPosition();
    }

    /**
     * Set y component of position vector
     * @param f: y component
     */
    inline void setPositionY(const float& f) {
        _position.y = f;
        adjustGlobalPosition();
    }

    /**
     * Get the position
     * @return glm::vec2, the position
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
     * Get the global position
     * @return glm::vec2, the position
     */
    inline glm::vec2 getGlobalPosition() const {
        return _global_position;
    }

    /**
     * Get x component of global position vector
     * @return float, x component
     */
    inline float getGlobalPositionX() const {
        return _global_position.x;
    }

    /**
     * Get y component of global position vector
     * @return float, y component
     */
    inline float getGlobalPositionY() const {
        return _global_position.y;
    }

    /**
     * Set scale property of this object
     * @param v: new scale
     */
    inline void setScale(const glm::vec2& v) {
        _scale = v;
        adjustGlobalScale();
    }

    /**
     * Set x component of scale vector
     * @param f: x component
     */
    inline void setScaleX(const float& f) {
        _scale.x = f;
        adjustGlobalScale();
    }

    /**
     * Set y component of scale vector
     * @param f: y component
     */
    inline void setScaleY(const float& f) {
        _scale.y = f;
        adjustGlobalScale();
    }

    /**
     * Get the scale
     * @return glm::vec2, the scale
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
     * Get the global scale
     * @return glm::vec2, the scale
     */
    inline glm::vec2 getGlobalScale() const {
        return _global_scale;
    }

    /**
     * Get x component of global scale vector
     * @return float, x component
     */
    inline float getGlobalScaleX() const {
        return _global_scale.x;
    }

    /**
     * Get y component of global scale vector
     * @return float, y component
     */
    inline float getGlobalScaleY() const {
        return _global_scale.y;
    }

    /**
     * Set rotation for this object
     * @param f: new rotation angle
     */
    inline void setRotation(const float& f) {
        _rotation = f;
        adjustGlobalRotation();
    }

    /**
     * Get rotation for this object
     * @return float, the angle of rotation
     */
    inline float getRotation() const {
        return _rotation;
    }

    /**
     * Get global rotation for this object
     * @return float, the angle of rotation
     */
    inline float getGlobalRotation() const {
        return _global_rotation;
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
        setDirtyComponents();
    }

    /**
     * Set the anchor of object. It will not change other properties.
     * The (0, 0) points left top vertex and (1, 1) points right bottom vertex.
     * @param anchor: new anchor point
     */
    inline void setAnchor(const glm::vec2& anchor) {
        _anchor = anchor;
    }

    /**
     * Set component x of the anchor of object.
     * @param x: component x
     */
    inline void setAnchorX(const float& x) {
        _anchor.x = x;
    }

    /**
     * Set component y of the anchor of object.
     * @param y: component y
     */
    inline void setAnchorY(const float& y) {
        _anchor.y = y;
    }

    /**
     * Get the anchor of object.
     * @return glm::vec2, the anchor of object
     */
    inline glm::vec2 getAnchor() const {
        return _anchor;
    }

    /**
     * Get component x of the anchor of object.
     * @return float, component x
     */
    inline float getAnchorX() const {
        return _anchor.x;
    }

    /**
     * Get component y of the anchor of object.
     * @return float, component y
     */
    inline float getAnchorY() const {
        return _anchor.y;
    }

    static EntityObject* create(const typename resources::ConfigResource::JsonObject& data);
private:
    /**
     * The position of this object
     */
    glm::vec2 _position;

    /**
     * The global position of this object
     */
    glm::vec2 _global_position;

    /**
     * The scale of this object
     */
    glm::vec2 _scale;

    /**
     * The global scale of this object
     */
    glm::vec2 _global_scale;

    /**
     * The anchor of this object
     */
    glm::vec2 _anchor;

    /**
     * The rotation angle of this object
     */
    float _rotation;

    /**
     * The global rotation angle of this object
     */
    float _global_rotation;

    /**
     * The z order of this object
     */
    int _z_order;

    int _id;

    /**
     * Adjust global position and push down the change when local position changed.
     */
    void adjustGlobalPosition();

    /**
     * Adjust global scale and push down the change when local scale changed.
     */
    void adjustGlobalScale();

    /**
     * Adjust global rotation and push down the change when local rotation changed.
     */
    void adjustGlobalRotation();

    /**
     * Set all components dirty so that components will redraw with new data.
     */
    void setDirtyComponents();

    void init(const typename resources::ConfigResource::JsonObject& data);
};

NGIND_LUA_BRIDGE_REGISTRATION(vec2) {
luabridge::getGlobalNamespace(script::LuaState::getInstance()->getState())
    .beginNamespace("engine")
        .beginClass<glm::vec2>("vec2")
            .addConstructor<void(*)(float, float)>()
            .addProperty("x", &glm::vec2::x)
            .addProperty("y", &glm::vec2::y)
        .endClass()
    .endNamespace();
}

NGIND_LUA_BRIDGE_REGISTRATION(EntityObject) {
luabridge::getGlobalNamespace(script::LuaState::getInstance()->getState())
        .beginNamespace("engine")
        .deriveClass<EntityObject, Object>("EntityObject")
            .addFunction("setPosition", &EntityObject::setPosition)
            .addFunction("setPositionX", &EntityObject::setPositionX)
            .addFunction("setPositionY", &EntityObject::setPositionY)
            .addFunction("getPosition", &EntityObject::getPosition)
            .addFunction("getPositionX", &EntityObject::getPositionX)
            .addFunction("getPositionY", &EntityObject::getPositionY)
            .addFunction("setScale", &EntityObject::setScale)
            .addFunction("setScaleX", &EntityObject::setScaleX)
            .addFunction("setScaleY", &EntityObject::setScaleY)
            .addFunction("getScale", &EntityObject::getScale)
            .addFunction("getScaleX", &EntityObject::getScaleX)
            .addFunction("getScaleY", &EntityObject::getScaleY)
            .addFunction("setRotation", &EntityObject::setRotation)
            .addFunction("getRotation", &EntityObject::getRotation)
            .addFunction("setZOrder", &EntityObject::setZOrder)
            .addFunction("getZOrder", &EntityObject::getZOrder)
        .endClass()
        .endNamespace();
}

} // namespace ngind::objects

#endif //NGIND_ENTITY_OBJECT_H
