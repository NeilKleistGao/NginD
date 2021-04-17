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

} // namespace ngind::physics
