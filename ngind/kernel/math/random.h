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

/// @file random.h
/// @date 2020/8/30

/**
@brief This file define the random number generator class by myself. Use this
rather than srand/rand functions.
*/

#ifndef NGIND_RANDOM_H
#define NGIND_RANDOM_H

#include <random>

namespace ngind {
/**
@class
    A random number generator class. This class ues a better algorithm and
is more powerful.
*/
class Random {
public:
    /// @public
    Random();

    /// @public
    /// @fn Generate a random number in the given range
    /// @param const int&: left boundary, included
    /// @param const int&: right boundary, not included
    /// @return int, a random number
    int getRangeRandomNumber(const int&, const int&);

    /// @public
    /// @fn Generate a random real number between 0 and 1. Both are included.
    /// @param void
    /// @return float, a real random number
    float getPercentageRandomNumber();

    /// @public
    /// @fn Generate a random number meeting the requirement of normal distribute
    /// @param const float&: the standard deviation
    /// @param const float&: the mean number
    /// @return float, a random number
    float getNormalDistributionRandomNumber(const float&, const float&);

private:
    /// @private
    /// @property The real pseudo number generator
    std::mt19937 _mt;

    /// @private
    /// @property The random engine for normal distribution
    std::default_random_engine _engine;
};

}

#endif //NGIND_RANDOM_H
