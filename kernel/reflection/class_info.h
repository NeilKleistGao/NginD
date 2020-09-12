// MIT License
//
// Copyright (c) 2020 NeilKleistGao
//
//        Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
//        to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//        copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
//        copies or substantial portions of the Software.
//
// THE SOFTWARsE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//        AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// LAST MODIFY: 2020/8/16
// FILENAME: class_info.h

#ifndef NGIND_CLASS_INFO_H
#define NGIND_CLASS_INFO_H

#include <iostream>
#include <map>
#include <functional>
#include <memory>

#include "object.h"

namespace ngind {

// The reflection supporter class
// If you use reflection comment, cmake will help you sign your class
// This class is a singleton class

class ClassInfo {
public:
    static ClassInfo* getInstance();
    static void destroyInstance();

    void sign(const std::string&, std::function<Object*(void)>&&);

    template <typename Type>
    std::shared_ptr<Type> create(const std::string& class_name) {
        if (this->_map.find(class_name) == this->_map.end()) {
            this->sign(class_name, []() -> Object* {return static_cast<Object*>(new Type());});
        }

        Object* original_pointer = this->_map[class_name]();
        std::shared_ptr<Type> pointer((Type*)(original_pointer));
        return pointer;
    }

    std::shared_ptr<Object> create(const std::string&);

private:
    static ClassInfo* _instance;
    std::map<std::string, std::function<Object*(void)>> _map;

    ClassInfo();
    ~ClassInfo();
};

} // namespace ngind

#endif //NGIND_CLASS_INFO_H
