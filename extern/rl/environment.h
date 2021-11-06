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

/// @file environment.h

#ifndef NGIND_ENVIRONMENT_H
#define NGIND_ENVIRONMENT_H

#include "agent.h"
#include "algorithm.h"
#include "observations.h"
#include "memory/auto_collection_object.h"

namespace ngind::rl {

class Environment : public memory::AutoCollectionObject {
public:
    Environment(Agent* agent, Observations* ob, Algorithm* algorithm, const std::string& script, const std::string& cl);
    ~Environment() override;

    void update();

    void setAgent(Agent* agent);
    void setObservations(Observations* ob);
    void setAlgorithm(Algorithm* algorithm);
private:
    Agent* _agent;
    Observations* _observations;
    Algorithm* _algorithm;

    luabridge::LuaRef _script;
    int _current;
protected:
};

} // namespace ngind::rl

#endif //NGIND_ENVIRONMENT_H
