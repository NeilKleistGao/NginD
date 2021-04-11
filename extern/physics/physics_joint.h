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

/// @file physics_joint.h

#ifndef NGIND_PHYSICS_JOINT_H
#define NGIND_PHYSICS_JOINT_H

#include "box2d/box2d.h"
#include "kernel/components/component.h"
#include "rigid_body.h"
#include "script/lua_registration.h"

namespace ngind::physics {

class PhysicsJoint : public components::Component {
public:
    PhysicsJoint() : components::Component(), _def(nullptr), _joint(nullptr), _body_a(nullptr), _body_b(nullptr) {}
    virtual ~PhysicsJoint();

    void update(const float& delta) override {}

    void init(const typename resources::ConfigResource::JsonObject& data) override {}

    inline RigidBody* getBodyA() {
        return _body_a;
    }

    inline RigidBody* getBodyB() {
        return _body_b;
    }

    glm::vec2 getAnchorA() const;
    glm::vec2 getAnchorB() const;
private:
protected:
    b2JointDef* _def;
    b2Joint* _joint;

    RigidBody* _body_a;
    RigidBody* _body_b;
};

NGIND_LUA_BRIDGE_REGISTRATION(PhysicsJoint) {
    luabridge::getGlobalNamespace(script::LuaState::getInstance()->getState())
        .beginNamespace("engine")
            .deriveClass<PhysicsJoint, components::Component>("PhysicsJoint")
                .addFunction("getBodyA", &PhysicsJoint::getBodyA)
                .addFunction("getBodyB", &PhysicsJoint::getBodyB)
                .addFunction("getAnchorA", &PhysicsJoint::getAnchorA)
                .addFunction("getAnchorB", &PhysicsJoint::getAnchorB)
            .endClass()
        .endNamespace();
}

class DistanceJoint : public PhysicsJoint {
public:
    DistanceJoint();
    ~DistanceJoint() override;
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

    static DistanceJoint* create(const typename resources::ConfigResource::JsonObject& data);
private:
protected:
};

class RevoluteJoint : public PhysicsJoint {
public:
    RevoluteJoint();
    ~RevoluteJoint() override;
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

    static RevoluteJoint* create(const typename resources::ConfigResource::JsonObject& data);
private:
protected:
};

class PrismaticJoint : public PhysicsJoint {
public:
    PrismaticJoint();
    ~PrismaticJoint() override;
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

    static PrismaticJoint* create(const typename resources::ConfigResource::JsonObject& data);
private:
protected:
};

class PulleyJoint : public PhysicsJoint {
public:
    PulleyJoint();
    ~PulleyJoint() override;
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

    static PulleyJoint* create(const typename resources::ConfigResource::JsonObject& data);
private:
protected:
};

class GearJoint : public PhysicsJoint {
public:
    GearJoint();
    ~GearJoint() override;
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

    static GearJoint* create(const typename resources::ConfigResource::JsonObject& data);
private:
protected:
};

class WheelJoint : public PhysicsJoint {
public:
    WheelJoint();
    ~WheelJoint() override;
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

    static WheelJoint* create(const typename resources::ConfigResource::JsonObject& data);
private:
protected:
};

class RopeJoint : public PhysicsJoint {
public:
    RopeJoint();
    ~RopeJoint() override;
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

    static RopeJoint* create(const typename resources::ConfigResource::JsonObject& data);
private:
protected:
};

} // namespace ngind::physics

#endif //NGIND_PHYSICS_JOINT_H
