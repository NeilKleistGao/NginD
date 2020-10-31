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
// FILENAME: world.h
// LAST MODIFY: 2020/10/31

#ifndef NGIND_WORLD_H
#define NGIND_WORLD_H

#include <string>

#include "object.h"
#include "components/component.h"
#include "resources/config_resource.h"
#include "render/rgba.h"

namespace ngind {

class World : public Object {
public:
    explicit World(std::string);

    inline std::string getName() {
        return _name;
    }

    inline RGBA getBackgroundColor() const {
        return _background_color;
    }

    inline void setBackgroundColor(const RGBA& color) {
        _background_color = color;
    }

    inline void setBackgroundColor(const std::string& code) {
        _background_color = RGBA{code};
    }

    void update(const float&) override;
private:
    std::string _name;
    ConfigResource* _config;
    RGBA _background_color;

    void loadObjects();
    Object* generateObject(Object*, const typename ConfigResource::JsonObject&);
    Component* generateComponent(const typename ConfigResource::JsonObject&);
};

} // namespace ngind

#endif //NGIND_WORLD_H
