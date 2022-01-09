//
// Created by Ryan.Zurrin001 on 1/8/2022.
//

#ifndef TRIEDS_TRIE_H
#define TRIEDS_TRIE_H
#include<bits/stdc++.h>
using namespace std;

class trie_node{
public:
    char ch;
    bool isTerminal;
    unordered_map<char,trie_node*> children;
    explicit trie_node(char ch){
        this->ch = ch;
        isTerminal = false;
    }
};

class Trie{
    trie_node*root;
public:
    Trie(){
        root = new trie_node('\0');
    }
    trie_node *getRoot(){
        return root;
    }
    void insert(const string& s){
        trie_node*temp = root;
        for(char ch : s){
            if(temp->children.count(ch)==0){
                temp->children[ch] = new trie_node(ch);
            }
            temp = temp->children[ch];
        }
        temp->isTerminal = true;
    }
};
bool isGoogly(Trie t,trie_node*root, string s,size_t i,int cnt){
    //entire string is finished
    if(i==s.length()){
        return root->isTerminal and (cnt + 1) >=2;
    }

    char ch = s[i];
    // trie is finished
    if(root->children.count(ch)==0){
        return false;
    }
    root = root->children[ch];
    //current node is terminal
    if(root->isTerminal){
        bool remaining = isGoogly(t,t.getRoot(),s,i+1,cnt+1);
        if(remaining){
            return true;
        }
    }
    return isGoogly(t,root,s,i+1,cnt);
}


vector<string> googlyStrings(vector<string> input) {
    // Write your code here.
    Trie t;

    for(const auto& str:input){
        t.insert(str);
    }
    vector<string> output = {};
    // for every word in the list of strings
    //check if it can be formed using atleast 2 words from the trie

    for(const auto& s : input){
        //cnt how many words are repeated to form a given string
        int cnt = 0;
        trie_node*temp = t.getRoot();
        if(isGoogly(t,temp,s,0,cnt)){
            output.push_back(s);
        }
    }
    return output;
}
#endif //TRIEDS_TRIE_H
