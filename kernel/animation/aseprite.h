/**
 * @copybrief
 * MIT License
 * Copyright (c) 2020 NeilKleistGao
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/// @file aseprite.h

#ifndef NGIND_ASEPRITE_H
#define NGIND_ASEPRITE_H

#include <vector>
#include <string>

#include "aseprite_frame.h"
#include "aseprite_tag.h"

namespace ngind::animation {

class Aseprite {
public:
    explicit Aseprite(const std::string& name);
    ~Aseprite();
    Aseprite(const Aseprite&) = delete;
    Aseprite& operator= (const Aseprite&) = delete;

    inline std::string getFilename() const {
        return _image_path;
    }

    AsepriteFrame play(const std::string& name);
    AsepriteFrame next();

    bool isEnd() const;

private:
    std::string _image_path;
    std::vector<AsepriteFrame> _frames;
    std::vector<AsepriteTag> _tags;

    AsepriteTag* _current_tag;
    unsigned int _current_index;

    resources::ConfigResource* _config;
};

} // namespace ngind::animation

#endif //NGIND_ASEPRITE_H
