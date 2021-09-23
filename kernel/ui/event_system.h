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
#include "kd_tree.h"

namespace ngind::ui {

/**
 * Singleton class dealing with ui events.
 */
class EventSystem {
public:
    /**
     * Get instance of EventSystem. Create if instance is null.
     * @return EventSystem*, the unique instance
     */
    static EventSystem* getInstance();

    /**
     * Destroy the unique instance of EventSystem.
     */
    static void destroyInstance();

    EventSystem(const EventSystem&) = delete;
    EventSystem& operator= (const EventSystem&) = delete;

    /**
     * Register a new click event.
     * @param receiver: clickable area data
     */
    inline void registerEvent(const ClickableReceiver& receiver) {
        _tree->insert(receiver);
    }

    /**
     * Unregister some click event.
     * @param receiver: clickable area data
     */
    inline void unregisterEvent(const ClickableReceiver& receiver) {
        _tree->erase(receiver);
    }

    /**
     * Update events' states each frame.
     */
    void update();

    /**
     * Initialize the window's height.
     * @param win_height: window's height
     */
    inline void init(const size_t& win_height) {
        _win_height = win_height;
    }

    /**
     * Initialize or reinitialize quad tree with world's size.
     * @param width: world's width
     * @param height: world's height
     */
    void init();
private:
    EventSystem();
    ~EventSystem();


    /**
     * The unique instance of EventSystem.
     */
    static EventSystem* _instance;

    /**
     * Quad tree maintaining receiver data.
     */
    KDTree* _tree;

    /**
     * Window's height.
     */
    size_t _win_height;

    /**
     * Clickable receiver on processing of click.
     */
    ClickableReceiver* _current_receiver;

    /**
     * Clickable receiver on processing of moving.
     */
    ClickableReceiver* _current_moving;
};

} // namespace ngind::ui

#endif //NGIND_EVENT_SYSTEM_H
