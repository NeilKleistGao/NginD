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
// FILENAME: render_queue.h
// LAST MODIFY: 2020/10/26

#ifndef NGIND_RENDER_QUEUE_H
#define NGIND_RENDER_QUEUE_H

#include <vector>

#include "render_command.h"

namespace ngind {

class RenderQueue {
public:
    RenderQueue() = default;
    ~RenderQueue() = default;

    using iterator = std::vector<RenderCommand>::iterator;

    inline iterator begin() {
        return _queue.begin();
    }

    inline iterator end() {
        return _queue.end();
    }

    inline void clear() {
        _queue.clear();
    }

private:
    std::vector<RenderCommand> _queue;
};

} // namespace

#endif //NGIND_RENDER_QUEUE_H