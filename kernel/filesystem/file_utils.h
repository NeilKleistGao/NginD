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
// LAST MODIFY: 2020/10/1
// FILENAME: file_util.h

#ifndef NGIND_FILE_UTILS_H
#define NGIND_FILE_UTILS_H

#include <iostream>

namespace ngind {
const char PATH_SEPARATOR = '/'; // TODO: mul-env

const std::string STDIN_PATH = "__STDIN__";
const std::string STDOUT_PATH = "__STDOUT__";
const std::string STDERR_PATH = "__STDERR__";

// image resources path
const std::string IMAGE_RESOURCES_PATH = "./resources/images";

// config resources path
const std::string CONFIG_RESOURCES_PATH = "./resources/config";

std::string joinPath(const std::string&, const std::string&);
} // namespace ngind

#endif //NGIND_FILE_UTILS_H
