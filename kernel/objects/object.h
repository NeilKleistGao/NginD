/** MIT License
Copyright (c) 2020 NeilKleistGao
    Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
// LAST MODIFY: 2020/10/31
// FILENAME: object.h

#ifndef NGIND_OBJECT_H
#define NGIND_OBJECT_H

#include <map>
#include <iostream>

#include "kernel/utils/serialization.h"
#include "memory/auto_collection_object.h"
#include "updatable_object.h"
#include "components/component.h"

namespace ngind {

class Object : public Serializable, public AutoCollectionObject, public UpdatableObject {
public:
    Object();
    ~Object() override;

    void serialize(std::ostream&) const override;
    void deserialize(std::istream&) override;

    void addChild(const std::string&, Object*);
    void removeChild(const std::string&);
    Object* getChildByName(const std::string&);

    inline void setParent(Object* object) {
        this->_parent = object;
    }

    inline Object* getParent() {
        return this->_parent;
    }

    virtual void update(const float&);

    virtual inline void addComponent(const std::string& name, Component* component) {
        if (_components.find(name) == _components.end()) {
            _components[name] = component;
            component->setParent(this);
        }
    }

    template<typename Type, typename std::enable_if_t<std::is_base_of_v<Component, Type>> N = 0>
    Type* getComponent(const std::string& name) {
        if (_components.find(name) == _components.end()) {
            return nullptr;
        }

        return static_cast<Type>(_components[name]);
    }

    template<typename Type, typename std::enable_if_t<std::is_base_of_v<Component, Type>> N = 0>
    void removeComponent(const std::string& name) {
        if (_components.find(name) == _components.end()) {
            return;
        }

        auto p = static_cast<Type>(_components[name]);
        delete p;
        p = _components[name] = nullptr;
        _components.erase(name);
    }

protected:
    std::map<std::string, Object*> _children;
    std::map<std::string, Component*> _components;
    Object* _parent;
};
} // namespace ngind



#endif //NGIND_OBJECT_H
