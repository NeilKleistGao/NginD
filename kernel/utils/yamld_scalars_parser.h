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
// FILENAME: yamld_scalars_parser.h

#ifndef NGIND_YAMLD_SCALARS_PARSER_H
#define NGIND_YAMLD_SCALARS_PARSER_H

#include <iostream>

namespace NginD {
namespace yamld {

bool parseYAMLDBool(const std::string&, const bool& default_val = false);
int parseYAMLDInt(const std::string&, const int& default_val = 0);
float parseYAMLDFloat(const std::string&, const float& default_val = 0.0f);
std::string parseYAMLDString(const std::string&, const std::string& default_val = "");


} // namespace yamld
} // namespace NginD

#endif //NGIND_YAMLD_SCALARS_PARSER_H
