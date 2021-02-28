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

/// @file quad_tree.cc

#include "quad_tree.h"

#include <climits>

namespace ngind::ui {

QuadTree::QuadTree(const int& top, const int& bottom, const int& left, const int& right) {
    _root = new QuadNode();
    _root->top = top;
    _root->bottom = bottom;
    _root->left = left;
    _root->right = right;
}

QuadTree::~QuadTree() {
    if (_root != nullptr) {
        this->erase(_root);
        delete _root;
        _root = nullptr;
    }
}

void QuadTree::erase(const ClickableReceiver& value) {
    if (value.vertex.empty()) {
        // TODO:
    }
    int top = value.vertex[0].y, bottom = value.vertex[0].y,
        left = value.vertex[0].x, right = value.vertex[0].x;

    for (const auto& v : value.vertex) {
        top = std::max(top, static_cast<int>(v.y));
        bottom = std::min(bottom, static_cast<int>(v.y));
        left = std::min(left, static_cast<int>(v.x));
        right = std::max(right, static_cast<int>(v.x));
    }

    this->erase(_root, value, top, bottom, left, right);
}

ClickableReceiver* QuadTree::query(const glm::vec2 & point, const input::MouseCode& code) {
    return this->query(_root, point, code, nullptr);
}

void QuadTree::erase(QuadNode* node) {
    if (node->upper_left != nullptr) {
        this->erase(node->upper_left);
        delete node->upper_left;
        node->upper_left = nullptr;
    }

    if (node->upper_right != nullptr) {
        this->erase(node->upper_right);
        delete node->upper_right;
        node->upper_right = nullptr;
    }

    if (node->lower_left != nullptr) {
        this->erase(node->lower_left);
        delete node->lower_left;
        node->lower_left = nullptr;
    }

    if (node->lower_right != nullptr) {
        this->erase(node->lower_right);
        delete node->lower_right;
        node->lower_right = nullptr;
    }
}

void QuadTree::insert(QuadNode* node, const ClickableReceiver& value) {
    node->value.push_back(value);
    if (node->value.size() < MAX_NODE_THRESHOLD) {
        return;
    }

    for (int i = 0; i < node->value.size(); ) {
        int left = INT_MAX, right = INT_MIN,
            top = INT_MIN, bottom = INT_MAX;

        for (const auto& v : node->value[i].vertex) {
            left = std::min(left, static_cast<int>(v.x));
            right = std::max(right, static_cast<int>(v.x));
            top = std::max(top, static_cast<int>(v.y));
            bottom = std::min(bottom, static_cast<int>(v.y));
        }

        int vertical = (node->left + node->right) >> 1,
            horizontal = (node->top + node->bottom) >> 1;

        if (left >= vertical && bottom >= horizontal) {
            if (node->upper_right == nullptr) {
                node->upper_right = new(std::nothrow) QuadNode();
                if (node->upper_right == nullptr) {
                    // TODO:
                }
                node->upper_right->bottom = horizontal;
                node->upper_right->top = node->top;
                node->upper_right->left = vertical;
                node->upper_right->right = node->right;
            }

            this->insert(node->upper_right, node->value[i]);
            node->value.erase(node->value.begin() + i);
        }
        else if (left >= vertical && top < horizontal) {
            if (node->lower_right == nullptr) {
                node->lower_right = new(std::nothrow) QuadNode();
                if (node->lower_right == nullptr) {
                    // TODO:
                }
                node->lower_right->bottom = node->bottom;
                node->lower_right->top = horizontal;
                node->lower_right->left = vertical;
                node->lower_right->right = node->right;
            }

            this->insert(node->lower_right, node->value[i]);
            node->value.erase(node->value.begin() + i);
        }
        else if (right < vertical && bottom >= horizontal) {
            if (node->upper_left == nullptr) {
                node->upper_left = new(std::nothrow) QuadNode();
                if (node->upper_left == nullptr) {
                    // TODO:
                }
                node->upper_left->bottom = horizontal;
                node->upper_left->top = node->top;
                node->upper_left->left = node->left;
                node->upper_left->right = vertical;
            }

            this->insert(node->upper_left, node->value[i]);
            node->value.erase(node->value.begin() + i);
        }
        else if (right < vertical && top < horizontal) {
            if (node->lower_left == nullptr) {
                node->lower_left = new(std::nothrow) QuadNode();
                if (node->lower_left == nullptr) {
                    // TODO:
                }
                node->lower_left->bottom = node->bottom;
                node->lower_left->top = horizontal;
                node->lower_left->left = node->left;
                node->lower_left->right = vertical;
            }

            this->insert(node->lower_left, node->value[i]);
            node->value.erase(node->value.begin() + i);
        }
        else {
            ++i;
        }
    }
}

void QuadTree::erase(QuadNode* node, const ClickableReceiver& value,
                     const int& top, const int& bottom, const int& left, const int& right) {
    int vertical = (node->left + node->right) >> 1,
            horizontal = (node->top + node->bottom) >> 1;

    if (left >= vertical && bottom >= horizontal && node->upper_right != nullptr) {
        this->erase(node->upper_right, value, top, bottom, left, right);

        if (node->upper_right->value.empty()) {
            delete node->upper_right;
            node->upper_right = nullptr;
        }
    }
    else if (left >= vertical && top < horizontal && node->lower_right != nullptr) {
        this->erase(node->lower_right, value, top, bottom, left, right);

        if (node->lower_right->value.empty()) {
            delete node->lower_right;
            node->lower_right = nullptr;
        }
    }
    else if (right < vertical && bottom >= horizontal && node->upper_left != nullptr) {
        this->erase(node->upper_left, value, top, bottom, left, right);

        if (node->upper_left->value.empty()) {
            delete node->upper_left;
            node->upper_left = nullptr;
        }
    }
    else if (right < vertical && top < horizontal && node->lower_left != nullptr) {
        this->erase(node->lower_left, value, top, bottom, left, right);

        if (node->lower_left->value.empty()) {
            delete node->lower_left;
            node->lower_left = nullptr;
        }
    }
    else {
        for (int i = 0; i < node->value.size(); i++) {
            if (node->value[i] == value) {
                node->value.erase(node->value.begin() + i);
                break;
            }
        }
    }
}

ClickableReceiver* QuadTree::query(QuadNode* node, const glm::vec2& point, const input::MouseCode& code, ClickableReceiver* last) {
    for (auto& v : node->value) {
        if (check(v, point)) {
            if (last == nullptr || last->z_order < v.z_order) {
                last = &v;
            }
        }
    }

    int vertical = (node->left + node->right) >> 1,
            horizontal = (node->top + node->bottom) >> 1;

    if (point.x >= vertical && point.y >= horizontal && node->upper_right != nullptr) {
        return this->query(node->upper_right, point, code, last);
    }
    else if (point.x >= vertical && point.y < horizontal && node->lower_right != nullptr) {
        return this->query(node->lower_right, point, code, last);
    }
    else if (point.x < vertical && point.y >= horizontal && node->upper_left != nullptr) {
        return this->query(node->upper_left, point, code, last);
    }
    else if (point.x < vertical && point.y < horizontal && node->lower_left != nullptr) {
        return this->query(node->lower_left, point, code, last);
    }

    return last;
}

bool QuadTree::check(const ClickableReceiver& rec, const glm::vec2& point) {
    int count = 0;
    auto size = rec.vertex.size();
    for (int i = 0, j = 1; i < size; i++, j = (j + 1) % size) {
        const auto& v1 = rec.vertex[i];
        const auto& v2 = rec.vertex[j];

        auto t2 = (point.y - v1.y) / (v2.y - v1.y);
        if (t2 < 0 || t2 >= 1) {
            continue;
        }

        auto t = v1.x + t2 * (v2.x - v1.x) - point.x;
        if (t < 0) {
            continue;
        }

        if (t2 < 1e-6) {
            const auto& v3 = rec.vertex[(i - 1 + size) % size];
            if ((v3.y - v1.y) * (v2.y - v1.y) < 0) {
                count++;
            }
        }
        else {
            count++;
        }
    }

    return count & 1;
}

} // namespace ngind::ui