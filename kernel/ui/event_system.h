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

/// @file event_system.h

#ifndef NGIND_EVENT_SYSTEM_H
#define NGIND_EVENT_SYSTEM_H

#include "clickable_receiver.h"
#include "quad_tree.h"

namespace ngind::ui {

class EventSystem {
public:
    static EventSystem* getInstance();
    static void destroyInstance();

    EventSystem(const EventSystem&) = delete;
    EventSystem& operator= (const EventSystem&) = delete;

    void registerEvent(const ClickableReceiver& receiver);
    void unregisterEvent(const ClickableReceiver& receiver);

    void update();

    inline void init(const size_t& win_height) {
        _win_height = win_height;
    }
    void init(const size_t& width, const size_t& height);
private:
    EventSystem();
    ~EventSystem();

    static EventSystem* _instance;
    QuadTree* _tree;
    size_t _win_height;
    ClickableReceiver* _current_receiver;
    ClickableReceiver* _current_moving;
};

} // namespace ngind::ui

#endif //NGIND_EVENT_SYSTEM_H
