//
// Created by Ryan.Zurrin001 on 1/7/2022.
//

#ifndef TRIEDS_PREFIXTRIE_H
#define TRIEDS_PREFIXTRIE_H
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <memory>

using namespace std;

class trieNode {
public:
    char data;
    unordered_map<char, std::shared_ptr<trieNode>> children;
    bool isTerminal;
    explicit trieNode(char data) {
        this->data = data;
        this->isTerminal = false;
    }
};

class __attribute__((unused)) PrefixTrie {
    // use smart pointers to make a root node
    std::shared_ptr<trieNode> root;
    static void search_helper(PrefixTrie t, string doc, int i, unordered_map<string, bool>& map);
public:
    PrefixTrie();
    ~PrefixTrie();

    __attribute__((unused)) std::shared_ptr<trieNode> getRoot();

    __attribute__((unused)) void setRoot(std::unique_ptr<trieNode> root_);
    __attribute__((unused)) void insert(const std::string& word);
    __attribute__((unused)) bool search(const std::string& word);

    __attribute__((unused)) static void documentSearch(const std::string& document, std::vector<std::string>& words);

    __attribute__((unused)) bool startsWith(const std::string& prefix);

    __attribute__((unused)) bool endsWith(const std::string& suffix);
    __attribute__((unused)) void print();
};



PrefixTrie::PrefixTrie() {
    root = std::make_unique<trieNode>('\0');
}

PrefixTrie::~PrefixTrie() = default;

void PrefixTrie::search_helper(PrefixTrie t, string doc, int i,
                               unordered_map<string, bool> &map) {
    // make a trieNode pointer
    auto temp = t.getRoot();
    for (int j = i; j < doc.length(); j++) {
        char ch = doc[j];
        if (temp->children.count(ch) == 0) {
            return;
        }
        temp = temp->children[ch];
        if (temp->isTerminal) {
            string out = doc.substr(i, j - i + 1);
            map[out] = true;
        }
    }
}

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

__attribute__((unused)) void PrefixTrie::documentSearch(const std::string &document,
                                vector<std::string> &words) {
    // 1. create a trie of words
    PrefixTrie trie;
    for (const auto &word : words) {
        trie.insert(word);
    }
    unordered_map<string, bool> map;
    for (int i = 0; i < document.length(); i++) {
        search_helper(trie, document, i, map);
    }
    for ( const auto& w : words) {
        if (map[w]) {
            cout << w << " : True" << endl;
        } else {
            cout << w << " : False" << endl;
        }
    }
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

__attribute__((unused)) bool PrefixTrie::endsWith(const string &suffix) {
    trieNode *current = root.get();
    for (char c : suffix) {
        if (current->children.count (c) == 0) {
            return false;
        }
        current = current->children[c].get();
    }
    return current->isTerminal;
}

#endif //TRIEDS_PREFIXTRIE_H
