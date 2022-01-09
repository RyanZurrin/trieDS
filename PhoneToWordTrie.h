#pragma ide diagnostic ignored "modernize-return-braced-init-list"
#pragma ide diagnostic ignored "cert-err58-cpp"
//
// Created by Ryan.Zurrin001 on 1/9/2022.
//

#ifndef TRIEDS_PHONETOWORDTRIE_H
#define TRIEDS_PHONETOWORDTRIE_H
#include <bits/stdc++.h>
#include <utility>
using namespace std;

string keypad[] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

class wordTrieNode {
public:
    __attribute__((unused)) char data;
    bool isTerminal;
    string word;
    unordered_map<char, wordTrieNode*> children;
    explicit wordTrieNode(char data) {
        this->data = data;
        this->isTerminal = false;
        this->word = "";
    }
};

class PhoneToWordTrie {
public:
    wordTrieNode* root;
    PhoneToWordTrie() {
        root = new wordTrieNode('\0');
    }
    void insert(const string& word) const {
        wordTrieNode* curr = root;
        for (char c : word) {
            if (curr->children.count(c) == 0) {
                curr->children[c] = new wordTrieNode(c);
            }
            curr = curr->children[c];
        }
        curr->isTerminal = true;
        curr->word = word;
    }
};

#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"
void checkForWords(wordTrieNode* node, string phoneNumber, size_t i, unordered_set<string>& words) {
    if (node->isTerminal) {
        words.insert(node->word);
    }
    if (i == phoneNumber.length()) {
        return;
    }
    int num = phoneNumber[i] - '0';
    for (char c : keypad[num]) {
        if (node->children.count(c) != 0) {
            checkForWords(node->children[c], phoneNumber, i + 1, words);
        }
    }
}
#pragma clang diagnostic pop

__attribute__((unused)) vector<string> filterNames(const string& phoneNumber, const vector<string>& words) {
    PhoneToWordTrie trie;
    for (const auto& word : words) {
        trie.insert(word);
    }
    unordered_set<string> good_words;
    for (size_t i = 0; i < phoneNumber.size(); i++) {
        checkForWords(trie.root, phoneNumber, i, good_words);
    }
    return vector<string>(good_words.begin(), good_words.end());
}


#endif //TRIEDS_PHONETOWORDTRIE_H