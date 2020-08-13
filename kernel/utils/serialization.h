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
// LAST MODIFY: 2020/8/13
// FILENAME: serialization.h

#ifndef NGIND_SERIALIZATION_H
#define NGIND_SERIALIZATION_H

#include <iostream>
#include <sstream>
#include <type_traits>

namespace ngind {

// @interface
class Serializable {
public:
    virtual void serialize(std::ostream&) const = 0;
    virtual void deserialize(std::istream&) = 0;
};

template <typename Type,
        typename std::enable_if_t<std::is_trivially_copyable_v<Type>, int> N = 0>
void serialize(const Type& content, std::ostream& stream) {
    stream.write(reinterpret_cast<const char*>(&content), sizeof(Type));
}

template <typename Type,
        typename std::enable_if_t<std::is_trivially_copyable_v<Type>, int> N = 0>
void deserialize(Type& content, std::istream& stream) {
    stream.read(reinterpret_cast<char*>(&content), sizeof(Type));
}

template <typename Type,
        typename std::enable_if_t<std::is_same_v<typename Type::iterator, decltype(std::declval<Type>().begin())> &&
        std::is_same_v<typename Type::iterator, decltype(std::declval<Type>().end())> &&
        std::is_trivially_copyable_v<typename Type::value_type>, int> N = 0>
void serialize(const Type& content, std::ostream& stream) {
    size_t size = content.size();
    stream.write(reinterpret_cast<const char*>(&size), sizeof(size_t));
    stream.write(reinterpret_cast<const char*>(content.data()), size * sizeof(typename Type::value_type));
}

template <typename Type,
        typename std::enable_if_t<std::is_same_v<typename Type::iterator, decltype(std::declval<Type>().begin())> &&
                                  std::is_same_v<typename Type::iterator, decltype(std::declval<Type>().end())> &&
                                  std::is_trivially_copyable_v<typename Type::value_type>, int> N = 0>
void deserialize(Type& content, std::istream& stream) {
    size_t size;
    stream.read(reinterpret_cast<char*>(&size), sizeof(size_t));
    content.resize(size);
    stream.read(reinterpret_cast<char*>(content.data()), size * sizeof(typename Type::value_type));
}

template <typename Type,
        typename std::enable_if_t<std::is_base_of_v<Serializable, Type>, int> N = 0>
void serialize(const Type& content, std::ostream& stream) {
    content.serialize(stream);
}

template <typename Type,
        typename std::enable_if_t<std::is_base_of_v<Serializable, Type>, int> N = 0>
void deserialize(Type& content, std::istream& stream) {
    content.deserialize(stream);
}

template <typename Type,
        typename std::enable_if_t<std::is_same_v<typename Type::iterator, decltype(std::declval<Type>().begin())> &&
                                  std::is_same_v<typename Type::iterator, decltype(std::declval<Type>().end())> &&
                                  !std::is_trivially_copyable_v<typename Type::value_type>, int> N = 0>
void serialize(const Type& content, std::ostream& stream) {
    size_t size = content.size();
    stream.write(reinterpret_cast<const char*>(&size), sizeof(size_t));
    for (const auto& item : content) {
        serialize(item, stream);
    }
}

    template <typename Type,
            typename std::enable_if_t<std::is_same_v<typename Type::iterator, decltype(std::declval<Type>().begin())> &&
                                      std::is_same_v<typename Type::iterator, decltype(std::declval<Type>().end())> &&
                                      !std::is_trivially_copyable_v<typename Type::value_type>, int> N = 0>
void deserialize(Type& content, std::istream& stream) {
    size_t size;
    stream.read(reinterpret_cast<char*>(&size), sizeof(size_t));
    content.resize(size);
    auto pointer = content.data();

    for (int i = 0; i < size; i++) {
        auto item = typename Type::value_type();
        deserialize(item, stream);
        pointer[i] = item;
    }
}

} // namespace ngind

#endif //NGIND_SERIALIZATION_H
