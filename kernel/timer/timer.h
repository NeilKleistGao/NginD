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
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/// @file timer.h

#ifndef NGIND_TIMER_H
#define NGIND_TIMER_H

#include <chrono>

namespace ngind::timer {

/**
 * A smarter timer allowing you to time and scale time even pause it.
 * You can use different timer for different usage.
 */
class Timer {
public:
    using time_type = std::chrono::time_point<std::chrono::system_clock>;

    /**
     * @param scale: scale of time speed.
     */
    explicit Timer(const float& scale = 1.0f);

    ~Timer() = default;

    /**
     * Pause current timer.
     */
    void pause();

    /**
     * Resume current timer from pause.
     */
    void resume();

    /**
     * Sleep for a while and block current thread.
     * @param sec: time to sleep in second
     */
    void sleep(const float& sec);

    /**
     * Calculate how many seconds passed
     * @return float, time passed in second
     */
    float getTick();

    /**
     * Get current time.
     * @return time_type, current time point
     */
    static inline time_type getNow() {
        return std::chrono::system_clock::now();
    }

    /**
     * Start timing.
     */
    inline void start() {
        _previous = getNow();
    }

    /**
     * @see void pause();
     */
    inline void theWorld() {
        //zawarudo! toki o tomare
        this->pause();
    }

    /**
     * Set time scale
     * @param scale: time scale
     */
    inline void setTimeScale(const float& scale) {
        this->_time_scale = scale;
    }

    /**
     * Get time scale
     * @return float, time scale
     */
    inline const float getTimeScale() const {
        return this->_time_scale;
    }

    /**
     * Get the actual passed time
     * @return float, seconds passed
     */
    inline const float GetLocalClock() const {
        return this->_local_clock;
    }
private:
    /**
     * Time scale
     */
    float _time_scale;

    /**
     * Actual time lock
     */
    float _local_clock;

    /**
     * Time passed when timer is paused
     */
    float _pause_used;

    /**
     * Previous time point
     */
    time_type _previous;

    /**
     * Time point when pause started
     */
    time_type _pause_start;

    /**
     * Time point when pause ended
     */
    time_type _pause_end;

    /**
     * If timer paused
     */
    bool _paused;
};

} // namespace ngind::timer

#endif //NGIND_TIMER_H
