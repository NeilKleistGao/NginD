/**
 * @copybrief
 * MIT License
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

/// @file camera.h

#ifndef NGIND_CAMERA_H
#define NGIND_CAMERA_H

#include "include/glm/glm.hpp"
#include "resources/program_resource.h"
#include "script/lua_registration.h"

namespace ngind::rendering {
/**
 * Player's perspective in game. It can project rendered objects to
 * screen.
 */
class Camera {
public:
    /**
     * Get the instance of unique perspective in game
     * @return Camera*, pointer of instance
     */
    static Camera* getInstance();

    /**
     * Destroy the instance of unique perspective in game
     */
    static void destroyInstance();

    Camera(const Camera&) = delete;
    Camera& operator= (const Camera&) = delete;

    /**
     * Initialize perspective with position and size
     * @param center: the position of perspective
     * @param width: the width of perspective
     * @param height: the height of perspective
     */
    void init(const glm::vec2& center, const size_t& width, const size_t& height);

    /**
     * Move perspective to specified position
     * @param center: the center position of
     */
    inline void moveTo(const glm::vec2& center) {
        init(center, _width, _height);
    }

    /**
     * Get the view projection matrix
     * @return glm::mat4, the projection matrix
     */
    inline glm::mat4 getProjection() const {
        return _projection;
    }

    /**
     * Get perspective's size
     * @return Vector2D, the size
     */
    inline glm::vec2 getCameraSize() const {
        return glm::vec2{_width, _height};
    }

    /**
     * Capture a picture in the screen.
     * @param filename: the saved file's name
     */
    void capture(const std::string& filename) const;

    /**
     * Get camera's position
     * @return glm::vec2, camera's position
     */
    inline glm::vec2 getCameraPosition() const {
        return _center;
    }
private:
    Camera();
    ~Camera() = default;

    /**
     * The instance
     */
    static Camera* _instance;

    /**
     * The size
     */
    size_t _width, _height;

    /**
     * The central position of camera
     */
    glm::vec2 _center;

    /**
     * Projection matrix
     */
    glm::mat4 _projection;
};

NGIND_LUA_BRIDGE_REGISTRATION(Camera) {
    luabridge::getGlobalNamespace(script::LuaState::getInstance()->getState())
        .beginNamespace("engine")
            .beginClass<Camera>("Camera")
                .addStaticFunction("getInstance", &Camera::getInstance)
                .addFunction("moveTo", &Camera::moveTo)
                .addFunction("capture", &Camera::capture)
                .addFunction("getCameraPosition", &Camera::getCameraPosition)
            .endClass()
        .endNamespace();

    luabridge::setGlobal(script::LuaState::getInstance()->getState(), Camera::getInstance(), "Camera");
}

} // namespace ngind::rendering

#endif //NGIND_CAMERA_H
