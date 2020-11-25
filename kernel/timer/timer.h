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

/// @file timer.h
/// @date 2020/10/16

#ifndef NGIND_TIMER_H
#define NGIND_TIMER_H

#include <chrono>

namespace ngind {

/**
@class
    A smarter timer allowing you to time and scale time even pause it.
You can use different timer for different usage.
*/
class Timer {
public:
    /// @public
    /// @typedef Time point type.
    using time_type = std::chrono::time_point<std::chrono::system_clock>;

    /// @public
    /// @param const float& scale: scale of time speed.
    explicit Timer(const float& scale = 1.0f);

    /// @public
    ~Timer() = default;

    /// @public
    /// @fn Pause current timer.
    /// @param void
    /// @return void
    void pause();

    /// @public
    /// @fn Resume current timer from pause.
    /// @param void
    /// @return void
    void resume();

    /// @public
    /// @fn Sleep for a while and block current thread.
    /// @param const float&: time to sleep in second
    /// @return void
    void sleep(const float&);

    /// @public
    /// @fn Calculate how many seconds passed
    /// @param void
    /// @return float, time passed in second
    float getTick();

    /// @public
    /// @static
    /// @fn Get current time.
    /// @param void
    /// @return time_type, current time point
    static inline time_type getNow() {
        return std::chrono::system_clock::now();
    }

    /// @public
    /// @fn Start timing.
    /// @param void
    /// @return void
    inline void start() {
        _previous = getNow();
    }

    /// @see void pause();
    inline void theWorld() {
        //zawarudo! toki o tomare
        this->pause();
    }

    /// @public
    /// @fn Set time scale
    /// @param const float& scale: time scale
    /// @return void
    inline void setTimeScale(const float& scale) {
        this->_time_scale = scale;
    }

    /// @public
    /// @fn Get time scale
    /// @param void
    /// @return float, time scale
    inline const float getTimeScale() const {
        return this->_time_scale;
    }

    /// @public
    /// @fn Get the actual passed time
    /// @param void
    /// @return float, seconds passed
    inline const float GetLocalClock() const {
        return this->_local_clock;
    }
private:
    /// @private
    /// @property Time scale
    float _time_scale;

    /// @private
    /// @property Actual time lock
    float _local_clock;

    /// @private
    /// @property Time passed when timer is paused
    float _pause_used;

    /// @private
    /// @property Previous time point
    time_type _previous;

    /// @private
    /// @property Time point when pause started
    time_type _pause_start;

    /// @private
    /// @property Time point when pause ended
    time_type _pause_end;

    /// @private
    /// @property If timer paused
    bool _paused;
};

} // namespace ngind

#endif //NGIND_TIMER_H
