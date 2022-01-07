#include <iostream>
#include "PrefixTrie.h"
#include "SuffixTrie.h"
using namespace std;
int main() {
    // Create a new PrefixTrie
    string input = "hello";
    string suffixes[] = {"lo", "ell", "hel", "ello", "hello"};

    SuffixTrie t;
    t.insert(input);
    for(const auto& sf : suffixes) {
        if(t.search(sf)) {
            cout << sf << " is in the trie" << endl;
        } else {
            cout << sf << " is not in the trie" << endl;
        }
    }

    return 0;
}
