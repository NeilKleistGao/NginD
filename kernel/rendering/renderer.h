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

/// @file rendering.h

#ifndef NGIND_RENDERER_H
#define NGIND_RENDERER_H

#include "rendering_queue.h"
#include "window.h"
#include "color.h"
#include "camera.h"

#include "script/lua_registration.h"

namespace ngind::rendering {

/**
 * This class is due to operations of rendering, including drawing on screen
 * and window management.
 */
class Renderer {
public:
    /**
     * Get the instance of rendering
     * @return Renderer*, the instance of rendering
     */
    static Renderer* getInstance();

    /**
     * Destroy the instance of rendering
     */
    static void destroyInstance();

    /**
     * Start rendering and check whether application should exit or not
     * @return bool, true if it should exit
     */
    bool startRenderingLoopOnce();

    /**
     * Create a window
     * @param width: width of window
     * @param height: height of window
     * @param title: title of window
     * @param icon: icon path of window
     * @param is_full: true if this window is fullscreen
     */
    void createWindow(int screen_width,
                      int screen_height,
                      int resolution_width,
                      int resolution_height,
                      const std::string& title,
                      const std::string& icon,
                      bool is_full);

    /**
     * Clean the scene
     * @param color: background color of scene
     */
    inline void clearScene(const Color& color) {
        glClearColor(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    /**
     * Add a rendering command to rendering queue
     * @param cmd: rendering command
     */
    inline void addRendererCommand(RenderingCommand* cmd) {
        _queue->push(cmd);
    }

    inline void setBlendFactor(const unsigned int& src, const unsigned int& dst) {
        glBlendFunc(src, dst);
    }

    void enableMultisampling(const bool& en);

    bool isMultisampling() const {
        return _multisampling;
    }

    inline void setFullScreen(bool enable) {
        _window->setFullScreen(enable);
    }

    inline glm::vec2 getWindowSize() const {
        return _window->getWindowSize();
    }

private:
    /**
     * The unique instance if rendering
     */
    static Renderer* _instance;

    /**
     * The instance of window
     */
    Window* _window;

    /**
     * Queue for rendering command
     */
    RenderingQueue* _queue;

    bool _multisampling;

    /**
     * Execute a rendering command
     * @param cmd: the command to be executed
     */
    void execute(RenderingCommand* cmd);

    Renderer();

    ~Renderer();
};

NGIND_LUA_BRIDGE_REGISTRATION(Renderer) {
    luabridge::getGlobalNamespace(script::LuaState::getInstance()->getState())
        .beginNamespace("engine")
            .beginClass<Renderer>("Renderer")
                .addStaticFunction("getInstance", &Renderer::getInstance)
                .addFunction("enableMultisampling", &Renderer::enableMultisampling)
                .addFunction("isMultisampling", &Renderer::isMultisampling)
            .endClass()
        .endNamespace();
}

} // namespace ngind::rendering

#endif //NGIND_RENDERER_H
