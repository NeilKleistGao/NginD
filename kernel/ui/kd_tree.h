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

/// @file kd_tree.h

#ifndef NGIND_KD_TREE_H
#define NGIND_KD_TREE_H

#include <vector>

#include "glm/glm.hpp"
#include "clickable_receiver.h"

namespace ngind::ui {

class KDTree {
public:
    KDTree();
    ~KDTree();

    /**
     * Insert a new clickable receiver.
     * @param value: new clickable receiver
     */
    void insert(const ClickableReceiver& value);

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
    inline ClickableReceiver* query(const glm::vec2 & point) {
        return this->query(_root, point);
    }
private:
    /**
     * Max receiver a node can contain. If too many receivers in the same node, split it.
     */
    constexpr static size_t MAX_NODE_THRESHOLD = 8;

    struct KDNode {
        bool vertical;
        float center;
        KDNode* first;
        KDNode* second;

        std::vector<ClickableReceiver> receivers;

        KDNode() : vertical(true), center(0.0f), first(nullptr), second(nullptr), receivers() {}
    };

    KDNode* _root;

    /**
     * Erase all data in a node recursively.
     * @param node: given node
     */
    void erase(KDNode* node);

    /**
     * Erase a receiver with calculated boundary recursively.
     * @param node: current node
     * @param value: receiver to be removed
     * @param top: top of receiver's area
     * @param bottom: bottom of receiver's area
     * @param left: left of receiver's area
     * @param right: right of receiver's area
     */
    void erase(KDNode* node, const ClickableReceiver& value, float top, float bottom, float left, float right);

    /**
     * Insert a new receiver recursively.
     * @param node: current node
     * @param value: receiver to be inserted
     * @param top: top of receiver's area
     * @param bottom: bottom of receiver's area
     * @param left: left of receiver's area
     * @param right: right of receiver's area
     */
    void insert(KDNode* node, const ClickableReceiver& value, float top, float bottom, float left, float right);

    /**
     * Check given point's state recursively.
     * @param node: current node
     * @param point: given point
     * @param last: last receiver satisfying the condition
     * @return ClickableReceiver*, the receiver containing this point, null if receiver doesn't exit
     */
    ClickableReceiver* query(KDNode* node, const glm::vec2& point);
};

} // namespace ui

#endif //NGIND_KD_TREE_H
