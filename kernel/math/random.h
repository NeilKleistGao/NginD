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

/// @file random.h

#ifndef NGIND_RANDOM_H
#define NGIND_RANDOM_H

#include <random>

#include "script/lua_registration.h"

namespace ngind::math {
/**
 * A random number generator class. This class ues a better algorithm and
 * is more powerful.
 */
class Random {
public:
    Random();

    /**
     * Generate a random number in the given range
     * @param min: left boundary, included
     * @param max: right boundary, not included
     * @return int, a random number
     */
    int getRangeRandomNumber(const int& min, const int& max);

    /**
     * Generate a random real number between 0 and 1. Both are included.
     * @return float, a real random number
     */
    float getPercentageRandomNumber();

    /**
     * Generate a random number meeting the requirement of normal distribute
     * @param std: the standard deviation
     * @param mean: the mean number
     * @return float, a random number
     */
    float getNormalDistributionRandomNumber(const float& std, const float& mean);

private:
    /**
     * The real pseudo number generator
     */
    std::mt19937 _mt;

    /**
     * The random engine for normal distribution
     */
    std::default_random_engine _engine;
};

NGIND_LUA_BRIDGE_REGISTRATION(Random) {
luabridge::getGlobalNamespace(script::LuaState::getInstance()->getState())
    .beginNamespace("engine")
        .beginClass<Random>("Random")
            .addConstructor<void(*)(void)>()
            .addFunction("getRangeRandomNumber", &Random::getRangeRandomNumber)
            .addFunction("getPercentageRandomNumber", &Random::getPercentageRandomNumber)
            .addFunction("getNormalDistributionRandomNumber", &Random::getNormalDistributionRandomNumber)
        .endClass()
    .endNamespace();
}

} // namespace ngind::random

#endif //NGIND_RANDOM_H
