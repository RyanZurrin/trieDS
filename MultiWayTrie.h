//
// Created by Ryan.Zurrin001 on 1/9/2022.
//

#ifndef TRIEDS_MULTIWAYTRIE_H
#define TRIEDS_MULTIWAYTRIE_H
#include <bits/stdc++.h>
using namespace std;

class mwTrieNode {
public:
    __attribute__((unused)) char c;
    bool isWord;
    unordered_map<char, mwTrieNode*> children;
    explicit mwTrieNode(char c) {
        this->c = c;
        this->isWord = false;
    }
};

class __attribute__((unused)) MultiWayTrie {
public:
    mwTrieNode* root;
    MultiWayTrie() {
        root = new mwTrieNode('\0');
    }

    __attribute__((unused)) void insert(const string& word) const {
        mwTrieNode* curr = root;
        for (char  i : word) {
            if (curr->children.find(i) == curr->children.end()) {
                curr->children[i] = new mwTrieNode(i);
            }
            curr = curr->children[i];
        }
        curr->isWord = true;
    }

    __attribute__((unused)) void deleteWord(const string& word) const {
        mwTrieNode* curr = root;
        for (char  i : word) {
            if (curr->children.find(i) == curr->children.end()) {
                return;
            }
            curr = curr->children[i];
        }
        curr->isWord = false;
    }
    __attribute__((unused)) bool search(const string& word) const {
        mwTrieNode* curr = root;
        for (char  i : word) {
            if (curr->children.find(i) == curr->children.end()) {
                return false;
            }
            curr = curr->children[i];
        }
        return curr->isWord;
    }
    __attribute__((unused)) bool startsWith(const string& prefix) const {
        mwTrieNode* curr = root;
        for (char  i : prefix) {
            if (curr->children.find(i) == curr->children.end()) {
                return false;
            }
            curr = curr->children[i];
        }
        return true;
    }
    __attribute__((unused)) bool contains(const string& word) const {
        mwTrieNode* curr = root;
        for (char  i : word) {
            if (curr->children.find(i) == curr->children.end()) {
                return false;
            }
            curr = curr->children[i];
        }
        return curr->isWord;
    }
    __attribute__((unused)) bool endsWith(const string& suffix) const {
        mwTrieNode* curr = root;
        for (char  i : suffix) {
            if (curr->children.find(i) == curr->children.end()) {
                return false;
            }
            curr = curr->children[i];
        }
        return true;
    }
};

#endif //TRIEDS_MULTIWAYTRIE_H
