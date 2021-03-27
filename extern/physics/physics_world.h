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

namespace ngind::physics {

class RigidBody;

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

    inline float getGravityX() const {
        return _gravity.x;
    }

    inline float getGravityY() const {
        return _gravity.y;
    }

    friend class RigidBody;
private:
    b2Vec2 _gravity;
    b2World _world;
    PhysicsListener listener;
};

NGIND_LUA_BRIDGE_REGISTRATION(PhysicsWorld) {
    components::ComponentFactory::getInstance()->registerComponent<PhysicsWorld>("PhysicsWorld");
}

} // namespace ngind::physics

#endif //NGIND_PHYSICS_WORLD_H
