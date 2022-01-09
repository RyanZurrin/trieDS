#pragma ide diagnostic ignored "misc-no-recursion"
//
// Created by Ryan.Zurrin001 on 1/7/2022.
//

#ifndef TRIEDS_SUFFIXTRIE_H
#define TRIEDS_SUFFIXTRIE_H
#include <vector>
#include <unordered_map>
#include <memory>

using namespace std;

class suffixNode {
public:
    __attribute__((unused)) char data;
    unordered_map<char, std::shared_ptr<suffixNode>> children;
    bool isTerminal;
    explicit suffixNode(char data) {
        this->data = data;
        this->isTerminal = false;
    }
};

class __attribute__((unused)) SuffixTrie {
    // use smart pointers to make a root node
    std::shared_ptr<suffixNode> root;
    void insert_helper(const string& word);

public:
    SuffixTrie();
    ~SuffixTrie();

    __attribute__((unused)) std::shared_ptr<suffixNode> getRoot();
    __attribute__((unused)) void setRoot(std::unique_ptr<suffixNode> root_);
    __attribute__((unused)) void insert(string word);
    __attribute__((unused)) bool search(const std::string& word);
    __attribute__((unused)) bool endsWith(const std::string& prefix);
    void print();
};

SuffixTrie::SuffixTrie() {
    root = std::make_unique<suffixNode>('\0');
}

SuffixTrie::~SuffixTrie() = default;

__attribute__((unused)) std::shared_ptr<suffixNode> SuffixTrie::getRoot() {
    return root;
}

__attribute__((unused)) void SuffixTrie::setRoot(std::unique_ptr<suffixNode> root_) {
    root = std::move(root_);
}

void SuffixTrie::insert_helper(const string& word) {
    suffixNode *current = root.get();
    for (char c : word) {
        if (current->children.count (c) == 0) {
            current->children[c] = std::make_unique<suffixNode>(c);
        }
        current = current->children[c].get();
    }
    current->isTerminal = true;
}

__attribute__((unused)) void SuffixTrie::insert(string word) {
    for (int i = 0; word[i] != '\0'; i++) {
        insert_helper(word.substr(i));
    }
}

__attribute__((unused)) bool SuffixTrie::search(const string &word) {
    suffixNode *current = root.get();
    for (char c : word) {
        if (current->children.count (c) == 0) {
            return false;
        }
        current = current->children[c].get();
    }
    return current->isTerminal;
}

__attribute__((unused)) bool SuffixTrie::endsWith(const string &prefix) {
    suffixNode *current = root.get();
    for (char c : prefix) {
        if (current->children.count (c) == 0) {
            return false;
        }
        current = current->children[c].get();
    }
    return true;
}

void SuffixTrie::print() {
    suffixNode *current = root.get();
    for (auto &child : current->children) {
        cout << child.first << " ";
    }
    cout << endl;
    for (auto &child : current->children) {
        cout << child.first << " ";
        print();
    }
}

bool isGoogly(SuffixTrie& t, std::shared_ptr<suffixNode>& root, string& word, int i, int count) {
    if (i == word.length()) {
        return root->isTerminal && (count + 1) >= 2;
    }
    char ch = word[i];
    if (root->children.count(ch) == 0) {
        return false;
    }
    root = root->children[ch];
    if (root->isTerminal) {
        bool cntLeft = isGoogly(t, root, word, i + 1, count + 1);
        if (cntLeft) {
            return true;
        }
    }
    return isGoogly(t, root, word, i + 1, count);
}


static vector<string>  googlyStrings_suf(vector<string>& input){
    SuffixTrie t;
    for (auto& word : input) {
        t.insert(word);
    }
    vector<string> result;
    for (auto& word : input) {
        int cnt = 0;
        std::shared_ptr<suffixNode> temp = t.getRoot();
        if (isGoogly(t, temp, word, 0, cnt)) {
            result.push_back(word);
        }

    }
    return result;
}

#endif //TRIEDS_SUFFIXTRIE_H