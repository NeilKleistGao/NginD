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
// FILENAME: coroutine.h
// LAST MODIFY: 2020/9/27

#ifndef NGIND_COROUTINE_H
#define NGIND_COROUTINE_H

#include <functional>
#include <boost/fiber/all.hpp>
#include <utility>

namespace ngind {
template <typename Type, typename ... Param>
class Coroutine {
public:
    using task = std::function<Type(Param ...)>;
    using callback = std::function<void(Type)>;

    explicit Coroutine(task task_func) : Coroutine(task_func, nullptr) {
    }

    Coroutine(task task_func, callback callback_func) : _process(task_func), _callback(callback_func) {
    }

    void run(Param ... param) {
        if (this->_callback == nullptr) {
            _fiber = boost::fibers::fiber(boost::fibers::launch::dispatch, _process, param...);
        }
        else {
            task temp_task = this->_process;
            callback temp_callback = this->_callback;
            _fiber = boost::fibers::fiber(boost::fibers::launch::dispatch, [&]() {
                temp_callback(temp_task(param...));
            });
        }
        _fiber.detach();
    }

    void wait() {
        if (this->isRunning()) {
            _fiber.join();
        }
    }

    inline bool isRunning() {
        return _fiber.joinable();
    }

private:
    boost::fibers::fiber _fiber;
    task _process;
    callback _callback;
};

template <typename ... Param>
class Coroutine<void, Param...> {
public:
    using task = std::function<void(Param ...)>;
    using callback = std::function<void(void)>;

    explicit Coroutine(task task_func) : Coroutine(task_func, nullptr) {
    }

    Coroutine(task task_func, callback callback_func) : _process(task_func), _callback(std::move(callback_func)) {
    }

    void run(Param ... param) {
        if (this->_callback == nullptr) {
            _fiber = boost::fibers::fiber(boost::fibers::launch::dispatch, _process, param...);
        }
        else {
            task temp_task = this->_process;
            callback temp_callback = this->_callback;
            _fiber = boost::fibers::fiber(boost::fibers::launch::dispatch, [&]() {
                temp_task(param...);
                temp_callback();
            });
        }
        _fiber.detach();
    }

    void wait() {
        if (this->isRunning()) {
            _fiber.join();
        }
    }

    inline bool isRunning() {
        return _fiber.joinable();
    }

private:
    boost::fibers::fiber _fiber;
    task _process;
    callback _callback;
};

template <typename Type>
class Coroutine<Type, void> {
public:
    using task = std::function<Type(void)>;
    using callback = std::function<void(const Type&)>;

    explicit Coroutine(task task_func) : Coroutine(task_func, nullptr) {
    }

    Coroutine(task task_func, callback callback_func) : _process(task_func), _callback(callback_func) {
    }

    void run() {
        if (this->_callback == nullptr) {
            _fiber = boost::fibers::fiber(boost::fibers::launch::dispatch, _process);
        }
        else {
            task temp_task = this->_process;
            callback temp_callback = this->_callback;
            _fiber = boost::fibers::fiber(boost::fibers::launch::dispatch, [&temp_task, &temp_callback]() {
                temp_callback(temp_task());
            });
        }
        _fiber.detach();
    }

    void wait() {
        if (this->isRunning()) {
            _fiber.join();
        }
    }

    inline bool isRunning() {
        return _fiber.joinable();
    }

private:
    boost::fibers::fiber _fiber;
    task _process;
    callback _callback;
};

template <>
class Coroutine<void, void>
{
public:
    using task = std::function<void(void)>;
    using callback = std::function<void(void)>;

    explicit Coroutine(task task_func) : Coroutine(task_func, nullptr) {
    }

    Coroutine(task task_func, callback callback_func) : _process(task_func), _callback(callback_func) {
    }

    void run() {
        if (this->_callback == nullptr) {
            _fiber = boost::fibers::fiber(boost::fibers::launch::dispatch, _process);
        }
        else {
            task temp_task = this->_process;
            callback temp_callback = this->_callback;
            _fiber = boost::fibers::fiber(boost::fibers::launch::dispatch, [&temp_task, &temp_callback]() {
                temp_task();
                temp_callback();
            });
        }
        _fiber.detach();
    }

    void wait() {
        if (this->isRunning()) {
            _fiber.join();
        }
    }

    inline bool isRunning() {
        return _fiber.joinable();
    }
private:
    boost::fibers::fiber _fiber;
    task _process;
    callback _callback;
};
} // namespace ngind

#endif //NGIND_COROUTINE_H
