/** MIT License
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

/// @file physics_shape.cc

#include "physics_shape.h"

#include "kernel/log/logger_factory.h"

namespace ngind::physics {

CircleShape::CircleShape(const typename resources::ConfigResource::JsonObject& data) : PhysicsShape(), radius(0) {
    try {
        shape = new b2CircleShape();
        radius = shape->m_radius = data["radius"].GetFloat();
    }
    catch (...) {
        auto logger = log::LoggerFactory::getInstance()->getLogger("crash.log", log::LogLevel::LOG_LEVEL_ERROR);
        logger->log("Can't create circle shape.");
        logger->flush();
    }
}

CircleShape::~CircleShape() {
    if (shape != nullptr) {
        delete shape;
        shape = nullptr;
    }
}

PolygonShape::PolygonShape(const typename resources::ConfigResource::JsonObject& data) : PhysicsShape(), vertex(nullptr), length(0) {
    try {
        shape = new b2PolygonShape();
        length = data["length"].GetInt();
        if (length == 1) {
            auto size = data["vertex"].GetArray();
            for (const auto& s : size) {
                dynamic_cast<b2PolygonShape*>(shape)->SetAsBox(s["x"].GetFloat() / 2, s["y"].GetFloat() / 2);
            }
        }
        else {
            vertex = new b2Vec2[length];
            auto list = data["vertex"].GetArray();
            int i = 0;
            for (const auto& v : list) {
                vertex[i] = b2Vec2{v["x"].GetFloat(), v["y"].GetFloat()};
            }

            dynamic_cast<b2PolygonShape*>(shape)->Set(vertex, length);
        }
    }
    catch (...) {
        auto logger = log::LoggerFactory::getInstance()->getLogger("crash.log", log::LogLevel::LOG_LEVEL_ERROR);
        logger->log("Can't create polygon shape.");
        logger->flush();
    }
}

PolygonShape::~PolygonShape() {
    if (shape != nullptr) {
        delete shape;
        shape = nullptr;
    }

    if (vertex != nullptr) {
        delete [] vertex;
        vertex = nullptr;
    }
}

EdgeShape::EdgeShape(const typename resources::ConfigResource::JsonObject& data) : PhysicsShape(), vertex(nullptr), length(0) {
    try {
        shape = new b2EdgeShape();
        length = data["length"].GetInt();
        vertex = new b2Vec2[length];

        int i = 0;
        auto array = data["vertex"].GetArray();
        for (const auto& v : array) {
            vertex[i++] = b2Vec2{v["x"].GetFloat(), v["y"].GetFloat()};
        }

        if (length == 2) {
            dynamic_cast<b2EdgeShape*>(shape)->SetTwoSided(vertex[0], vertex[1]);
        }
        else if (length == 4) {
            dynamic_cast<b2EdgeShape*>(shape)->SetOneSided(vertex[0], vertex[1], vertex[2], vertex[3]);
        }
        else {
            throw std::exception();
        }
    }
    catch (...) {
        auto logger = log::LoggerFactory::getInstance()->getLogger("crash.log", log::LogLevel::LOG_LEVEL_ERROR);
        logger->log("Can't create edge shape.");
        logger->flush();
    }
}

EdgeShape::~EdgeShape() {
    if (shape != nullptr) {
        delete shape;
        shape = nullptr;
    }

    if (vertex != nullptr) {
        delete [] vertex;
        vertex = nullptr;
    }
}

ChainShape::ChainShape(const typename resources::ConfigResource::JsonObject& data) : PhysicsShape(), vertex(nullptr), length(0) {
    try {
        shape = new b2ChainShape();
        length = data["length"].GetInt();
        vertex = new b2Vec2[length];

        int i = 0;
        auto array = data["vertex"].GetArray();
        for (const auto& v : array) {
            vertex[i++] = b2Vec2{v["x"].GetFloat(), v["y"].GetFloat()};
        }

        dynamic_cast<b2ChainShape*>(shape)->CreateLoop(vertex, length);
    }
    catch (...) {
        auto logger = log::LoggerFactory::getInstance()->getLogger("crash.log", log::LogLevel::LOG_LEVEL_ERROR);
        logger->log("Can't create chain shape.");
        logger->flush();
    }
}

ChainShape::~ChainShape() {
    if (shape != nullptr) {
        delete shape;
        shape = nullptr;
    }

    if (vertex != nullptr) {
        delete [] vertex;
        vertex = nullptr;
    }
}

} // namespace ngind::physics