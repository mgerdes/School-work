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
        HuffmanNode **charToNode;
        std::string **charToCode;
        std::string *length7NonLeafCode;

        void createHuffmanTree();

        void setCodes(HuffmanNode *node, std::string currentCode);

        void cleanUp();

    public:
        Huffman();

        ~Huffman();

        void initializeFromFile(std::string fileName);

        void encodeFile(std::string decodedFileName, std::string encodedFileName);

        void decodeFile(std::string encodedFileName, std::string decodedFileName);
};

#endif // HUFFMAN
