#include <iostream>

#include "trie.h"

const std::string DicPath = "Dic.txt";
const std::string inputPath = "input.txt";
const std::string outputPath = "output.txt";
int main(int argc, char const* argv[])
{
    Trie trie;
    trie.init();
    trie.buildTreeFromList(DicPath);

    trie.solve(inputPath, outputPath);
    return 0;
}