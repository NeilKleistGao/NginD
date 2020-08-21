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
// LAST MODIFY: 2020/8/21
// FILENAME: ini_config.cc

#include "ini_config.h"

#include <cstdio>

#include "file_utils.h"
#include "resources_settings.h"

namespace ngind {

INIConfig::INIConfig() {

}

INIConfig::INIConfig(const std::string& filename) : INIConfig() {
    this->open(filename);
}

INIConfig::~INIConfig() {
    this->clear();
}

std::string INIConfig::get(const std::string& section, const std::string& key) {
    std::string res = "";
    if (this->_content.find(section) != this->_content.end()) {
        if (this->_content[section].find(key) != this->_content[section].end()) {
            res = this->_content[section][key];
        }
    }

    return res;
}

void INIConfig::set(const std::string& section, const std::string& key, const std::string& value) {
    if (this->_content.find(section) == this->_content.end()) {
        return;
    }

    this->_content[section][key] = value;
}

void INIConfig::open(const std::string& filename) {
    this->_filename = file_utils::joinPath(settings::CONFIG_RESOURCES_PATH, filename);
    FILE* fp = fopen(this->_filename.c_str(), "r");

    if (fp == nullptr) {
        return;
    }

    const size_t BUFF_SIZE = 256;
    char buff[BUFF_SIZE];
    std::string section_name = "";

    while (!feof(fp)) {
        fgets(buff, BUFF_SIZE - 1, fp);
        std::string str = buff;
        str = str.substr(0, str.length() - 1);

        if ((*str.begin()) == '[' && (*str.rbegin()) == ']') {
            section_name = str.substr(1, str.length() - 2);
            this->_content[section_name] = section();
        }
        else {
            int pos = str.find('=');
            if (pos == -1) {
                continue;
            }

            this->_content[section_name][str.substr(0, pos)] = str.substr(pos + 1);
        }
    }

    fclose(fp);
}

void INIConfig::save() {
    FILE * fp = fopen(this->_filename.c_str(), "w");
    if (fp == nullptr) {
        return;
    }

    for (const auto& sec : this->_content) {
        fprintf(fp, "[%s]\n", sec.first.c_str());
        for (const auto& pair : sec.second) {
            fprintf(fp, "%s=%s\n", pair.first.c_str(), pair.second.c_str());
        }
    }

    fclose(fp);
}

void INIConfig::clear() {
    for (auto& sec : this->_content) {
        sec.second.clear();
    }

    this->_content.clear();
}

} // namespace

