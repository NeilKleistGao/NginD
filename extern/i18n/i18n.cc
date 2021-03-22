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

/// @file i18n.cc

#include "i18n.h"

#include "filesystem/file_input_stream.h"
#include "filesystem/cipher_input_stream.h"
#include "settings.h"
#include "script/lua_state.h"

namespace ngind::i18n {
const std::string I18N::TEXT_PATH = "resources/text";
I18N* I18N::_instance = nullptr;
std::unordered_map<LanguageCode, std::string> I18N::_mapping = {
        {LanguageCode::EN_US, TEXT_PATH + "/en-us"},
        {LanguageCode::ZH_CN, TEXT_PATH + "/zh-cn"},
        {LanguageCode::JA_JP, TEXT_PATH + "/ja-jp"},
        {LanguageCode::FR_FR, TEXT_PATH + "/fr-fr"},
        {LanguageCode::DE_DE, TEXT_PATH + "/de-de"}
};

I18N::I18N() : _lang(LanguageCode::EN_US) {
}

I18N* I18N::getInstance() {
    if (_instance == nullptr) {
        _instance = new I18N{};
    }

    return _instance;
}

void I18N::destroyInstance() {
    if (_instance != nullptr) {
       delete _instance;
       _instance = nullptr;
    }
}

void I18N::loadLanguagePack(const int& icode, const std::string& filename) {
    auto code = static_cast<LanguageCode>(icode);
    if (_data.find(code) != _data.end()) {
        return;
    }

    _data[code] = LabeledLanguagePack{};
    _default[code] = DefaultLanguagePack{};

    std::string content;
    if constexpr (CURRENT_MODE == MODE_RELEASE) {
        std::string temp = filename;
        temp.replace(filename.length() - 4, filename.length(), "cini");
        auto fp = new filesystem::CipherInputStream(new filesystem::FileInputStream{_mapping[code] + "/" + temp});
        content = fp->readAllCharacters();
        fp->close();
    }
    else {
        auto fp = new filesystem::FileInputStream{_mapping[code] + "/" + filename};
        content = fp->readAllCharacters();
        fp->close();
    }

    content += static_cast<char>(-1);
    std::string key, value;
    bool flag = false;
    for (const char& c : content) {
        if (c == -1) {
            if (!flag) {
                _default[code].push_back(key);
            }
            else {
                _data[code][key] = value;
                _default[code].push_back(value);
            }
            break;
        }
        else if (c == '=') {
            flag = true;
        }
        else if (c == '\n') {
            if (!flag) {
                _default[code].push_back(key);
            }
            else {
                _data[code][key] = value;
                _default[code].push_back(value);
            }

            flag = false;
        }
        else {
            if (!flag) {
                key += c;
            }
            else {
                value += c;
            }
        }
    }
}

std::string I18N::getByName(const std::string& name) {
    if (_data.find(_lang) == _data.end()) {
        // TODO:
    }

    auto& pack = _data[_lang];
    if (pack.find(name) != pack.end()) {
        return pack[name];
    }

    return "";
}

std::string I18N::getByIndex(const size_t & index) {
    if (_default.find(_lang) == _default.end()) {
        // TODO:
    }

    auto& pack = _default[_lang];
    if (pack.size() > index) {
        return pack[index];
    }

    return "";
}

} // namespace ngind::i18n