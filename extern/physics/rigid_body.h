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

/// @file rigid_body.h

#ifndef NGIND_RIGID_BODY_H
#define NGIND_RIGID_BODY_H

#include "kernel/components/component.h"
#include "box2d/box2d.h"
#include "kernel/components/component_factory.h"
#include "kernel/script/lua_registration.h"
#include "kernel/objects/entity_object.h"
#include "physics_shape.h"
#include "objects/object.h"

namespace ngind::physics {
class PhysicsWorld;

class RigidBody : public components::Component {
public:
    RigidBody();
    ~RigidBody() override;

    /**
     * @see objects/updatable_object.h
     */
    void update(const float& delta) override;

    /**
     * Initialization function of this class used by configuration creating method. This function
     * is inherited from Component
     * @param data: the configuration data this component initialization process requires.
     */
    void init(const typename resources::ConfigResource::JsonObject& data) override;

    /**
     * Create a rigid body component instance.
     * @param data: the configuration data this component initialization process requires
     * @return PulleyJoint*, the instance of pulley joint component
     */
    static RigidBody* create(const typename resources::ConfigResource::JsonObject& data);

    /**
     * Get b2Body object.
     * @return b2Body*, b2Body object
     */
    inline b2Body* getBody() const {
        return _body;
    }

    /**
     * Apply force on this rigid body.
     * @param force: force on this rigid body.
     */
    void applyForce(const glm::vec2& force);

    /**
     * Apply torque on this rigid body.
     * @param torque: torque on this rigid body.
     */
    void applyTorque(float torque);

    /**
     * Set velocity of this rigid body directly.
     * @param velocity: velocity of this rigid body
     */
    void setVelocity(const glm::vec2& velocity);

    glm::vec2 getVelocity() const;

    /**
     * Set angular velocity of this rigid body directly.
     * @param velocity: angular velocity of this rigid body
     */
    void setAngularVelocity(float velocity);

    /**
     * Allow this rigid body to sleep or not.
     * @param allowed: true if this body can sleep
     */
    void setSleepingAllowed(bool allowed);

    /**
     * Can this rigid body sleep.
     * @return bool, true if this body can sleep
     */
    bool isSleepingAllowed() const;

    /**
     * Allow this rigid body to rotate or not.
     * @param fixed: true if this body can't rotate
     */
    void setRotationFixed(bool fixed);

    /**
     * Can this rigid body rotate.
     * @return bool, true if this body can't rotate
     */
    bool isRotationFixed() const;

    static RigidBody* getComponent(objects::Object* parent);

    friend class PhysicsWorld;
private:
    /**
     * Body definition.
     */
    b2BodyDef _def;

    /**
     * Fixture definition.
     */
    b2FixtureDef _fixture_def;

    /**
     * Fixture of body.
     */
    b2Fixture* _fixture;

    /**
     * Collision shape.
     */
    PhysicsShape* _shape;

    /**
     * B2 body object.
     */
    b2Body* _body;

    /**
     * Entity parent object.
     */
    objects::EntityObject* _ep;
};

NGIND_LUA_BRIDGE_REGISTRATION(RigidBody) {
    luabridge::getGlobalNamespace(script::LuaState::getInstance()->getState())
        .beginNamespace("engine")
            .deriveClass<RigidBody, components::Component>("RigidBody")
                .addFunction("applyForce", &RigidBody::applyForce)
                .addFunction("applyTorque", &RigidBody::applyTorque)
                .addFunction("setVelocity", &RigidBody::setVelocity)
                .addFunction("setAngularVelocity", &RigidBody::setAngularVelocity)
                .addFunction("setSleepingAllowed", &RigidBody::setSleepingAllowed)
                .addFunction("isSleepingAllowed", &RigidBody::isSleepingAllowed)
                .addFunction("setRotationFixed", &RigidBody::setRotationFixed)
                .addFunction("isRotationFixed", &RigidBody::isRotationFixed)
                .addFunction("getVelocity", &RigidBody::getVelocity)
                .addStaticFunction("getComponent", &RigidBody::getComponent)
            .endClass()
        .endNamespace();

        components::ComponentFactory::getInstance()->registerComponent<RigidBody>("RigidBody");
}

} // namespace ngind::physics

#endif //NGIND_RIGID_BODY_H
