//
// Created by Ryan.Zurrin001 on 1/8/2022.
//

#ifndef TRIEDS_BINARYTRIE_H
#define TRIEDS_BINARYTRIE_H
#include <vector>
#include <unordered_map>
#include <memory>

class btNode {
public:
    std::shared_ptr<btNode> left; // 0
    std::shared_ptr<btNode> right; // 1
};

class __attribute__((unused)) BinaryTrie {
    std::shared_ptr<btNode> root;
    int max_xor_helper(int val);

public:
    BinaryTrie();
    void insert(int n);

    __attribute__((unused)) int max_xor(vector<int> in, int len);
    __attribute__((unused)) bool search(int val);
    __attribute__((unused)) void print();
}; // _____________________end of class BinaryTrie_____________________

BinaryTrie::BinaryTrie() {
    root = std::make_shared<btNode>();
}

void BinaryTrie::insert(int n) {
    std::shared_ptr<btNode> curr = root;
    for (int i = 31; i >= 0; i--) {
        int bit = (n >> i) & 1;
        if (bit == 0) {
            if (curr->left == nullptr) {
                curr->left = std::make_shared<btNode>();
            }
            curr = curr->left;
        } else {
            if (curr->right == nullptr) {
                curr->right = std::make_shared<btNode>();
            }
            curr = curr->right;
        }
    }
}

int BinaryTrie::max_xor_helper(int val) {
    int current_ans = 0;
    std::shared_ptr<btNode> curr = root;

    for (int i = 31; i >= 0; i--) {
        int bit = (val >> i) & 1;
        if (bit == 0) {
            if (curr->right != nullptr) {
                current_ans += (1 << i);
                curr = curr->right;
            } else {
                curr = curr->left;
            }
        } else {
            if (curr->left != nullptr) {
                current_ans += (1 << i);
                curr = curr->left;
            } else {
                curr = curr->right;
            }
        }
    }
    return current_ans;
}

__attribute__((unused)) int BinaryTrie::max_xor(vector<int> in, int len) {
    int ans = 0;
    for (int i = 0; i < len; i++) {
        int val = in[i];
        insert(val);
        int current_xor = max_xor_helper(val);
        ans = std::max(ans, current_xor);
    }
    return ans;
}

__attribute__((unused)) bool BinaryTrie::search(int val) {
    std::shared_ptr<btNode> curr = root;
    for (int i = 31; i >= 0; i--) {
        int bit = (val >> i) & 1;
        if (bit == 0) {
            if (curr->left == nullptr) {
                return false;
            }
            curr = curr->left;
        } else {
            if (curr->right == nullptr) {
                return false;
            }
            curr = curr->right;
        }
    }
    return true;
}

__attribute__((unused)) void BinaryTrie::print() {
    std::unordered_map<std::shared_ptr<btNode>, int> map;
    std::vector<std::shared_ptr<btNode>> queue;
    queue.push_back(root);
    int level = 0;
    while (!queue.empty()) {
        auto size = queue.size();
        for (int i = 0; i < size; i++) {
            std::shared_ptr<btNode> curr = queue.front();
            queue.erase(queue.begin());
            if (curr->left != nullptr) {
                queue.push_back(curr->left);
            }
            if (curr->right != nullptr) {
                queue.push_back(curr->right);
            }
        }
        level++;
    }
}

#endif //TRIEDS_BINARYTRIE_H
