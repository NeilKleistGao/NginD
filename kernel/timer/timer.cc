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
// FILENAME: timer.cc
// LAST MODIFY: 2020/10/16

#include "timer.h"

#include "platforms/platforms.h"

namespace ngind {

Timer::Timer(const float& scale)
    : _time_scale(scale), _local_clock(0.0f), _paused(false), _pause_used(0.0f) {
}

void Timer::pause() {
    this->_paused = true;
    this->_pause_start = getNow();
    this->_pause_used = 0.0f;
}

void Timer::resume() {
    this->_paused = false;
    this->_pause_end = getNow();
    std::chrono::duration<float> duration = _pause_end - _pause_start;
    this->_pause_used = duration.count();
}

void Timer::sleep(const float& sec) {
    if (this->_paused) {
        return;
    }

    PlatformUtils::sleep(sec);
    _previous = getNow();
}

float Timer::getTick() {
    if (this->_paused) {
        return 0.0f;
    }

    time_type now = getNow();
    std::chrono::duration<float> duration = now - _previous;
    this->_previous = now;
    float local_duration = (duration.count() - _pause_used) * _time_scale;
    this->_pause_used = 0.0f;
    this->_local_clock += local_duration;

    return local_duration;
}

} // namespace ngind