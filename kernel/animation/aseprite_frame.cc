/** MIT License
 * Copyright (c) 2020 NeilKleistGao
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/// @file aseprite_frame.cc

#include "aseprite_frame.h"

namespace ngind::animation {

AsepriteFrame::AsepriteFrame(const typename resources::ConfigResource::JsonObject& data)
: _trimmed(false), _rect(), _position(), _original_size(), _duration() {
    auto rect = data["frame"].GetObject();
    _rect.x = rect["x"].GetInt(); _rect.y = rect["y"].GetInt(); _rect.z = rect["w"].GetInt(); _rect.w = rect["h"].GetInt();

    _trimmed = data["trimmed"].GetBool();

    auto pos = data["spriteSourceSize"].GetObject();
    _position.x = pos["x"].GetInt(); _position.y = pos["y"].GetInt();

    auto size = data["sourceSize"].GetObject();
    _original_size.x = size["x"].GetInt(); _original_size.y = size["y"].GetInt();

    _duration = std::chrono::milliseconds{data["duration"].GetInt64()};
}

} // namespace ngind::animation
