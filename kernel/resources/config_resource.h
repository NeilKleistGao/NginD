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

/// @file config_resource.h

#ifndef NGIND_CONFIG_RESOURCE_H
#define NGIND_CONFIG_RESOURCE_H

#include "resource.h"

#include "include/rapidjson/document.h"

namespace ngind::resources {

/**
 * Resource class containing configure data.
 */
class ConfigResource : public Resource {
public:
    /**
     * Path all configure files stored
     */
    const static std::string CONFIG_RESOURCE_PATH;

    ConfigResource() : Resource() {};
    ~ConfigResource() override = default;

    /**
     * @see kernel/resources/resource.h
     */
    virtual void load(const std::string&);

    using JsonObject = rapidjson::GenericValue<rapidjson::UTF8<>>;

    /**
     * Get JSON document object.
     * @return
     */
    inline rapidjson::Document& getDocument() {
        return _doc;
    }
private:
    /**
     * JSON document object
     */
    rapidjson::Document _doc;
};

} // namespace ngind::resources

#endif //NGIND_CONFIG_RESOURCE_H
