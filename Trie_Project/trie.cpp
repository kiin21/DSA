#include "trie.h"

#include <iostream>
#include <fstream>

/**
 * @brief Initializes the Trie by creating a new root node and setting all children pointers to nullptr.
 */
void Trie::init()
{
    root = new TrieNode();
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        root->children[i] = nullptr;
    }
}

/**
 * @brief Inserts a word into the trie.
 *
 * @param word The word to be inserted.
 */
void Trie::insert(std::string word)
{
    TrieNode* cur = root;
    for (char c : word)
    {
        int index = c - 'a';
        if (cur->children[index] == nullptr)
        {
            cur->children[index] = new TrieNode();
        }
        cur = cur->children[index];
    }
    cur->isEndOfWord = true;
    cur->word = word;
}

/**
 * @brief Searches for a given key in the Trie.
 *
 * @param key The key to search for.
 * @return true if the key is found in the Trie, false otherwise.
 */
bool Trie::search(std::string key)
{
    TrieNode* cur = root;
    for (char c : key)
    {
        int index = c - 'a';
        if (cur->children[index] == nullptr)
        {
            return false;
        }
        cur = cur->children[index];
    }
    return cur->isEndOfWord == true;
}

/**
 * @brief Performs a depth-first search on the Trie and prints all valid words.
 *
 * @param node The current node in the Trie.
 */
void Trie::dfs_print(TrieNode* node)
{
    if (node == nullptr)
        return;

    if (node->isEndOfWord)
    {
        std::cout << node->word << "\n";
    }

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        dfs_print(node->children[i]);
    }
}

/**
 * @brief Finds all keys in the Trie that have the given prefix.
 *
 * @param prefix The prefix to search for.
 */
void Trie::findPrefix(std::string prefix)
{
    TrieNode* cur = root;
    for (char c : prefix)
    {
        int index = c - 'a';
        if (cur->children[index] == nullptr)
        {
            std::cout << "Not found any key has prefix " << prefix << "\n";
            return;
        }
        cur = cur->children[index];
    }
    dfs_print(cur);
}

/**
 * @brief Finds the longest prefix of a given key in the Trie.
 *
 * @param key The key to find the longest prefix for.
 */
void Trie::longestPrefix(std::string key)
{
    TrieNode* cur = root;
    std::string prefix = "";
    for (char c : key)
    {
        int index = c - 'a';
        if (cur->children[index] == nullptr)
        {
            break;
        }
        cur = cur->children[index];
        prefix += c;
    }
    std::cout << "The longest prefix of " << key << " is " << prefix << "\n";
}

/**
 * @brief Counts the number of non-null child nodes of a given TrieNode.
 *
 * @param node The TrieNode for which to count the child nodes.
 * @return The number of non-null child nodes.
 */
int Trie::countChild(TrieNode* node)
{
    int count = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (node->children[i] != nullptr)
        {
            count++;
        }
    }
    return count;
}

/**
 * @brief Deletes a word from the Trie.
 *
 * This function deletes the specified word from the Trie data structure.
 * If the word is not found in the Trie, it prints a message indicating that the word was not found.
 *
 * @param key The word to be deleted from the Trie.
 */
void Trie::deleteWord(std::string key)
{
    TrieNode** cur = &root;
    TrieNode** parent = nullptr;
    for (char c : key)
    {
        int index = c - 'a';
        if ((*cur)->children[index] == nullptr)
        {
            std::cout << "Not found " << key << "\n";
            return;
        }
        if (countChild(*cur) > 1 && countChild((*cur)->children[index]) == 1)
            parent = &((*cur)->children[index]);
        cur = &((*cur)->children[index]);
    }
    if (countChild(*cur) > 0) // if *cur is not a leaf, simply mark it as not the end of word
    {
        (*cur)->isEndOfWord = false;
    }
    else // *cur is leaf
    {    // if *cur is root, delete all children from parent
        delete* cur;
        *cur = nullptr;
        if (parent && *parent)
        {
            clear(*parent);
        }
    }
}

/**
 * @brief Builds a trie tree from a list of words in a file.
 *
 * @param path The path to the file containing the list of words.
 */
void Trie::buildTreeFromList(std::string path)
{
    std::ifstream file(path, std::ios::in);
    std::string word;
    while (file >> word)
    {
        insert(word);
    }
    file.close();
}

/**
 * @brief Clears the trie by deleting all nodes and setting the root to nullptr.
 *
 * @param root The root node of the trie.
 */
void Trie::clear(TrieNode*& root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (root->children[i] != nullptr)
        {
            clear(root->children[i]);
        }
    }
    delete root;
    root = nullptr;
}

/**
 * @brief Performs a depth-first search on the Trie to find all valid words based on character counts.
 *
 * @param node The current node in the Trie.
 * @param cnt A vector representing the count of each character in the alphabet.
 * @param index The index of the current character in the alphabet.
 * @param res A vector to store the valid words found during the search.
 */
void Trie::dfs(TrieNode* node, std::vector<int>& cnt, int index, std::vector<std::string>& res)
{
    if (node == nullptr)
        return;

    if (cnt[index] < 0) // if this character is not in list or exceed the number of it in list
        return;

    if (node->isEndOfWord) // if there is a word in the Trie
    {
        if (node->word.size() >= 3)
            res.push_back(node->word);
    }
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (node->children[i] != nullptr)
        {
            cnt[i]--;
            dfs(node->children[i], cnt, i, res);
            cnt[i]++;
        }
    }
}

/**
 * @brief Solves the problem of finding all valid words made from a list of characters.
 *
 * @param inputPath The path to the input file.
 * @param outputPath The path to the output file.
 */
void Trie::solve(std::string inputPath, std::string outputPath)
{
    std::ifstream fin(inputPath, std::ios::in);
    std::ofstream fout(outputPath, std::ios::out);
    std::vector<std::string> res;
    std::string s;
    std::vector<int> cnt(26, 0);
    std::getline(fin, s);
    for (char c : s)
    {
        if (c != ' ')
            cnt[c - 'a']++;
    }

    Trie::dfs(Trie::root, cnt, 0, res);
    fout << res.size() << "\n";
    for (auto it : res)
    {
        if (it != res.back())
            fout << it << "\n";
        else
            fout << it;
    }
    fin.close();
    fout.close();
}