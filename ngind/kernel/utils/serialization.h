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

// FILENAME: serialization.h
// LAST MODIFY: 2020/8/16

#ifndef NGIND_SERIALIZATION_H
#define NGIND_SERIALIZATION_H

// All serialization methods here
// Use these methods if the object to be serialized is a POD or std container
// Or you need to implement the Serializable interface and serialize method

#include <iostream>
#include <sstream>
#include <type_traits>

namespace ngind {

class Serializable {
public:
    virtual void serialize(std::ostream&) const = 0;
    virtual void deserialize(std::istream&) = 0;
};

} // namespace ngind

#endif //NGIND_SERIALIZATION_H
