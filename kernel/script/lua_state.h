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

class LuaState {
public:
    const static std::string SCRIPT_PATH;
    static LuaState* getInstance();
    static void destroyInstance();

    void loadScript(const std::vector<std::string>& filenames);
    void loadScript(const std::string& name);

    void preload(const std::string& path);

    void restart();

    luabridge::LuaRef createStateMachine(const std::string& classname);

    void destroyStateMachineInstance(luabridge::LuaRef& instance);

    inline lua_State* getState() {
        return _state;
    }
private:
    static LuaState* _instance;

    LuaState();
    ~LuaState();

    lua_State* _state;
    std::unordered_set<std::string> _visit;
    std::vector<std::string> _preload_list;
};

} // namespace ngind::script

#endif //NGIND_LUA_STATE_H