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

/// @file visual_logger.h

#ifndef NGIND_VISUAL_LOGGER_H
#define NGIND_VISUAL_LOGGER_H

#include <map>

#include "objects/entity_object.h"
#include "components/label.h"
#include "utils/converter.h"

namespace ngind::log {

class VisualLogger {
public:
    static VisualLogger* getInstance();
    static void destroyInstance();

    void enable();
    inline void disable() {
        _enable = false;
    }

    void draw();

    void registerVariable(const std::string& key, const std::string default_value = "");

    template<typename T>
    void updateVariable(const std::string& key, const T& value) {
        if (_var.find(key) != _var.end()) {
            _var[key] = std::to_string(value);
        }
    }

    void resignVariable(const std::string& key);
private:
    VisualLogger();
    ~VisualLogger();

    static VisualLogger* _instance;

    bool _enable;
    std::map<std::string, std::string> _var;

    objects::EntityObject* _entity;
    components::Label* _label;

    std::string _text;
};

} // namespace ningd::log

#endif //NGIND_VISUAL_LOGGER_H
