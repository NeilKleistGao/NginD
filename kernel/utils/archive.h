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

/// @file archive.h

#ifndef NGIND_ARCHIVE_H
#define NGIND_ARCHIVE_H

#include <string>

#include "rapidjson/document.h"

#include "script/lua_registration.h"

namespace ngind::utils {

/**
 * Archive manager used to save simple user data.
 */
class Archive {
public:
    /**
     * Get the unique instance of archive. If it does not exist, this function will create one.
     * @return Archive*, the unique instance
     */
    static Archive* getInstance();

    /**
     * Destroy the instance if it exists.
     */
    static void destroyInstance();

    /**
     * Save string variable.
     * @param key: variable's key
     * @param value: variable's value
     */
    void setString(const std::string& key, const std::string& value);

    /**
     * Save integer variable.
     * @param key: variable's key
     * @param value: variable's value
     */
    void setInteger(const std::string& key, int value);

    /**
     * Save float variable.
     * @param key: variable's key
     * @param value: variable's value
     */
    void setFloat(const std::string& key, float value);

    /**
     * Save boolean variable.
     * @param key: variable's key
     * @param value: variable's value
     */
    void setBoolean(const std::string& key, bool value);

    /**
     * Read string variable.
     * @param key: variable's key
     * @param default_value: default value if the key does not exist
     * @return std::string, string variable
     */
    std::string getString(const std::string& key, const std::string& default_value);

    /**
     * Read integer variable.
     * @param key: variable's key
     * @param default_value: default value if the key does not exist
     * @return int, integer variable
     */
    int getInteger(const std::string& key, int default_value);

    /**
     * Read float variable.
     * @param key: variable's key
     * @param default_value: default value if the key does not exist
     * @return float, float variable
     */
    float getFloat(const std::string& key, float default_value);

    /**
     * Read boolean variable.
     * @param key: variable's key
     * @param default_value: default value if the key does not exist
     * @return bool, boolean variable
     */
    bool getBoolean(const std::string& key, bool default_value);
private:
    /**
     * The unique instance.
     */
    static Archive* _instance;

    /**
     * Archive document.
     */
    rapidjson::Document _doc;

    Archive();
    ~Archive();
};

NGIND_LUA_BRIDGE_REGISTRATION(Archive) {
    luabridge::getGlobalNamespace(script::LuaState::getInstance()->getState())
        .beginNamespace("engine")
            .beginClass<Archive>("Archive")
                .addStaticFunction("getInstance", &Archive::getInstance)
                .addFunction("setString", &Archive::setString)
                .addFunction("setInteger", &Archive::setInteger)
                .addFunction("setFloat", &Archive::setFloat)
                .addFunction("setBoolean", &Archive::setBoolean)
                .addFunction("getString", &Archive::getString)
                .addFunction("getInteger", &Archive::getInteger)
                .addFunction("getFloat", &Archive::getFloat)
                .addFunction("getBoolean", &Archive::getBoolean)
            .endClass()
        .endNamespace();

    luabridge::setGlobal(script::LuaState::getInstance()->getState(), Archive::getInstance(), "Archive");
}

} // namespace ngind::utils

#endif //NGIND_ARCHIVE_H
