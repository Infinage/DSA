#pragma once

#include <algorithm>
#include <concepts>
#include <queue>
#include <initializer_list>
#include <stack>
#include <vector>

template<std::integral T>
struct HashVector {
    inline std::size_t operator()(const std::vector<T> &vec) const {
        std::hash<T> hasher; auto seed {vec.size()};
        return std::ranges::fold_left(vec, seed, 
            [&hasher](std::size_t acc, const T &n) {
                acc ^= hasher(n) + 0x9e3779b9 + (acc << 6) + (acc >> 2);
                return acc;
            }
        );
    }
};

template<typename T = int>
struct BinaryTreeNode {
    T val {}; BinaryTreeNode *left {}, *right {};
    ~BinaryTreeNode() { delete left; delete right; }

    /*
     * Function to create a Forest of Binary Tree Nodes from an array.
     * Array must be in *level* order format.
     * `null` values would be set to nullptr.
     */
    static BinaryTreeNode* from(std::initializer_list<T> array, const T &null) {
        // Convert into an array of BinaryTreeNodes
        std::vector<BinaryTreeNode*> forest(array.size());
        std::transform(array.begin(), array.end(), forest.begin(), 
            [&null](const T &val) { 
                return val == null? nullptr: new BinaryTreeNode {val}; 
            }
        );

        // Link the BinaryTreeNode to parent
        std::size_t parent {}, N {forest.size()};
        for (std::size_t curr {1}; curr < N; ++curr) {
            if (curr % 2) forest[parent]->left = forest[curr];
            else forest[parent++]->right = forest[curr];
            while (parent < N && !forest[parent]) ++parent;
        }

        return forest.empty()? nullptr: forest[0];
    }

    /*
     * Function to create a vector of values from a Root Tree node.
     * Returned array would be in level order format.
     * nullptr values would be set to `null`.
     */
    static std::vector<T> levelOrder(BinaryTreeNode *root, const T &null) {
        std::vector<T> res; 
        std::queue<BinaryTreeNode*> queue {{root}};
        while (!queue.empty()) {
            BinaryTreeNode *curr {queue.front()}; queue.pop();
            if (!curr) res.emplace_back(null);
            else {
                queue.push(curr->left); queue.push(curr->right);
                res.emplace_back(curr->val);
            }
        }
        return res;
    }

    /*
     * Function to create a vector of values from a Root Tree node.
     * Returned array would be in inorder format, i.e: "left, root, right".
     * nullptr values would be discarded.
     */
    static std::vector<T> inOrder(BinaryTreeNode *root) {
        std::vector<T> res;
        std::stack<std::pair<BinaryTreeNode*, bool>> stk {{{root, false}}};
        while (!stk.empty()) {
            auto [curr, done] {stk.top()};
            if (!curr) {
                stk.pop(); continue;
            } else if (!done) {
                stk.top().second = true;
                stk.push({curr->left, false});
            } else {
                stk.pop(); 
                res.emplace_back(curr->val);
                stk.push({curr->right, false});
            }
        }
        return res;
    }
};
