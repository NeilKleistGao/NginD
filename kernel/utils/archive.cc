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
#include "settings.h"
#include "log/logger_factory.h"

namespace ngind::utils {
Archive* Archive::_instance = nullptr;
const std::string Archive::ARCHIVE_FILENAME = "NGIND_ARCHIVE.json";

Archive* Archive::getInstance() {
    if (_instance == nullptr) {
        _instance = new(std::nothrow) Archive();
        if (_instance == nullptr) {
            auto logger = log::LoggerFactory::getInstance()->getLogger("crash.log", log::LogLevel::LOG_LEVEL_ERROR);
            logger->log("Can't create archive instance.");
            logger->flush();
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

    if (content.empty()) {
        content = "{}";
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
    if (!_doc.HasMember(key.c_str())) {
        auto& allocator = _doc.GetAllocator();
        auto rk = rapidjson::Value();
        rk.SetString(key.c_str(), key.length());
        auto rv = rapidjson::Value();
        rv.SetString(value.c_str(), value.length());
        _doc.AddMember(rk.Move(), rv.Move(), allocator);
    }
    else {
        auto& v = _doc[key.c_str()];
        v.SetString(value.c_str(), value.length());
    }
}

void Archive::setInteger(const std::string& key, int value) {
    if (!_doc.HasMember(key.c_str())) {
        auto& allocator = _doc.GetAllocator();
        auto rk = rapidjson::Value();
        rk.SetString(key.c_str(), key.length());
        auto rv = rapidjson::Value();
        rv.SetInt(value);
        _doc.AddMember(rk.Move(), rv.Move(), allocator);
    }
    else {
        auto& v = _doc[key.c_str()];
        v.SetInt(value);
    }
}

void Archive::setFloat(const std::string& key, float value) {
    if (!_doc.HasMember(key.c_str())) {
        auto& allocator = _doc.GetAllocator();
        auto rk = rapidjson::Value();
        rk.SetString(key.c_str(), key.length());
        auto rv = rapidjson::Value();
        rv.SetFloat(value);
        _doc.AddMember(rk.Move(), rv.Move(), allocator);
    }
    else {
        auto& v = _doc[key.c_str()];
        v.SetFloat(value);
    }
}

void Archive::setBoolean(const std::string& key, bool value) {
    if (!_doc.HasMember(key.c_str())) {
        auto& allocator = _doc.GetAllocator();
        auto rk = rapidjson::Value();
        rk.SetString(key.c_str(), key.length());
        auto rv = rapidjson::Value();
        rv.SetBool(value);
        _doc.AddMember(rk.Move(), rv.Move(), allocator);
    }
    else {
        auto& v = _doc[key.c_str()];
        v.SetBool(value);
    }
}

std::string Archive::getString(const std::string& key, const std::string& default_value) {
    if (_doc.HasMember(key.c_str())) {
        auto& v = _doc[key.c_str()];
        return v.GetString();
    }

    return default_value;
}

int Archive::getInteger(const std::string& key, int default_value) {
    if (_doc.HasMember(key.c_str())) {
        auto& v = _doc[key.c_str()];
        return v.GetInt();
    }

    return default_value;
}

float Archive::getFloat(const std::string& key, float default_value) {
    if (_doc.HasMember(key.c_str())) {
        auto& v = _doc[key.c_str()];
        return v.GetFloat();
    }

    return default_value;
}

bool Archive::getBoolean(const std::string& key, bool default_value) {
    if (_doc.HasMember(key.c_str())) {
        auto& v = _doc[key.c_str()];
        return v.GetBool();
    }

    return default_value;
}

} // namespace ngind::utils
