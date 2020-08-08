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
// FILENAME: yamld_scalars_parser.cc

#include "yamld_scalars_parser.h"

#include <cctype>

namespace NginD {
namespace yamld {

bool parseYAMLDBool(const std::string& val, const bool& default_val) {
    std::string lower_val;
    for (const auto& c : val) {
        lower_val += std::tolower(c);
    }

    bool flag = default_val;
    if (lower_val == "true") {
        flag = true;
    }
    else if (lower_val == "false") {
        flag = false;
    }

    return flag;
}

int parseYAMLDInt(const std::string& val, const int& default_val) {
    int num = 0, flag = 1;
    for (const auto& c : val) {
        if (c == '-' && num == 0 && flag == 1) {
            flag = -1;
        }
        else if (std::isdigit(c)) {
            num *= 10;
            num += (c - '0');
        }
        else {
            num = default_val;
            break;
        }
    }

    return num * flag;
}

float parseYAMLDFloat(const std::string& val, const float& default_val) {
    float num = 0.0f, multiple = 10.0f;
    int flag = 1;

    for (const auto& c : val) {
        if (c == '-' && num == 0.0 && flag == 1) {
            flag = -1;
        }
        else if (c == '.') {
            multiple = 0.1f;
        }
        else if (std::isdigit(c)) {
            if (multiple > 1.0f) {
                num *= multiple;
                num += (c - '0');
            }
            else {
                float temp = (c - '0') * multiple;
                num += temp;
                multiple *= 0.1;
            }
        }
        else {
            num = default_val;
            break;
        }
    }

    return num * flag;
}

std::string parseYAMLDString(const std::string& val, const std::string& default_val) {
    char begin = *val.begin(), end = *val.rbegin();
    if (val.size() >= 2 && ((begin == '"' && end == '"') || (begin == '\'' && end == '\''))) {
        return val.substr(1, val.length() - 2);
    }
    else {
        return default_val;
    }
}

}
} // namespace NginD