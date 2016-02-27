#ifndef MULTI_CHARACTER_HUFFMAN
#define MULTI_CHARACTER_HUFFMAN

#include <string>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <unordered_map>
#include <queue>
#include <limits.h>

#include "huffman_node.h"
#include "priority_queue.h"

class MultiCharacterHuffman
{
    private: 
        int maxLengthStrings = 6;

        HuffmanNode *root;

        std::unordered_map<std::string, HuffmanNode *> stringToHuffmanNode;
        std::unordered_map<std::string, std::string *> stringToHuffmanCode;

        void makeHuffmanTree();

        void setCodes(HuffmanNode *node, std::string currentCode);

    public:
        MultiCharacterHuffman() { };

        void initializeFromFile(std::string fileName);

        void encodeFile(std::string decodedFileName, std::string encodedFileName);

        void decodeFile(std::string encodedFileName, std::string decodedFileName);
};

#endif // MULTI_CHARACTER_HUFFMAN
