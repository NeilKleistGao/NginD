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
// FILENAME: timer.h
// LAST MODIFY: 2020/10/16

#ifndef NGIND_TIMER_H
#define NGIND_TIMER_H

#include <chrono>

namespace ngind {

class Timer {
public:
    using time_type = std::chrono::time_point<std::chrono::system_clock>;

    explicit Timer(const float& scale = 1.0f);
    ~Timer() = default;

    void pause();
    void resume();
    void sleep(const float&);
    float getTick();

    static inline time_type getNow() {
        return std::chrono::system_clock::now();
    }

    inline void start() {
        _previous = getNow();
    }

    inline void theWorld() {
        this->pause();
    }

    inline void setTimeScale(const float& scale) {
        this->_time_scale = scale;
    }

    inline const float getTimeScale() const {
        return this->_time_scale;
    }

    inline const float GetLocalClock() const {
        return this->_local_clock;
    }
private:
    float _time_scale, _local_clock, _pause_used;
    time_type _previous, _pause_start, _pause_end;
    bool _paused;
};

} // namespace ngind

#endif //NGIND_TIMER_H
