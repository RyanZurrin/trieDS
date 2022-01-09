#include <iostream>
#include "PrefixTrie.h"
#include "SuffixTrie.h"
#include "BinaryTrie.h"
#include "Trie.h"
using namespace std;
int main() {
    // Create a new PrefixTrie
    vector<string> input = {"goo", "gle", "google", "le", "googly", "ly", "g", "googoole"};
    vector<string> result = googlyStrings(input);
    for (const auto& i : result) {
        cout << i << endl;
    }


    return 0;
}
