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

/**
 * 2D general physics joint. You should use specified joint type rather than this.
 */
class PhysicsJoint : public components::Component {
public:
    PhysicsJoint()
        : components::Component(),
        _joint(nullptr), _body_a(nullptr), _body_b(nullptr),
        _index_a(0), _index_b(0), _collide(false)
        {}
    ~PhysicsJoint() override;

    /**
     * @see objects/updatable_object.h
     */
    void update(const float& delta) override {}

    /**
     * Initialization function of this class used by configuration creating method. This function
     * is inherited from Component
     * @param data: the configuration data this component initialization process requires.
     */
    void init(const typename resources::ConfigResource::JsonObject& data) override {}

    /**
     * Get the first body connected by this joint.
     * @return RigidBody* the first rigid body
     */
    inline RigidBody* getBodyA() {
        return _body_a;
    }

    /**
     * Get the second body connected by this joint.
     * @return RigidBody* the second rigid body
     */
    inline RigidBody* getBodyB() {
        return _body_b;
    }

    /**
     * Get connection anchor in first rigid body.
     * @return glm::vec2, connection anchor in first rigid body
     */
    glm::vec2 getAnchorA() const;

    /**
     * Get connection anchor in second rigid body.
     * @return glm::vec2, connection anchor in second rigid body
     */
    glm::vec2 getAnchorB() const;

    /**
     * Get b2joint object.
     * @return b2Joint*, b2joint object
     */
    inline b2Joint* getJoint() {
        return _joint;
    }
private:
protected:
    /**
     * B2joint object.
     */
    b2Joint* _joint;

    /**
     * Index of body a.
     */
    int _index_a;

    /**
     * Index of body b.
     */
    int _index_b;

    /**
     * Rigid body a.
     */
    RigidBody* _body_a;

    /**
     * Rigid body b.
     */
    RigidBody* _body_b;

    /**
     * Calculate collision or not.
     */
    bool _collide;

    /**
     * Initialize body information.
     */
    void setBodies();
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

/**
 * Distance joint.
 */
class DistanceJoint : public PhysicsJoint {
public:
    DistanceJoint() : PhysicsJoint() {}
    ~DistanceJoint() override = default;
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
     * Create a distance joint component instance.
     * @param data: the configuration data this component initialization process requires
     * @return DistanceJoint*, the instance of distance joint component
     */
    static DistanceJoint* create(const typename resources::ConfigResource::JsonObject& data);

    /**
     * Get current length of distance joint
     * @return float, current length
     */
    float getCurrentLength() const;

    static DistanceJoint* getComponent(objects::Object* parent) {
        return parent->getComponent<DistanceJoint>("DistanceJoint");
    }
private:
    /**
     * Joint definition data.
     */
    b2DistanceJointDef _def;

    /**
     * Anchor's position in first rigid body.
     */
    glm::vec2 _anchor_a{};

    /**
     * Anchor's position in second rigid body.
     */
    glm::vec2 _anchor_b{};

    /**
     * Initial length of joint.
     */
    float _length{};

    /**
     * Minimum length of joint.
     */
    float _min_length{};

    /**
     * Maximum length of joint.
     */
    float _max_length{};

    /**
     * Damping factor.
     */
    float _damping{};

    /**
     * Stiffness of the joints
     */
    float _stiffness{};
};

NGIND_LUA_BRIDGE_REGISTRATION(DistanceJoint) {
    components::ComponentFactory::getInstance()->registerComponent<DistanceJoint>("DistanceJoint");

    luabridge::getGlobalNamespace(script::LuaState::getInstance()->getState())
        .beginNamespace("engine")
            .deriveClass<DistanceJoint, PhysicsJoint>("DistanceJoint")
                .addFunction("getCurrentLength", &DistanceJoint::getCurrentLength)
                .addStaticFunction("getComponent", &DistanceJoint::getComponent)
            .endClass()
        .endNamespace();
}

/*
 * Revolute joint.
 */
class RevoluteJoint : public PhysicsJoint {
public:
    RevoluteJoint() : PhysicsJoint() {}
    ~RevoluteJoint() override = default;
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
     * Create a revolute joint component instance.
     * @param data: the configuration data this component initialization process requires
     * @return RevoluteJoint*, the instance of revolute joint component
     */
    static RevoluteJoint* create(const typename resources::ConfigResource::JsonObject& data);

    static RevoluteJoint* getComponent(objects::Object* parent) {
        return parent->getComponent<RevoluteJoint>("RevoluteJoint");
    }
private:
    /**
     * Joint definition data.
     */
    b2RevoluteJointDef _def;

    /**
     * The lower joint limit in radians.
     */
    float _lower_angle{};

    /**
     * The upper joint limit in radians.
     */
    float _upper_angle{};

    /**
     * 	Is the joint limit enabled.
     */
    bool _enable_limit{};

    /**
     * The maximum motor torque, usually in N-m.
     */
    float _max_motor{};

    /**
     * The motor speed in radians per second.
     */
    float _motor_speed{};

    /**
     * 	Enable the joint motor.
     */
    bool _enable_motor{};

    /**
     * Central position.
     */
    glm::vec2 _center{};
};

NGIND_LUA_BRIDGE_REGISTRATION(RevoluteJoint) {
    components::ComponentFactory::getInstance()->registerComponent<RevoluteJoint>("RevoluteJoint");
    luabridge::getGlobalNamespace(script::LuaState::getInstance()->getState())
        .beginNamespace("engine")
            .deriveClass<RevoluteJoint, PhysicsJoint>("RevoluteJoint")
                .addStaticFunction("getComponent", &RevoluteJoint::getComponent)
            .endClass()
        .endNamespace();
}

/**
 * Prismatic joint.
 */
class PrismaticJoint : public PhysicsJoint {
public:
    PrismaticJoint() : PhysicsJoint() {}
    ~PrismaticJoint() override = default;
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
     * Create a prismatic joint component instance.
     * @param data: the configuration data this component initialization process requires
     * @return PrismaticJoint*, the instance of prismatic joint component
     */
    static PrismaticJoint* create(const typename resources::ConfigResource::JsonObject& data);

    static PrismaticJoint* getComponent(objects::Object* parent) {
        return parent->getComponent<PrismaticJoint>("PrismaticJoint");
    }
private:
    /**
     * Joint definition data.
     */
    b2PrismaticJointDef _def;

    /**
     * Central position.
     */
    glm::vec2 _center{};

    /**
     * Joint axis.
     */
    glm::vec2 _axis{};

    /**
     * The lower translation limit, usually in meters.
     */
    float _lower_trans{};

    /**
     * The upper translation limit, usually in meters.
     */
    float _upper_trans{};

    /**
     * Enable the joint limit.
     */
    bool _enable_limit{};

    /**
     * The maximum motor torque, usually in N-m.
     */
    float _max_force{};

    /**
     * The desired motor speed in radians per second.
     */
    float _motor_speed{};

    /**
     * 	Enable the joint motor.
     */
    bool _enable_motor{};
};

NGIND_LUA_BRIDGE_REGISTRATION(PrismaticJoint) {
    components::ComponentFactory::getInstance()->registerComponent<PrismaticJoint>("PrismaticJoint");
    luabridge::getGlobalNamespace(script::LuaState::getInstance()->getState())
        .beginNamespace("engine")
            .deriveClass<PrismaticJoint, PhysicsJoint>("PrismaticJoint")
                .addStaticFunction("getComponent", &PrismaticJoint::getComponent)
            .endClass()
        .endNamespace();
}

/**
 * Pulley joint.
 */
class PulleyJoint : public PhysicsJoint {
public:
    PulleyJoint() : PhysicsJoint() {}
    ~PulleyJoint() override = default;
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
     * Create a pulley joint component instance.
     * @param data: the configuration data this component initialization process requires
     * @return PulleyJoint*, the instance of pulley joint component
     */
    static PulleyJoint* create(const typename resources::ConfigResource::JsonObject& data);

    /**
     * Get the current length of the segment attached to the first body.
     * @return float, current length of the segment
     */
    float getCurrentLengthA() const;

    /**
     * Get the current length of the segment attached to the second body.
     * @return float, current length of the segment
     */
    float getCurrentLengthB() const;

    static PulleyJoint* getComponent(objects::Object* parent) {
        return parent->getComponent<PulleyJoint>("PulleyJoint");
    }
private:
    /**
     * Joint definition data.
     */
    b2PulleyJointDef _def;

    /**
     * 	The pulley ratio, used to simulate a block-and-tackle.
     */
    float _ratio{};

    /**
     * 	The local anchor point relative to bodyA's origin.
     */
    glm::vec2 _anchor_a{};

    /**
     * 	The local anchor point relative to bodyB's origin.
     */
    glm::vec2 _anchor_b{};

    /**
     * The first ground anchor in world coordinates. This point never moves.
     */
    glm::vec2 _ground_a{};

    /**
     * The second ground anchor in world coordinates. This point never moves.
     */
    glm::vec2 _ground_b{};
};

NGIND_LUA_BRIDGE_REGISTRATION(PulleyJoint) {
    components::ComponentFactory::getInstance()->registerComponent<PulleyJoint>("PulleyJoint");
    luabridge::getGlobalNamespace(script::LuaState::getInstance()->getState())
        .beginNamespace("engine")
            .deriveClass<PulleyJoint, PhysicsJoint>("PulleyJoint")
                .addFunction("getCurrentLengthA", &PulleyJoint::getCurrentLengthA)
                .addFunction("getCurrentLengthB", &PulleyJoint::getCurrentLengthB)
                .addStaticFunction("getComponent", &PulleyJoint::getComponent)
            .endClass()
        .endNamespace();
}

/**
 * Gear joint.
 */
class GearJoint : public PhysicsJoint {
public:
    GearJoint() : PhysicsJoint() {}
    ~GearJoint() override = default;
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
     * Create a gear joint component instance.
     * @param data: the configuration data this component initialization process requires
     * @return GearJoint*, the instance of gear joint component
     */
    static GearJoint* create(const typename resources::ConfigResource::JsonObject& data);

    /**
     * Get the first joint.
     * @return PhysicsJoint*, the first joint.
     */
    PhysicsJoint* getJointA() const;

    /**
     * Get the second joint.
     * @return PhysicsJoint*, the second joint.
     */
    PhysicsJoint* getJointB() const;

    static GearJoint* getComponent(objects::Object* parent) {
        return parent->getComponent<GearJoint>("GearJoint");
    }
private:
    /**
     * Joint definition data.
     */
    b2GearJointDef _def;

    /**
     * Rigid body A's index.
     */
    int _joint_a{};

    /**
     * Rigid body B's index.
     */
    int _joint_b{};

    /**
     * Gear ratio.
     */
    float _ratio{};

    /**
     * Component A's name.
     */
    std::string _name_a;

    /**
     * Component B's name.
     */
    std::string _name_b;
};

NGIND_LUA_BRIDGE_REGISTRATION(GearJoint) {
    components::ComponentFactory::getInstance()->registerComponent<GearJoint>("GearJoint");
    luabridge::getGlobalNamespace(script::LuaState::getInstance()->getState())
        .beginNamespace("engine")
            .deriveClass<GearJoint, PhysicsJoint>("GearJoint")
                .addFunction("getJointA", &GearJoint::getJointA)
                .addFunction("getJointB", &GearJoint::getJointB)
                .addStaticFunction("getComponent", &GearJoint::getComponent)
            .endClass()
        .endNamespace();
}

} // namespace ngind::physics

#endif //NGIND_PHYSICS_JOINT_H
