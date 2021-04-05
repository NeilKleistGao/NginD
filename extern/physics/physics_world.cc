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

/// @file physics_manager.cc

#include "physics_world.h"

namespace ngind::physics {

PhysicsWorld::PhysicsWorld() : components::Component(), _gravity(0, -9.8), _world(_gravity) {
}

PhysicsWorld::~PhysicsWorld() {
    clearRigidBody(_parent);
}

void PhysicsWorld::update(const float& delta) {
    components::Component::update(delta);
    _world.Step(delta, 8, 3);
}

void PhysicsWorld::init(const typename resources::ConfigResource::JsonObject& data) {
    auto gravity = data["gravity"].GetObject();
    setGravity(gravity["x"].GetFloat(), gravity["y"].GetFloat());
    _world.SetContinuousPhysics(true);
    _world.SetAllowSleeping(true);
    _world.SetContactListener(&listener);
}

PhysicsWorld* PhysicsWorld::create(const typename resources::ConfigResource::JsonObject& data) {
    auto* world = memory::MemoryPool::getInstance()->create<PhysicsWorld>();
    world->init(data);
    return world;
}

void PhysicsWorld::clearRigidBody(objects::Object* node) {
    auto body = node->getComponent<RigidBody>("RigidBody");
    if (body != nullptr) {
        _world.DestroyBody(body->getBody());
    }

    auto children = node->getChildren();
    for (auto* child : children) {
        clearRigidBody(child);
    }
}

} // namespace ngind::physics