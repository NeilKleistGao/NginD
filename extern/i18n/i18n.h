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

/// @file i18n.h

#ifndef NGIND_I18N_H
#define NGIND_I18N_H

#include <string>
#include <map>
#include <unordered_map>
#include <vector>

#include "lang_code.h"
#include "kernel/script/lua_registration.h"

namespace ngind::i18n {
/**
 * Internationalisation helper.
 */
class I18N {
public:
    /**
     * Text resources path.
     */
    const static std::string TEXT_PATH;

    /**
     * Get the unique instance of I18N helper.
     * @return I18N*, the unique instance
     */
    static I18N* getInstance();

    /**
     * Destroy the unique instance.
     */
    static void destroyInstance();

    /**
     * Load language package from file.
     * @param icode: language code
     * @param filename: filename of package
     */
    void loadLanguagePack(const int& icode, const std::string& filename);

    /**
     * Use another language package.
     * @param code: language code
     */
    inline void use(const int& code) {
        _lang = static_cast<LanguageCode>(code);
    }

    /**
     * Get text by name.
     * @param name: name of text item
     * @return std::string, the I18N text
     */
    std::string getByName(const std::string& name);

    /**
     * Get text by index.
     * @param index: index of text item
     * @return std::string, the I18N text
     */
    std::string getByIndex(const size_t & index);
private:
    I18N();
    ~I18N() = default;

    /**
     * The unique instance.
     */
    static I18N* _instance;
    using LabeledLanguagePack = std::map<std::string, std::string>;
    using DefaultLanguagePack = std::vector<std::string>;

    /**
     * Labeled data.
     */
    std::map<LanguageCode, LabeledLanguagePack> _data;

    /**
     * All data with a default index.
     */
    std::map<LanguageCode, DefaultLanguagePack> _default;

    /**
     * Current language.
     */
    LanguageCode _lang;

    /**
     * A mapping from language code to string.
     */
    static std::unordered_map<LanguageCode, std::string> _mapping;
};

NGIND_LUA_BRIDGE_REGISTRATION(I18N) {
    luabridge::getGlobalNamespace(script::LuaState::getInstance()->getState())
        .beginNamespace("engine")
            .beginClass<I18N>("I18N")
                .addStaticFunction("getInstance", &I18N::getInstance)
                .addFunction("loadLanguagePack", &I18N::loadLanguagePack)
                .addFunction("use", &I18N::use)
                .addFunction("getByName", &I18N::getByName)
                .addFunction("getByIndex", &I18N::getByIndex)
            .endClass()
        .endNamespace();
    script::LuaState::getInstance()->preload("extern/i18n");
}

} // namespace ngind::i18n

#endif //NGIND_I18N_H
