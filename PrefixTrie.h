//
// Created by Ryan.Zurrin001 on 1/7/2022.
//

#ifndef TRIEDS_PREFIXTRIE_H
#define TRIEDS_PREFIXTRIE_H
#include <vector>
#include <unordered_map>
#include <memory>

using namespace std;

class trieNode {
public:
    char data;
    unordered_map<char, std::unique_ptr<trieNode>> children;
    bool isTerminal;
    explicit trieNode(char data) {
        this->data = data;
        this->isTerminal = false;
    }
};

class PrefixTrie {
    // use smart pointers to make a root node
    std::shared_ptr<trieNode> root;

public:
    PrefixTrie();
    ~PrefixTrie();

    __attribute__((unused)) std::shared_ptr<trieNode> getRoot();

    __attribute__((unused)) __attribute__((unused)) void setRoot(std::unique_ptr<trieNode> root_);
    __attribute__((unused)) void insert(const std::string& word);
    __attribute__((unused)) bool search(const std::string& word);

    __attribute__((unused)) __attribute__((unused)) bool startsWith(const std::string& prefix);
    __attribute__((unused)) void print();
};



PrefixTrie::PrefixTrie() {
    root = std::make_unique<trieNode>('\0');
}

PrefixTrie::~PrefixTrie() = default;

__attribute__((unused)) std::shared_ptr<trieNode> PrefixTrie::getRoot() {
    return root;
}

__attribute__((unused)) void PrefixTrie::setRoot(std::unique_ptr<trieNode> root_) {
    root = std::move(root_);
}

__attribute__((unused)) void PrefixTrie::insert(const std::string& word) {
    trieNode *current = root.get();
    for (char c : word) {
        if (current->children.count (c) == 0) {
            current->children[c] = std::make_unique<trieNode>(c);
        }
        current = current->children[c].get();
    }
    current->isTerminal = true;
}

__attribute__((unused)) bool PrefixTrie::search(const std::string& word) {
    trieNode *current = root.get();
    for (char c : word) {
        if (current->children.count (c) == 0) {
            return false;
        }
        current = current->children[c].get();
    }
    return current->isTerminal;
}

__attribute__((unused)) bool PrefixTrie::startsWith(const std::string& prefix) {
    trieNode *current = root.get();
    for (char c : prefix) {
        if (current->children.count (c) == 0) {
            return false;
        }
        current = current->children[c].get();
    }
    return true;
}

__attribute__((unused)) void PrefixTrie::print() {
    std::vector<trieNode *> queue;
    queue.push_back(root.get());
    while (!queue.empty()) {
        trieNode *current = queue.front();
        queue.erase(queue.begin());
        cout << current->data << " ";
        for (auto &child : current->children) {
            queue.push_back(child.second.get());
        }
    }
    cout << endl;
}



#endif //TRIEDS_PREFIXTRIE_H
