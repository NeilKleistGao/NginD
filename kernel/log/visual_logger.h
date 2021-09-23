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

namespace ngind::log {

/**
 * Display information on the screen during debug.
 * It's still not available for lua.
 */
class VisualLogger {
public:
    /**
     * Get the unique instance of class. If it does not exist, this function will create one.
     * @return VisualLogger*, the unique instance
     */
    static VisualLogger* getInstance();

    /**
     * Destroy the instance if it exists.
     */
    static void destroyInstance();

    /**
     * Enable the logger.
     */
    void enable();

    /**
     * Disable the logger.
     */
    inline void disable() {
        _enable = false;
    }

    /**
     * Update data on the screen per frame.
     */
    void draw();

    /**
     * Register a new variable to the logger.
     * @param key: name of the variable
     * @param default_value: default value.
     */
    void registerVariable(const std::string& key, const std::string& default_value = "");

    /**
     * Update variable's value in the logger.
     * @tparam T: type of the variable
     * @param key: name of the variable
     * @param value: variable's value
     */
    template<typename T>
    void updateVariable(const std::string& key, const T& value) {
        if (_var.find(key) != _var.end()) {
            _var[key] = std::to_string(value);
        }
    }

    /**
     * Remove a variable from the logger.
     * @param key: name of the variable
     */
    void resignVariable(const std::string& key);
private:
    VisualLogger();
    ~VisualLogger();

    /**
     * The unique instance.
     */
    static VisualLogger* _instance;

    /**
     * Is logger enabled.
     */
    bool _enable;

    /**
     * Variables table.
     */
    std::map<std::string, std::string> _var;

    /**
     * Entity of label component.
     */
    objects::EntityObject* _entity;

    /**
     * Label component for displaying information.
     */
    components::Label* _label;

    /**
     * Text to be display.
     */
    std::string _text;
};

} // namespace ningd::log

#endif //NGIND_VISUAL_LOGGER_H
