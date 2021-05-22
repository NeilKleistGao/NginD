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

namespace ngind::utils {

class Archive {
public:
    static Archive* getInstance();
    static void destroyInstance();

    void setString(const std::string& key, const std::string& value);
    void setInteger(const std::string& key, int value);
    void setFloat(const std::string& key, float value);
    void setBoolean(const std::string& key, bool value);
    void dumpWorld(const std::string& name);

    std::string getString(const std::string& key);
    int getInteger(const std::string& key);
    float getFloat(const std::string& key);
    bool getBoolean(const std::string& key);
    void loadWorld(const std::string& name);
private:
    static Archive* _instance;

    rapidjson::Document _doc;
    static const std::string ARCHIVE_FILENAME;

    Archive();
    ~Archive();
};

} // namespace ngind::utils

#endif //NGIND_ARCHIVE_H
