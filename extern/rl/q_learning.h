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

/// @file q_learning.h

#ifndef NGIND_Q_LEARNING_H
#define NGIND_Q_LEARNING_H

#include <unordered_map>

#include "i_algorithm.h"
#include "action.h"
#include "math/random.h"

namespace ngind::rl {

class QLearning : IAlgorithm {
public:
    QLearning(Agent* agent, const double& learning_rate, const double& discount_factor, const double& epsilon);
    ~QLearning() override = default;

    bool step(Agent* agent, const luabridge::LuaRef& obs) override;

    void dump(const std::string& filename) override;

    void load(const std::string& filename) override;
private:
    using ActionRewards = std::unordered_map<int, double>;

    double _learning_rate;
    double _discount_factor;
    double _epsilon;

    int _state;
    int _action_space_size;

    std::unordered_map<int, ActionRewards> _q_table;

    math::Random _random;

    void learn(int state, int next_state, int action, double reward);
protected:
};

} // namespace ngind::rl

#endif //NGIND_Q_LEARNING_H
