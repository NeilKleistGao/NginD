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
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/// @file game.h

#ifndef NGIND_GAME_H
#define NGIND_GAME_H

#include <map>
#include <string>
#include <stack>

#include "resources/config_resource.h"
#include "timer/timer.h"
#include "objects/world.h"
#include "script/lua_registration.h"

namespace ngind {

/**
 * Game manager class. It's a singleton class and manages all game works.
 */
class Game {
public:
    /**
     * Get instance of game manager.
     * @return Game*, instance of game manager
     */
    static Game* getInstance();

    /**
     * Destroy instance of game manager.
     */
    static void destroyInstance();

    /**
     * Load a game world into memory
     * @param name: world's name
     */
    void loadWorld(const std::string& name);

    void loadWorld(resources::ConfigResource* config);

    /**
     * Destroy a game world
     * @param name: world's name
     */
    void destroyWorld(const std::string& name);

    /**
     * Push current world into stack and load a new one
     * @param name: world's name
     */
    void pushAndLoadWorld(const std::string& name);

    /**
     * Pop a world from stack and load it.
     * @param has_destroy_current: true if destroy current world later
     */
    void popAndLoadWorld(const bool& has_destroy_current);

    /**
     * Load a game world into memory and destroy current world
     * @param name: world's name
     */
    void destroyAndLoadWorld(std::string name);

    /**
     * Start playing game.
     */
    void start();

    /**
     * Get current world
     * @return World*, current world
     */
    inline objects::World* getCurrentWorld() {
        return _current_world;
    }

    /**
     * Quit game.
     */
    inline void quit() {
        this->_loop_flag = false;
    }

    inline std::string getCurrentWorldName() {
        return this->_current_world->getName();
    }

private:
    Game();
    ~Game();

    /**
     * Instance of game manager
     */
    static Game* _instance;

    /**
     * Global config data
     */
    resources::ConfigResource* _global_settings;

    /**
     * Global timer
     */
    timer::Timer _global_timer;

    /**
     * Current world
     */
    objects::World* _current_world;

    /**
     * Worlds dictionary
     */
    std::map<std::string, objects::World*> _worlds;

    /**
     * Worlds stack
     */
    std::stack<objects::World*> _stack;

    /**
     * Whether game still goes on
     */
    bool _loop_flag;

    std::function<void(void)> _transition;
    bool _trans_next;
    std::string _next_world;
};

NGIND_LUA_BRIDGE_REGISTRATION(Input) {
    luabridge::getGlobalNamespace(script::LuaState::getInstance()->getState())
        .beginNamespace("engine")
            .beginClass<Game>("Game")
                .addStaticFunction("getInstance", &Game::getInstance)
                .addFunction("quit", &Game::quit)
                .addFunction("destroyAndLoadWorld", &Game::destroyAndLoadWorld)
                .addFunction("getCurrentWorldName", &Game::getCurrentWorldName)
            .endClass()
        .endNamespace();
}

} // namespace ngind

#endif //NGIND_GAME_H
