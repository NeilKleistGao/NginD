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
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//        AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// LAST MODIFY: 2020/8/14
// FILENAME: class_info_test.cc

#ifdef NGIND_CLASS_INFO_TEST

#include "class_info.h"
#include <iostream>
#include "object.h"

class Foo : public ngind::Object {
public:
    Foo() {
        std::cout << "rua" << std::endl;
    }

    ~Foo() {
        std::cout << "1551" << std::endl;
    }
};

int main() {
    ngind::ClassInfo::getInstance()->create<Foo>("Foo");
    ngind::ClassInfo::getInstance()->sign("bar", []() -> ngind::Object* {return new Foo();});
    ngind::ClassInfo::getInstance()->create("bar");
    ngind::ClassInfo::destroyInstance();
    return 0;
}

#endif // NGIND_CLASS_INFO_TEST