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

/// @file physics_joint.cc

#include "physics_joint.h"

#include "kernel/game.h"
#include "physics_world.h"

namespace ngind::physics {

PhysicsJoint::~PhysicsJoint() {
    if (_joint != nullptr) {
        // TODO:
    }
}

glm::vec2 PhysicsJoint::getAnchorA() const {
    if (_joint == nullptr) {
        // TODO: warning
        return glm::vec2 {};
    }

    auto b2vec = _joint->GetAnchorA();
    return glm::vec2 {b2vec.x, b2vec.y};
}

glm::vec2 PhysicsJoint::getAnchorB() const {
    if (_joint == nullptr) {
        // TODO: warning
        return glm::vec2 {};
    }

    auto b2vec = _joint->GetAnchorB();
    return glm::vec2 {b2vec.x, b2vec.y};
}

void PhysicsJoint::setBodies() {
    auto game = Game::getInstance();
    auto world = game->getCurrentWorld();

    _body_a = world->getChildByID(_index_a)->getComponent<RigidBody>("RigidBody");
    _body_b = world->getChildByID(_index_b)->getComponent<RigidBody>("RigidBody");
}

void DistanceJoint::update(const float& delta) {
    if (_body_a == nullptr || _body_b == nullptr) {
        setBodies();

        if (_body_a == nullptr || _body_b == nullptr) {
            return;
        }

        _def.Initialize(_body_a->getBody(), _body_b->getBody(),
                        b2Vec2{_anchor_a.x, _anchor_a.y}, b2Vec2{_anchor_b.x, _anchor_b.y});

        _def.length = _length;
        _def.minLength = _min_length;
        _def.maxLength = _max_length;
        _def.damping = _damping;
        _def.stiffness = _stiffness;
        _def.collideConnected = _collide;

        auto game = Game::getInstance();
        auto world = game->getCurrentWorld();

        auto pw = world->getComponent<PhysicsWorld>("PhysicsWorld");
        _joint = pw->_world.CreateJoint(&_def);
    }
}

void DistanceJoint::init(const typename resources::ConfigResource::JsonObject& data) {
    _index_a = data["index-a"].GetInt();
    _index_b = data["index-b"].GetInt();

    _length = data["length"].GetFloat();
    _min_length = data["min-length"].GetFloat();
    _max_length = data["max-length"].GetFloat();
    _damping = data["damping"].GetFloat();
    _stiffness = data["stiffness"].GetFloat();
    _collide = data["collide"].GetBool();

    auto anchor_a = data["anchor-a"].GetObject();
    auto anchor_b = data["anchor-b"].GetObject();

    _anchor_a = {anchor_a["x"].GetFloat(), anchor_a["y"].GetFloat()};
    _anchor_b = {anchor_b["x"].GetFloat(), anchor_b["y"].GetFloat()};
}

DistanceJoint* DistanceJoint::create(const typename resources::ConfigResource::JsonObject& data) {
    auto* joint = memory::MemoryPool::getInstance()->create<DistanceJoint>();
    joint->init(data);
    return joint;
}

void RevoluteJoint::update(const float& delta) {
    if (_body_a == nullptr || _body_b == nullptr) {
        setBodies();

        if (_body_a == nullptr || _body_b == nullptr) {
            return;
        }

        _def.Initialize(_body_a->getBody(), _body_b->getBody(), {_center.x, _center.y});

        _def.enableLimit = _enable_limit;
        _def.enableMotor = _enable_motor;
        _def.maxMotorTorque = _max_motor;
        _def.motorSpeed = _motor_speed;
        _def.lowerAngle = _lower_angle;
        _def.upperAngle = _upper_angle;
        _def.collideConnected = _collide;

        auto game = Game::getInstance();
        auto world = game->getCurrentWorld();

        auto pw = world->getComponent<PhysicsWorld>("PhysicsWorld");
        _joint = pw->_world.CreateJoint(&_def);
    }
}

void RevoluteJoint::init(const typename resources::ConfigResource::JsonObject& data) {
    _index_a = data["index-a"].GetInt();
    _index_b = data["index-b"].GetInt();

    _collide = data["collide"].GetBool();
    _enable_limit = data["enable-limit"].GetBool();
    _enable_motor = data["enable-motor"].GetBool();
    _max_motor = data["max-motor"].GetFloat();
    _motor_speed = data["motor-speed"].GetFloat();
    _lower_angle = data["lower-angle"].GetFloat();
    _upper_angle = data["upper-angle"].GetFloat();

    auto center = data["center"].GetObject();
    _center = {center["x"].GetFloat(), center["y"].GetFloat()};
}

RevoluteJoint* RevoluteJoint::create(const typename resources::ConfigResource::JsonObject& data) {
    auto* joint = memory::MemoryPool::getInstance()->create<RevoluteJoint>();
    joint->init(data);
    return joint;
}

void PrismaticJoint::update(const float& delta) {
    if (_body_a == nullptr || _body_b == nullptr) {
        setBodies();

        if (_body_a == nullptr || _body_b == nullptr) {
            return;
        }

        auto game = Game::getInstance();
        auto world = game->getCurrentWorld();

        _def.Initialize(_body_a->getBody(), _body_b->getBody(), {_center.x, _center.y}, {_axis.x, _axis.y});

        _def.enableLimit = _enable_limit;
        _def.enableMotor = _enable_motor;
        _def.motorSpeed = _motor_speed;
        _def.collideConnected = _collide;
        _def.maxMotorForce = _max_force;
        _def.lowerTranslation = _lower_trans;
        _def.upperTranslation = _upper_trans;

        auto pw = world->getComponent<PhysicsWorld>("PhysicsWorld");
        _joint = pw->_world.CreateJoint(&_def);
    }
}

void PrismaticJoint::init(const typename resources::ConfigResource::JsonObject& data) {
    _index_a = data["index-a"].GetInt();
    _index_b = data["index-b"].GetInt();

    _motor_speed = data["motor-speed"].GetFloat();
    _enable_motor = data["enable-motor"].GetBool();
    _enable_limit = data["enable-limit"].GetBool();
    _lower_trans = data["lower-trans"].GetFloat();
    _upper_trans = data["upper-trans"].GetFloat();
    _max_force = data["max-force"].GetFloat();
    _collide = data["collide"].GetBool();

    auto center = data["center"].GetObject();
    _center = {center["x"].GetFloat(), center["y"].GetFloat()};
    auto axis = data["axis"].GetObject();
    _axis = {axis["x"].GetFloat(), axis["y"].GetFloat()};
}

PrismaticJoint* PrismaticJoint::create(const typename resources::ConfigResource::JsonObject& data) {
    auto* joint = memory::MemoryPool::getInstance()->create<PrismaticJoint>();
    joint->init(data);
    return joint;
}

void PulleyJoint::update(const float& delta) {
    if (_body_a == nullptr || _body_b == nullptr) {
        setBodies();

        if (_body_a == nullptr || _body_b == nullptr) {
            return;
        }

        auto game = Game::getInstance();
        auto world = game->getCurrentWorld();

        _def.Initialize(_body_a->getBody(), _body_b->getBody(),
                        {_ground_a.x, _ground_a.y},
                        {_ground_b.x, _ground_b.y},
                        {_anchor_a.x, _anchor_a.y},
                        {_anchor_b.x, _anchor_b.y}, _ratio);
        _def.collideConnected = _collide;

        auto pw = world->getComponent<PhysicsWorld>("PhysicsWorld");
        _joint = pw->_world.CreateJoint(&_def);
    }
}

void PulleyJoint::init(const typename resources::ConfigResource::JsonObject& data) {
    _index_a = data["index-a"].GetInt();
    _index_b = data["index-b"].GetInt();

    _collide = data["collide"].GetBool();

    auto temp1 = data["anchor-a"].GetObject();
    _anchor_a = {temp1["x"].GetFloat(), temp1["y"].GetFloat()};
    auto temp2 = data["anchor-b"].GetObject();
    _anchor_b = {temp2["x"].GetFloat(), temp2["y"].GetFloat()};
    auto temp3 = data["ground-a"].GetObject();
    _ground_a = {temp3["x"].GetFloat(), temp3["y"].GetFloat()};
    auto temp4 = data["ground-b"].GetObject();
    _ground_b = {temp4["x"].GetFloat(), temp4["y"].GetFloat()};
}

PulleyJoint* PulleyJoint::create(const typename resources::ConfigResource::JsonObject& data) {
    auto* joint = memory::MemoryPool::getInstance()->create<PulleyJoint>();
    joint->init(data);
    return joint;
}

void GearJoint::update(const float& delta) {
    if (_body_a == nullptr || _body_b == nullptr) {
        setBodies();

        if (_body_a == nullptr || _body_b == nullptr) {
            return;
        }

        auto game = Game::getInstance();
        auto world = game->getCurrentWorld();

        _def.bodyA = _body_a->getBody();
        _def.bodyB = _body_b->getBody();
        _def.joint1 = world->getChildByID(_joint_a)->getComponent<PhysicsJoint>(_name_a)->getJoint();
        _def.joint2 = world->getChildByID(_joint_b)->getComponent<PhysicsJoint>(_name_b)->getJoint();
        _def.ratio = _ratio;
        _def.collideConnected = _collide;

        auto pw = world->getComponent<PhysicsWorld>("PhysicsWorld");
        _joint = pw->_world.CreateJoint(&_def);
    }
}

void GearJoint::init(const typename resources::ConfigResource::JsonObject& data) {
    _index_a = data["index-a"].GetInt();
    _index_b = data["index-b"].GetInt();

    _joint_a = data["index-a"].GetInt();
    _joint_b = data["index-b"].GetInt();
    _name_a = data["name-a"].GetString();
    _name_b = data["name-b"].GetString();

    _collide = data["collide"].GetBool();
    _ratio = data["ratio"].GetFloat();
}

GearJoint* GearJoint::create(const typename resources::ConfigResource::JsonObject& data) {
    auto* joint = memory::MemoryPool::getInstance()->create<GearJoint>();
    joint->init(data);
    return joint;
}

} // namespace ngind::physics
