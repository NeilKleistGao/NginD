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

/// @file archive.cc

#include "archive.h"

#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

#include "filesystem/file_input_stream.h"
#include "filesystem/file_output_stream.h"
#include "filesystem/cipher_output_stream.h"
#include "filesystem/cipher_input_stream.h"
#include "resources/config_resource.h"
#include "resources/resources_manager.h"
#include "game.h"
#include "settings.h"

namespace ngind::utils {
Archive* Archive::_instance = nullptr;
const std::string Archive::ARCHIVE_FILENAME = "NGIND_ARCHIVE.json";

Archive* Archive::getInstance() {
    if (_instance == nullptr) {
        _instance = new(std::nothrow) Archive();
        if (_instance == nullptr) {
            // TODO:
        }
    }

    return _instance;
}

void Archive::destroyInstance() {
    if (_instance != nullptr) {
        delete _instance;
        _instance = nullptr;
    }
}

Archive::Archive() {
    std::string content;
    if constexpr (CURRENT_MODE == MODE_RELEASE) {
        std::string temp = ARCHIVE_FILENAME;
        temp.replace(ARCHIVE_FILENAME.length() - 4, ARCHIVE_FILENAME.length(), "cson");
        auto stream = new filesystem::CipherInputStream(new filesystem::FileInputStream(temp));
        content = stream->readAllCharacters();
        stream->close();
    }
    else {
        auto stream = new filesystem::FileInputStream(ARCHIVE_FILENAME);
        content = stream->readAllCharacters();
        stream->close();
    }

    _doc.Parse(content.c_str());
}

Archive::~Archive() {
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    _doc.Accept(writer);
    std::string data = buffer.GetString();

    if constexpr (CURRENT_MODE == MODE_RELEASE) {
        std::string temp = ARCHIVE_FILENAME;
        temp.replace(ARCHIVE_FILENAME.length() - 4, ARCHIVE_FILENAME.length(), "cson");
        auto stream = new filesystem::CipherOutputStream(new filesystem::FileOutputStream(temp));
        stream->write(data);
        stream->close();
    }
    else {
        auto stream = new filesystem::FileOutputStream(ARCHIVE_FILENAME);
        stream->write(data);
        stream->close();
    }
}

void Archive::setString(const std::string& key, const std::string& value) {
    auto& v = _doc[key.c_str()];
    v.SetString(value.c_str(), value.length());
}

void Archive::setInteger(const std::string& key, int value) {
    auto& v = _doc[key.c_str()];
    v.SetInt(value);
}

void Archive::setFloat(const std::string& key, float value) {
    auto& v = _doc[key.c_str()];
    v.SetFloat(value);
}

void Archive::setBoolean(const std::string& key, bool value) {
    auto& v = _doc[key.c_str()];
    v.SetBool(value);
}

void Archive::dumpWorld(const std::string& name) {
    rapidjson::Document document;

}

std::string Archive::getString(const std::string& key) {
    auto& v = _doc[key.c_str()];
    return v.GetString();
}

int Archive::getInteger(const std::string& key) {
    auto& v = _doc[key.c_str()];
    return v.GetInt();
}

float Archive::getFloat(const std::string& key) {
    auto& v = _doc[key.c_str()];
    return v.GetFloat();
}

bool Archive::getBoolean(const std::string& key) {
    auto& v = _doc[key.c_str()];
    return v.GetBool();
}

void Archive::loadWorld(const std::string& name) {
    auto config = resources::ResourcesManager::getInstance()->load<resources::ConfigResource>(name);
    Game::getInstance()->loadWorld(config);
}

} // namespace ngind::utils
