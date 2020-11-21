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

/// @file render_queue.h
/// @date 2020/10/31

#ifndef NGIND_RENDER_QUEUE_H
#define NGIND_RENDER_QUEUE_H

#include "render_command.h"

#include <vector>

namespace ngind {

/**
@class A simple queue used to store the render commands.
*/
class RenderQueue {
public:
    /// @public
    RenderQueue() = default;

    /// @public
    ~RenderQueue() = default;

    /// @public
    /// @typedef Use std::vector<RenderCommand*>::iterator as queue's iterator
    using iterator = std::vector<RenderCommand*>::iterator;

    /// @public
    /// @fn Get iterator pointing the beginning of queue
    /// @param void
    /// @return iterator, beginning iterator
    inline iterator begin() {
        return _queue.begin();
    }

    /// @public
    /// @fn Get iterator pointing the end of queue
    /// @param void
    /// @return iterator, end iterator
    inline iterator end() {
        return _queue.end();
    }

    /// @public
    /// @fn Clean the queue
    /// @param void
    /// @return void
    inline void clear() {
        _queue.clear();
    }

    /// @public
    /// @fn Push a command pointer into queue
    /// @param RenderCommand* command: commmand to be pushed
    /// @return void
    inline void push(RenderCommand* command) {
        _queue.push_back(command);
    }

    /// @public
    /// @fn Sort all commands by order in z-dim
    /// @param void
    /// @return void
    void sort();

private:
    /// @private
    /// @property Vector buffer to store commands
    std::vector<RenderCommand*> _queue;
};

} // namespace

#endif //NGIND_RENDER_QUEUE_H
