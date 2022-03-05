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

/// @file kd_tree.cc

#include "kd_tree.h"

namespace ngind::ui {
KDTree::KDTree() : _root(new KDNode()) {
}

KDTree::~KDTree() {
    if (_root != nullptr) {
        erase(_root);
        _root = nullptr;
    }
}

void KDTree::insert(const ClickableReceiver& value) {
    if (value.vertex.empty()) {
        return;
    }

    float top = value.vertex[0].y, bottom = value.vertex[0].y,
            left = value.vertex[0].x, right = value.vertex[0].x;

    for (const auto& v : value.vertex) {
        top = std::max(top, v.y);
        bottom = std::min(bottom, v.y);
        left = std::min(left, v.x);
        right = std::max(right, v.x);
    }

    this->insert(_root, value, top, bottom, left, right);
}

void KDTree::erase(const ClickableReceiver& value) {
    if (value.vertex.empty()) {
        return;
    }

    float top = value.vertex[0].y, bottom = value.vertex[0].y,
            left = value.vertex[0].x, right = value.vertex[0].x;

    for (const auto& v : value.vertex) {
        top = std::max(top, v.y);
        bottom = std::min(bottom, v.y);
        left = std::min(left, v.x);
        right = std::max(right, v.x);
    }

    this->erase(_root, value, top, bottom, left, right);
}

void KDTree::erase(KDNode* node) {
    if (node == nullptr) {
        return;
    }

    if (node->receivers.empty()) {
        erase(node->first);
        erase(node->second);

        delete node->first;
        delete node->second;
        node->first = nullptr;
        node->second = nullptr;
    }
    else {
        node->receivers.clear();
    }
}

void KDTree::erase(KDNode* node, const ClickableReceiver& value, float top, float bottom, float left, float right) {
    if (node->first == nullptr) {
        auto target = node->receivers.end();
        for (auto it = node->receivers.begin(); it != node->receivers.end(); ++it) {
            if ((*it) == value) {
                target = it;
                break;
            }
        }

        if (target != node->receivers.end()) {
            node->receivers.erase(target);
            return;
        }
    }

    if (node->vertical) {
        if (right <= node->center) {
            this->erase(node->first, value, top, bottom, left, right);
        }
        else if (left > node->center) {
            this->erase(node->second, value, top, bottom, left, right);
        }
        else {
            this->erase(node->first, value, top, bottom, left, right);
            this->erase(node->second, value, top, bottom, left, right);
        }
    }
    else {
        if (top <= node->center) {
            this->erase(node->first, value, top, bottom, left, right);
        }
        else if (bottom> node->center) {
            this->erase(node->second, value, top, bottom, left, right);
        }
        else {
            this->erase(node->first, value, top, bottom, left, right);
            this->erase(node->second, value, top, bottom, left, right);
        }
    }

    if (node->first->receivers.empty() && node->second->receivers.empty()) {
        delete node->first;
        delete node->second;
        node->first = nullptr;
        node->second = nullptr;
    }
}

void KDTree::insert(KDNode* node, const ClickableReceiver& value, float top, float bottom, float left, float right) {
    if (node->first == nullptr) {
        node->receivers.push_back(value);
        if (node->receivers.size() > MAX_NODE_THRESHOLD) {
            node->first = new KDNode();
            node->second = new KDNode();
            node->first->vertical = node->second->vertical = !node->vertical;

            node->center = 0.0;
            for (const auto& r : node->receivers) {
                float temp = 0.0f;
                for (const auto& v : r.vertex) {
                    if (node->vertical) {
                        temp += v.x;
                    }
                    else {
                        temp += v.y;
                    }
                }

                temp /= static_cast<float>(r.vertex.size());
                node->center += temp;
            }
            node->center /= static_cast<float>(node->receivers.size());

            for (auto r : node->receivers) {
                float tp = r.vertex[0].y, bt = r.vertex[0].y,
                        lt = r.vertex[0].x, rt = r.vertex[0].x;
                for (const auto& v : r.vertex) {
                    tp = std::max(tp, v.y);
                    bt = std::min(bt, v.y);
                    lt = std::min(lt, v.x);
                    rt = std::max(rt, v.x);
                }

                if (node->vertical) {
                    if (rt <= node->center) {
                        this->insert(node->first, r, tp, bt, lt, rt);
                    }
                    else if (lt > node->center) {
                        this->insert(node->second, r, tp, bt, lt, rt);
                    }
                    else {
                        this->insert(node->first, r, tp, bt, lt, rt);
                        this->insert(node->second, r, tp, bt, lt, rt);
                    }
                }
                else {
                    if (tp <= node->center) {
                        this->insert(node->first, r, tp, bt, lt, rt);
                    }
                    else if (bt > node->center) {
                        this->insert(node->second, r, tp, bt, lt, rt);
                    }
                    else {
                        this->insert(node->first, r, tp, bt, lt, rt);
                        this->insert(node->second, r, tp, bt, lt, rt);
                    }
                }
            }

            node->receivers.clear();
        }
    }
    else {
        if (node->vertical) {
            if (right <= node->center) {
                this->insert(node->first, value, top, bottom, left, right);
            }
            else if (left > node->center) {
                this->insert(node->second, value, top, bottom, left, right);
            }
            else {
                this->insert(node->first, value, top, bottom, left, right);
                this->insert(node->second, value, top, bottom, left, right);
            }
        }
        else {
            if (top <= node->center) {
                this->insert(node->first, value, top, bottom, left, right);
            }
            else if (bottom> node->center) {
                this->insert(node->second, value, top, bottom, left, right);
            }
            else {
                this->insert(node->first, value, top, bottom, left, right);
                this->insert(node->second, value, top, bottom, left, right);
            }
        }
    }
}

ClickableReceiver* KDTree::query(KDNode* node, const glm::vec2& point) {
    ClickableReceiver* res = nullptr;
    if (!node->receivers.empty()) {
        for (auto & receiver : node->receivers) {
            if (receiver*point) {
                if (res == nullptr || res->z_order < receiver.z_order) {
                    res = &receiver;
                }
            }
        }
    }
    else if (node->first) {
        if (node->vertical) {
            if (point.x <= node->center) {
                res = query(node->first, point);
            }
            else {
                res = query(node->second, point);
            }
        }
        else {
            if (point.y <= node->center) {
                res = query(node->first, point);
            }
            else {
                res = query(node->second, point);
            }
        }
    }

    return res;
}


} // namespace ngind::ui
