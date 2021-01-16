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

/// @file lua_state.h

#ifndef NGIND_LUA_STATE_H
#define NGIND_LUA_STATE_H

#include <string>
#include <unordered_set>
#include <vector>

#include "lua/lua.hpp"
#include "LuaBridge/LuaBridge.h"

namespace ngind::script {

/**
 * The lua runtime environment.
 */
class LuaState {
public:
    /**
     * Script files path.
     */
    const static std::string SCRIPT_PATH;

    /**
     * Get environment instance.
     * @return LuaState*, the instance
     */
    static LuaState* getInstance();

    /**
     * Destroy the environment instance.
     */
    static void destroyInstance();

    /**
     * Load scripts on list.
     * @param filenames: filenames list
     */
    void loadScript(const std::vector<std::string>& filenames);

    /**
     * Load a script.
     * @param name: name of script
     */
    void loadScript(const std::string& name);

    /**
     * Preload scripts in a fold. These scripts will be loaded again automatically when restarting.
     * @param path: the preload fold's name
     */
    void preload(const std::string& path);

    /**
     * Restart the interpreter.
     */
    void restart();

    /**
     * Create a state machine driven by lua.
     * @param classname: state machine class name
     * @return luabridge::LuaRef, the reference of state machine
     */
    luabridge::LuaRef createStateMachine(const std::string& classname);

    /**
     * Destroy a state machine driven by lua.
     * @param instance: the reference of state machine
     */
    void destroyStateMachineInstance(luabridge::LuaRef& instance);

    /**
     * Get native lua state point.
     * @return lua_State*, the native lua state point
     */
    inline lua_State* getState() {
        return _state;
    }
private:
    /**
     * The instance of lua state
     */
    static LuaState* _instance;

    LuaState();
    ~LuaState();

    /**
     * Native lua state point
     */
    lua_State* _state;

    /**
     * Visit list recording files that have been loaded
     */
    std::unordered_set<std::string> _visit;

    /**
     * Preloading files list
     */
    std::vector<std::string> _preload_list;
};

} // namespace ngind::script

#endif //NGIND_LUA_STATE_H
