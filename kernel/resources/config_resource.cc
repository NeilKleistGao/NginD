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

/// @file config_resource.cc

#include "config_resource.h"

#include "filesystem/file_input_stream.h"
#include "filesystem/cipher_input_stream.h"
#include "settings.h"

namespace ngind::resources {
const std::string ConfigResource::CONFIG_RESOURCE_PATH = "resources/config";

void ConfigResource::load(const std::string& filename) {
    std::string content;
    if constexpr (CURRENT_MODE == MODE_RELEASE) {
        std::string temp = filename;
        temp.replace(filename.length() - 4, filename.length(), "cson");
        auto stream = new filesystem::CipherInputStream(new filesystem::FileInputStream(CONFIG_RESOURCE_PATH + "/" + temp));
        content = stream->readAllCharacters();
        stream->close();
    }
    else {
        auto stream = new filesystem::FileInputStream(CONFIG_RESOURCE_PATH + "/" + filename);
        content = stream->readAllCharacters();
        stream->close();
    }

    _doc.Parse(content.c_str());
    this->_path = filename;
}
} // namespace ngind