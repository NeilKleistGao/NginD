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
// LAST MODIFY: 2020/8/30
// FILENAME: random.cc

#include "random.h"

#include <chrono>

namespace ngind {

Random::Random() {
    std::random_device rd;
    this->_mt = std::mt19937 (rd());

    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    this->_engine = std::default_random_engine(seed);
}

int Random::getRangeRandomNumber(const int& min, const int& max) {
    int len = max - min,
        res = this->_mt() % len;
    return min + res;
}

float Random::getPercentageRandomNumber() {
    int res = this->_mt();
    return (float)res / (float)(0x7fffffff);
}

float Random::getNormalDistributionRandomNumber(const float& std, const float& mean) {
    std::normal_distribution dis(mean, std);
    return dis(this->_engine);
}

} // namespace ngind