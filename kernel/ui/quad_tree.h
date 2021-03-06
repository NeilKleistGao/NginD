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

/**
 * Quad tree data structure in order to divide the 2D world into 4 areas thus getting a better performance.
 */
class QuadTree {
public:
    /**
     * @param top: top of the world.
     * @param bottom: bottom of the world.
     * @param left: left of the world.
     * @param right: right of the world.
     */
    QuadTree(const int& top, const int& bottom, const int& left, const int& right);

    ~QuadTree();

    QuadTree(const QuadTree&) = delete;
    QuadTree& operator= (const QuadTree&) = delete;

    /**
     * Insert a new clickable receiver.
     * @param value: new clickable receiver
     */
    inline void insert(const ClickableReceiver& value) {
        this->insert(_root, value);
    }

    /**
     * Erase some receiver from the tree.
     * @param value: receiver to be removed
     */
    void erase(const ClickableReceiver& value);

    /**
     * Check if given point is in some receiver's area.
     * @param point: given 2D point
     * @return ClickableReceiver*, the receiver containing this point, null if receiver doesn't exit
     */
    ClickableReceiver* query(const glm::vec2 & point);

private:
    /**
     * Max receiver a node can contain. If too many receivers in the same node, split it.
     */
    constexpr static size_t MAX_NODE_THRESHOLD = 8;

    /**
     * Node with 4 children.
     */
    struct QuadNode {
        /**
         * The second quadrant.
         */
        QuadNode* upper_left;

        /**
         * The first quadrant.
         */
        QuadNode* upper_right;

        /**
         * The third quadrant.
         */
        QuadNode* lower_left;

        /**
         * The fourth quadrant.
         */
        QuadNode* lower_right;

        /**
         * Receiver data.
         */
        std::vector<ClickableReceiver> value;

        /**
         * Boundary of this sub area.
         */
        int top{}, bottom{}, left{}, right{};

        QuadNode() : upper_left(nullptr), upper_right(nullptr), lower_left(nullptr), lower_right(nullptr) {
            value.clear();
        }
    };

    /**
     * Root of quad tree.
     */
    QuadNode* _root;

    /**
     * Erase all data in a node recursively.
     * @param node: given node
     */
    void erase(QuadNode* node);

    /**
     * Erase a receiver with calculated boundary recursively.
     * @param node: current node
     * @param value: receiver to be removed
     * @param top: top of receiver's area
     * @param bottom: bottom of receiver's area
     * @param left: left of receiver's area
     * @param right: right of receiver's area
     */
    void erase(QuadNode* node, const ClickableReceiver& value, const int& top, const int& bottom, const int& left, const int& right);

    /**
     * Insert a new receiver recursively.
     * @param node: current node
     * @param value: receiver to be inserted
     */
    void insert(QuadNode* node, const ClickableReceiver& value);

    /**
     * Check given point's state recursively.
     * @param node: current node
     * @param point: given point
     * @param last: last receiver satisfying the condition
     * @return ClickableReceiver*, the receiver containing this point, null if receiver doesn't exit
     */
    ClickableReceiver* query(QuadNode* node, const glm::vec2& point, ClickableReceiver* last);

    /**
     * Check whether a point is in the area or not.
     * @param rec: given area data
     * @param point: given point
     * @return bool, true if point is in the area
     */
    bool check(const ClickableReceiver& rec, const glm::vec2& point);
};

} // namespace ngind::ui

#endif //NGIND_QUAD_TREE_H
