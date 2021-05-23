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

/// @file physics_manager.h

#ifndef NGIND_PHYSICS_WORLD_H
#define NGIND_PHYSICS_WORLD_H

#include "kernel/components/component.h"
#include "box2d/box2d.h"
#include "kernel/script/lua_registration.h"
#include "kernel/components/component_factory.h"
#include "physics_listener.h"

namespace ngind::objects {
class Object;
} // namespace ngind::objects

namespace ngind::physics {

class RigidBody;
class DistanceJoint;
class RevoluteJoint;
class PrismaticJoint;
class PulleyJoint;
class GearJoint;

class PhysicsWorld : public components::Component {
public:
    PhysicsWorld();
    ~PhysicsWorld() override;
    PhysicsWorld(const PhysicsWorld&) = delete;
    PhysicsWorld& operator= (const PhysicsWorld&) = delete;

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

    static PhysicsWorld* create(const typename resources::ConfigResource::JsonObject& data);

    inline void setGravity(const float& x, const float& y) {
        _gravity = b2Vec2(x, y);
        _world.SetGravity(_gravity);
    }

    inline void setGravityX(float x) {
        _world.SetGravity({x, _world.GetGravity().y});
    }

    inline void setGravityY(float y) {
        _world.SetGravity({_world.GetGravity().x, y});
    }

    inline glm::vec2 getGravity() const {
        auto temp = _world.GetGravity();
        return {temp.x, temp.y};
    }

    inline float getGravityX() const {
        return _gravity.x;
    }

    inline float getGravityY() const {
        return _gravity.y;
    }

    friend class RigidBody;
    friend class DistanceJoint;
    friend class RevoluteJoint;
    friend class PrismaticJoint;
    friend class PulleyJoint;
    friend class GearJoint;
    friend class objects::Object;
private:
    b2Vec2 _gravity;
    b2World _world;
    PhysicsListener listener;

    void clearRigidBody(objects::Object* node);
};

NGIND_LUA_BRIDGE_REGISTRATION(PhysicsWorld) {
    components::ComponentFactory::getInstance()->registerComponent<PhysicsWorld>("PhysicsWorld");
    luabridge::getGlobalNamespace(script::LuaState::getInstance()->getState())
        .beginNamespace("engine")
            .deriveClass<PhysicsWorld, components::Component>("PhysicsWorld")
                .addFunction("setGravity", &PhysicsWorld::setGravity)
                .addFunction("setGravityX", &PhysicsWorld::setGravityX)
                .addFunction("setGravityY", &PhysicsWorld::setGravityY)
                .addFunction("getGravity", &PhysicsWorld::getGravity)
                .addFunction("getGravityX", &PhysicsWorld::getGravityX)
                .addFunction("getGravityY", &PhysicsWorld::getGravityY)
            .endClass()
        .endNamespace();
}

} // namespace ngind::physics

#endif //NGIND_PHYSICS_WORLD_H
