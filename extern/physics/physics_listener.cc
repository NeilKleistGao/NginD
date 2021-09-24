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

/// @file physics_listener.cc

#include "physics_listener.h"

#include "script/observer.h"

namespace ngind::physics {

void PhysicsListener::BeginContact(b2Contact* contact) {
    auto bodies = getContactingBodies(contact);

    if (bodies.first != nullptr && bodies.second != nullptr) {
        auto filter_a = contact->GetFixtureA()->GetFilterData(),
             filter_b = contact->GetFixtureB()->GetFilterData();

        if (filter_a.categoryBits & filter_b.maskBits) {
            sendMessage("BeginContact", bodies.first->getParent(), bodies.second->getParent());
        }
        if (filter_a.maskBits & filter_b.categoryBits) {
            sendMessage("BeginContact", bodies.second->getParent(), bodies.first->getParent());
        }
    }
}

void PhysicsListener::EndContact(b2Contact* contact) {
    auto bodies = getContactingBodies(contact);

    if (bodies.first != nullptr && bodies.second != nullptr) {
        auto filter_a = contact->GetFixtureA()->GetFilterData(),
             filter_b = contact->GetFixtureB()->GetFilterData();

        if (filter_a.categoryBits & filter_b.maskBits) {
            sendMessage("EndContact", bodies.first->getParent(), bodies.second->getParent());
        }
        if (filter_a.maskBits & filter_b.categoryBits) {
            sendMessage("EndContact", bodies.second->getParent(), bodies.first->getParent());
        }
    }
}

void PhysicsListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
}

void PhysicsListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {
}

std::pair<RigidBody*, RigidBody*> PhysicsListener::getContactingBodies(b2Contact* contact) {
    auto fix_a = contact->GetFixtureA(),
         fix_b = contact->GetFixtureB();

    auto body_a = fix_a->GetBody(),
         body_b = fix_b->GetBody();

    auto rba = reinterpret_cast<RigidBody*>(body_a->GetUserData().pointer),
         rbb = reinterpret_cast<RigidBody*>(body_b->GetUserData().pointer);

    return std::make_pair(rba, rbb);
}

void PhysicsListener::sendMessage(const std::string& name, objects::Object* sender, objects::Object* other) {
    auto ob = script::Observer::getInstance();
    luabridge::setGlobal(script::LuaState::getInstance()->getState(), other, "__PHYSICS_CONTACT_DATA__");
    ob->notifySiblings("BeginContact", sender, luabridge::getGlobal(script::LuaState::getInstance()->getState(), "__PHYSICS_CONTACT_DATA__"));
    luabridge::setGlobal(script::LuaState::getInstance()->getState(), 0, "__PHYSICS_CONTACT_DATA__");
}

} // namespace ngind::physics