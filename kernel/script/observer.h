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

#include "lua_registration.h"
#include "components/state_machine.h"

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
    void notify(const luabridge::LuaRef& sender, const std::string& name, luabridge::LuaRef data);

    /**
     * Notify all objects that subscribe
     * @param sender: sender of message
     * @param name: name of message
     * @param data: data attained
     */
    void notifyAll(const luabridge::LuaRef& sender, const std::string& name, luabridge::LuaRef data);

    /**
     * Cancel a subscription.
     * @param machine: the subscriber
     * @param name: name of message
     */
    void cancel(components::StateMachine* machine, const std::string& name);
private:
    Observer() = default;
    ~Observer();

    /**
     * Instance of observer
     */
    static Observer* _instance;

    /**
     * Subscription list
     */
    std::unordered_map<std::string, std::vector<components::StateMachine*>> _dependence;
};

} // namespace ngind::script

#endif //NGIND_OBSERVER_H
