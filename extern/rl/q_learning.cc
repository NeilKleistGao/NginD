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

/// @file q_learning.cc

#include "q_learning.h"

#include <limits>

namespace ngind::rl {

QLearning::QLearning(int action_count, const double& learning_rate, const double& discount_factor, const double& epsilon)
    : IAlgorithm(), _learning_rate(learning_rate), _discount_factor(discount_factor),
    _epsilon(epsilon), _action_space_size(action_count) {
    auto& default_table = _q_table[""] = ActionRewards{};
    for (int i = 0; i < _action_space_size; ++i) {
        default_table[i] = 0.0;
    }
}

bool QLearning::step(Agent* agent, const luabridge::LuaRef& obs) {
    float rand = _random.getPercentageRandomNumber();
    auto& actions = agent->getActionSpace();

    int next = 0;
    if (rand < _epsilon) {
        next = _random.getRangeRandomNumber(0, _action_space_size - 1);
    }
    else {
        auto reward_table = _q_table[_state];
        double max = std::numeric_limits<double>::lowest();

        for (auto [index, reward] : reward_table) {
            if (reward > max) {
                max = reward;
                next = index;
            }
        }
    }

    auto* action = actions[next];
    (*action)();

    auto update = _script["update"];
    auto get_reward = _script["getReward"];
    if (!update.isFunction() || !get_reward.isFunction()) {
        //TODO:
    }

    auto next_state = update(_script, agent, obs).cast<std::string>();
    auto reward = get_reward(_script, agent, obs).cast<double>();
    learn(_state, next_state, next, reward);
    _state = next_state;

    auto is_end = _script["isEnd"];
    if (!is_end.isFunction()) {
        //TODO:
    }

    return is_end(_script, agent, obs).cast<bool>();
}

void QLearning::dump(const std::string& filename) {
    // TODO:
}

void QLearning::load(const std::string& filename) {
    //TODO:
}

void QLearning::learn(const std::string& state, const std::string& next_state, int action, const double& reward) {
    auto& current = _q_table[state][action];
    if (_q_table.find(next_state) == _q_table.end()) {
        _q_table[next_state] = ActionRewards {};
        for (int i = 0; i < _action_space_size; ++i) {
            _q_table[next_state][i] = 0.0;
        }
    }

    double max = std::numeric_limits<double>::lowest();
    for (auto [index, rwd] : _q_table[next_state]) {
        max = std::max(max, rwd);
    }

    auto next = reward + _discount_factor * max;
    current += (next - current) * _learning_rate;
}

} // namespace ngind::rl