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

/// @file quad_tree.h

#ifndef NGIND_QUAD_TREE_H
#define NGIND_QUAD_TREE_H

#include <vector>
#include <functional>

#include "clickable_receiver.h"

namespace ngind::ui {
class QuadTree {
public:
    QuadTree(const int& top, const int& bottom, const int& left, const int& right);

    ~QuadTree();

    QuadTree(const QuadTree&) = delete;
    QuadTree& operator= (const QuadTree&) = delete;

    inline void insert(const ClickableReceiver& value) {
        this->insert(_root, value);
    }

    void erase(const ClickableReceiver& value);

    ClickableReceiver* query(const glm::vec2 & point);

private:
    constexpr static size_t MAX_NODE_THRESHOLD = 8;

    struct QuadNode {
        QuadNode* upper_left;
        QuadNode* upper_right;
        QuadNode* lower_left;
        QuadNode* lower_right;

        std::vector<ClickableReceiver> value;

        int top, bottom, left, right;

        QuadNode() : upper_left(nullptr), upper_right(nullptr), lower_left(nullptr), lower_right(nullptr) {
            value.clear();
        }
    };

    QuadNode* _root;

    void erase(QuadNode* node);
    void erase(QuadNode* node, const ClickableReceiver& value, const int& top, const int& bottom, const int& left, const int& right);

    void insert(QuadNode* node, const ClickableReceiver& value);

    ClickableReceiver* query(QuadNode* node, const glm::vec2& point, ClickableReceiver* last);

    bool check(const ClickableReceiver& rec, const glm::vec2& point);
};

} // namespace ngind::ui

#endif //NGIND_QUAD_TREE_H
