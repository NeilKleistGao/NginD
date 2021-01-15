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

/// @file component_factory.h

#ifndef NGIND_COMPONENT_FACTORY_H
#define NGIND_COMPONENT_FACTORY_H

#include <map>
#include <functional>

#include "component.h"
#include "resources/config_resource.h"

namespace ngind::components {

/**
 * Factory class that worlds use to create components.
 */
class ComponentFactory {
public:
    /**
     * Get the unique instance of component factory.
     * @return ComponentFactory*, The unique instance
     */
    static ComponentFactory* getInstance();

    /**
     * Destroy the instance of component factory.
     */
    static void destroyInstance();

    /**
     * Register a component to factory.
     * @tparam T: Type of component
     * @param name: Name of component
     */
    template<typename T>
    void registerComponent(const std::string& name) {
        _map[name] = [](const typename resources::ConfigResource::JsonObject& data) -> Component* {
            return T::create(data);
        };
    }

    /**
     * Create an instance of component bu given name.
     * @param name: name of component
     * @param data: data the creation needs
     * @return Component*, the component created
     */
    Component* create(const std::string& name, const typename resources::ConfigResource::JsonObject& data);

private:
    ComponentFactory() = default;
    ~ComponentFactory() = default;

    /**
     * The unique instance
     */
    static ComponentFactory* _instance;

    /**
     * Mapping from component name to component creation function
     */
    std::map<std::string, std::function<Component*(const typename resources::ConfigResource::JsonObject&)>> _map;
};

} // namespace ngind::components

#endif //NGIND_COMPONENT_FACTORY_H
