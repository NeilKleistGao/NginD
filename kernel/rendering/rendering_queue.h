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

/// @file render_queue.h

#ifndef NGIND_RENDERING_QUEUE_H
#define NGIND_RENDERING_QUEUE_H

#include "render_command.h"

#include <vector>

namespace ngind::rendering {

/**
 * A simple queue used to store the rendering commands.
 */
class RenderingQueue {
public:
    RenderingQueue() = default;
    ~RenderingQueue() = default;

    using iterator = std::vector<RenderCommand*>::iterator;

    /**
     * Get iterator pointing the beginning of queue
     * @return iterator, beginning iterator
     */
    inline iterator begin() {
        return _queue.begin();
    }

    /**
     * Get iterator pointing the end of queue
     * @return iterator, end iterator
     */
    inline iterator end() {
        return _queue.end();
    }

    /**
     * Clean the queue
     */
    inline void clear() {
        _queue.clear();
    }

    /**
     * Push a command pointer into queue
     * @param command: command to be pushed
     */
    inline void push(RenderCommand* command) {
        _queue.push_back(command);
    }

    /**
     * Sort all commands by order in z-dim
     */
    void sort();

private:
    /**
     * Vector buffer to store commands
     */
    std::vector<RenderCommand*> _queue;
};

} // namespace ngind::rendering

#endif //NGIND_RENDERING_QUEUE_H
