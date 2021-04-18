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
    PhysicsJoint()
        : components::Component(),
        _joint(nullptr), _body_a(nullptr), _body_b(nullptr),
        _index_a(0), _index_b(0)
        {}
    ~PhysicsJoint() override;

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

    inline b2Joint* getJoint() {
        return _joint;
    }
private:
protected:
    b2Joint* _joint;

    int _index_a;
    int _index_b;

    RigidBody* _body_a;
    RigidBody* _body_b;

    bool _collide;

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

    static DistanceJoint* create(const typename resources::ConfigResource::JsonObject& data);
private:
    b2DistanceJointDef _def;

    glm::vec2 _anchor_a;
    glm::vec2 _anchor_b;

    float _length;
    float _min_length;
    float _max_length;
    float _damping;
    float _stiffness;
};

NGIND_LUA_BRIDGE_REGISTRATION(DistanceJoint) {
    components::ComponentFactory::getInstance()->registerComponent<DistanceJoint>("DistanceJoint");

    luabridge::getGlobalNamespace(script::LuaState::getInstance()->getState())
        .beginNamespace("engine")
            .deriveClass<DistanceJoint, PhysicsJoint>("DistanceJoint")
            .endClass()
        .endNamespace();
}

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

    static RevoluteJoint* create(const typename resources::ConfigResource::JsonObject& data);
private:
    b2RevoluteJointDef _def;

    float _lower_angle;
    float _upper_angle;
    bool _enable_limit;
    float _max_motor;
    float _motor_speed;
    bool _enable_motor;

    glm::vec2 _center;
};

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

    static PrismaticJoint* create(const typename resources::ConfigResource::JsonObject& data);
private:
    b2PrismaticJointDef _def;

    glm::vec2 _center;
    glm::vec2 _axis;

    float _lower_trans;
    float _upper_trans;
    bool _enable_limit;
    float _max_force;
    float _motor_speed;
    bool _enable_motor;
};

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

    static PulleyJoint* create(const typename resources::ConfigResource::JsonObject& data);
private:
    b2PulleyJointDef _def;

    float _ratio;
    glm::vec2 _anchor_a;
    glm::vec2 _anchor_b;
    glm::vec2 _ground_a;
    glm::vec2 _ground_b;
};

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

    static GearJoint* create(const typename resources::ConfigResource::JsonObject& data);
private:
    b2GearJointDef _def;

    int _joint_a;
    int _joint_b;
    float _ratio;

    std::string _name_a;
    std::string _name_b;
};

} // namespace ngind::physics

#endif //NGIND_PHYSICS_JOINT_H
