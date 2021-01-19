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

namespace ngind::i18n {
class I18N {
public:
    const static std::string TEXT_PATH;
    static I18N* getInstance();
    static void destroyInstance();

    void loadLanguagePack(const LanguageCode& code, const std::string& filename);
    inline void use(const LanguageCode& code) {
        _lang = code;
    }
    std::string get(const std::string& name);
    std::string get(const size_t & index);
private:
    I18N() : _lang(LanguageCode::EN_US) {};
    ~I18N() = default;

    static I18N* _instance;
    using LabeledLanguagePack = std::map<std::string, std::string>;
    using DefaultLanguagePack = std::vector<std::string>;

    std::map<LanguageCode, LabeledLanguagePack> _data;
    std::map<LanguageCode, DefaultLanguagePack> _default;

    LanguageCode _lang;

    static std::unordered_map<LanguageCode, std::string> _mapping;
};

} // namespace ngind::i18n

#endif //NGIND_I18N_H
