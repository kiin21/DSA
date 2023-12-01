#pragma once

#define ALPHABET_SIZE 26

#include <string>
#include <vector>
struct TrieNode
{
    TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord = false;
    std::string word = "";
};
struct Trie
{
    TrieNode* root = nullptr;

    void init();
    int countChild(TrieNode*);
    void insert(std::string);
    bool search(std::string);
    void clear(TrieNode*&);
    void buildTreeFromList(std::string);
    void dfs_print(TrieNode*);
    void findPrefix(std::string);
    void longestPrefix(std::string);
    void deleteWord(std::string);
    void dfs(TrieNode*, std::vector<int>&, int, std::vector<std::string>&);
    void solve(std::string, std::string);
};