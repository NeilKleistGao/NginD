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

/// @file observer.h

#ifndef NGIND_OBSERVER_H
#define NGIND_OBSERVER_H

#include <unordered_map>
#include <vector>
#include <string>
#include <queue>

#include "lua_registration.h"
#include "components/state_machine.h"
#include "objects/object.h"

namespace ngind::script {

/**
 * Observer used to passing message between two object.
 */
class Observer {
public:
    /**
     * Get the observer instance.
     * @return Observer*, the observer instance
     */
    static Observer* getInstance();

    /**
     * Destroy the observer instance.
     */
    static void destroyInstance();

    /**
     * Subscribe a message.
     * @param machine: state machine who subscribes
     * @param name: name of message
     */
    void subscribe(components::StateMachine* machine, const std::string& name);

    /**
     * Notify a object randomly
     * @param sender: sender of message
     * @param name: name of message
     * @param data: data attained
     */
    inline void notify(const luabridge::LuaRef& sender, const std::string& name, const luabridge::LuaRef& data) {
        if (_blocked) {
            return;
        }
        _queue.push(MessageDataPack(name, sender, data, false));
    }

    /**
     * Notify all objects that subscribe
     * @param sender: sender of message
     * @param name: name of message
     * @param data: data attained
     */
    inline void notifyAll(const luabridge::LuaRef& sender, const std::string& name, const luabridge::LuaRef& data) {
        if (_blocked) {
            return;
        }
        _queue.push(MessageDataPack(name, sender, data, true));
    }

    /**
     * Notify sibling components that subscribe
     * @param name: name of message
     * @param object: object containing components
     * @param data: data attained
     */
    inline void notifySiblings(const std::string& name, objects::Object* object, const luabridge::LuaRef& data) {
        if (_blocked) {
            return;
        }
        _queue.push(MessageDataPack(name, object, data));
    }

    /**
     * Cancel a subscription.
     * @param machine: the subscriber
     * @param name: name of message
     */
    void cancel(components::StateMachine* machine, const std::string& name);

    /**
     * Update messages' states.
     */
    void update();

    void clear();

    inline void reset() {
        _blocked = false;
    }
private:
    Observer() : _blocked(false) {};
    ~Observer();

    /**
     * Data pack used to save message in queue.
     */
    struct MessageDataPack {
        /**
         * Message's name.
         */
        std::string name;

        /**
         * Data to be sent.
         */
        luabridge::LuaRef data;

        /**
         * Message's sender
         */
        luabridge::LuaRef sender;

        /**
         * Sender's parent object.
         */
        objects::Object* object;

        /**
         * Should I send message to all objects meeting requirements.
         */
        bool all;

        MessageDataPack();

        /**
         * @param n: name of message
         * @param s: sender of message
         * @param d: data in message
         * @param all: send to all objects.
         */
        MessageDataPack(std::string n, const luabridge::LuaRef& s, const luabridge::LuaRef& d, bool all);

        /**
         * @param n: name of message
         * @param obj: parent object
         * @param d: data in message
         */
        MessageDataPack(std::string n, objects::Object* obj, luabridge::LuaRef d);
    };

    /**
     * Instance of observer
     */
    static Observer* _instance;

    /**
     * Message queue.
     */
    std::queue<MessageDataPack> _queue;

    bool _blocked;

    /**
     * Subscription list
     */
    std::unordered_map<std::string, std::vector<components::StateMachine*>> _dependence;

    /**
     * Notify a object randomly
     * @param sender: sender of message
     * @param name: name of message
     * @param data: data attained
     */
    void notify(const luabridge::LuaRef& sender, const std::string& name, const luabridge::LuaRef& data, int);

    /**
     * Notify all objects that subscribe
     * @param sender: sender of message
     * @param name: name of message
     * @param data: data attained
     */
    void notifyAll(const luabridge::LuaRef& sender, const std::string& name, const luabridge::LuaRef& data, int);

    /**
     * Notify sibling components that subscribe
     * @param name: name of message
     * @param object: object containing components
     * @param data: data attained
     */
    void notifySiblings(const std::string& name, objects::Object* object, const luabridge::LuaRef& data, int);
};

} // namespace ngind::script

#endif //NGIND_OBSERVER_H
