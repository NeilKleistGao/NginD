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

//#define NGIND_CLASS_INFO_TEST
#ifdef NGIND_CLASS_INFO_TEST

#include <iostream>

#include "rttr/type"
#include "rttr/registration.h"

class Foo {
public:
    Foo() {
        std::cout << "rua" << std::endl;
    }

    ~Foo() {
        std::cout << "1551" << std::endl;
    }

    void bar() {
        std::cout << "foo" << std::endl;
    }

private:
    int _foo;
};

RTTR_REGISTRATION {
    rttr::registration::class_<Foo>("Foo").constructor<>().method("bar", &Foo::bar);
}

int main() {
    rttr::type type = rttr::type::get_by_name("Foo");
    rttr::variant variant = type.create();
    Foo foo = variant.get_value<Foo>();
    foo.bar();

    rttr::instance ins = foo;
    return 0;
}

#endif // NGIND_CLASS_INFO_TEST