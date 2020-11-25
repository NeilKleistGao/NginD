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

/// @file coroutine.h
/// @date 2020/9/27

/**
@brief
    This file includes the declaration and implement of coroutine class. There is
only one class with 3 specialization classes.
*/


#ifndef NGIND_COROUTINE_H
#define NGIND_COROUTINE_H

#include <functional>
#include <boost/fiber/all.hpp>
#include <utility>

namespace ngind {

/**
@class
 Coroutine class based on boost fiber.
@tparam Type: the type of return value
@tparam Param: the type list of function's params
*/
template <typename Type, typename ... Param>
class Coroutine {
public:
    /// @public
    /// @typedef The type for coroutine task
    using task = std::function<Type(Param ...)>;
    /// @public
    /// @typedef The type of call back function that will be called when the main task finished
    using callback = std::function<void(Type)>;

    /// @public
    /// @param task task_func: main task function
    explicit Coroutine(task task_func) : Coroutine(task_func, nullptr) {
    }

    /// @public
    /// @param task task_func: main task function
    /// @param callback callback_func: callback function
    Coroutine(task task_func, callback callback_func) : _process(task_func), _callback(callback_func) {
    }

    /// @public
    /// @fn Start this coroutine and execute the function
    /// @param Param ... param: the params of main function
    /// @return void
    void run(Param ... param) {
        if (this->_callback == nullptr) { // if this coroutine doesn't have a callback function
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

    /// @public
    /// @fn Wait for this coroutine's end.
    /// @param void
    /// @return void
    void wait() {
        if (this->isRunning()) {
            _fiber.join();
        }
    }

    /// @public
    /// @fn Get the state of this coroutine.
    /// @param void
    /// @return bool, whether this coroutine is running or not
    inline bool isRunning() {
        return _fiber.joinable();
    }

private:
    /// @private
    /// @property The real fiber object
    boost::fibers::fiber _fiber;
    /// @private
    /// @property The main task function
    task _process;
    /// @private
    /// @property The callback function
    callback _callback;
};

/**
@class
    A specialization for functions that don't have a return value.
@see:
    template <typename Type, typename ... Param> class Coroutine
*/
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

/**
@class
    A specialization for functions that don't have params.
@see:
    template <typename Type, typename ... Param> class Coroutine
*/
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

/**
@class
    A specialization for functions that don't have a return value or params.
@see:
    template <typename Type, typename ... Param> class Coroutine
*/
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
