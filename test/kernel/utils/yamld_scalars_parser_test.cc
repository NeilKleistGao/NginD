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
// LAST MODIFY: 2020/8/8
// FILENAME: yamld_scalars_parser_test.cc

// #define YAMLD_SCALARS_PARSER_TEST
#ifdef YAMLD_SCALARS_PARSER_TEST

#include "yamld_scalars_parser.h"

#include <cassert>
#include <cmath>

static constexpr float epsilon = 1e-5;

static bool checkFloat(const float& x, const float& y) {
    return std::abs(x - y) <= epsilon;
}

int main() {
    assert(NginD::yamld::parseYAMLDBool("true") == true);
    assert(NginD::yamld::parseYAMLDBool("false") == false);
    assert(NginD::yamld::parseYAMLDBool("True") == true);
    assert(NginD::yamld::parseYAMLDBool("False") == false);
    assert(NginD::yamld::parseYAMLDBool("TRUE") == true);
    assert(NginD::yamld::parseYAMLDBool("FALSE") == false);
    assert(NginD::yamld::parseYAMLDBool("foo", true) == true);

    assert(NginD::yamld::parseYAMLDInt("123") == 123);
    assert(NginD::yamld::parseYAMLDInt("-123") == -123);
    assert(NginD::yamld::parseYAMLDInt("0") == 0);
    assert(NginD::yamld::parseYAMLDInt("-0") == 0);
    assert(NginD::yamld::parseYAMLDInt("123.4") == 0);
    assert(NginD::yamld::parseYAMLDInt("1e5", 1) == 1);

    assert(checkFloat(NginD::yamld::parseYAMLDFloat("12.3"), 12.3f));
    assert(checkFloat(NginD::yamld::parseYAMLDFloat("-12.3"), -12.3f));
    assert(checkFloat(NginD::yamld::parseYAMLDFloat("15"), 15.0f));
    assert(checkFloat(NginD::yamld::parseYAMLDFloat("-12"), -12.0f));
    assert(checkFloat(NginD::yamld::parseYAMLDFloat("foo", epsilon), epsilon));

    assert(NginD::yamld::parseYAMLDString("'abc'") == "abc");
    assert(NginD::yamld::parseYAMLDString("\"abc\"") == "abc");
    assert(NginD::yamld::parseYAMLDString("''") == "");
    assert(NginD::yamld::parseYAMLDString("\"\"") == "");
    assert(NginD::yamld::parseYAMLDString("'abc") == "");
    assert(NginD::yamld::parseYAMLDString("\"abc", "dd") == "dd");
    assert(NginD::yamld::parseYAMLDString("'abc\"") == "");
    assert(NginD::yamld::parseYAMLDString("\"abc'") == "");
    assert(NginD::yamld::parseYAMLDString("abc'") == "");
    assert(NginD::yamld::parseYAMLDString("abc\"") == "");
    assert(NginD::yamld::parseYAMLDString("123") == "");
    assert(NginD::yamld::parseYAMLDString("'") == "");
    assert(NginD::yamld::parseYAMLDString("\"") == "");

    return 0;
}

#endif // YAMLD_SCALARS_PARSER_TEST