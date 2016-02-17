#ifndef HUFFMAN
#define HUFFMAN

#include <string>
#include <fstream>

#include "huffman_node.h"
#include "priority_queue.h"

class Huffman
{
    private: 
        HuffmanNode *root;
        HuffmanNode charToNode[256];
        std::string charToCode[256];

        bool isLength7NonLeafCodeSet = false;
        std::string length7NonLeafCode;

        void createHuffmanTree();

        void setCodes(HuffmanNode *node, std::string currentCode);

    public:
        Huffman();

        ~Huffman();

        void initializeFromFile(std::string fileName);

        void encodeFile(std::string decodedFileName, std::string encodedFileName);

        void decodeFile(std::string encodedFileName, std::string decodedFileName);
};

#endif // HUFFMAN
