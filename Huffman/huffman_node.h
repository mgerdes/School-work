#ifndef HUFFMAN_NODE
#define HUFFMAN_NODE

#include "iostream"

struct HuffmanNode 
{
    std::string str;
    unsigned char ch; 
    int weight;
    HuffmanNode *leftChild;
    HuffmanNode *rightChild;

    HuffmanNode(char ch)
        : ch(ch), weight(0), leftChild(NULL), rightChild(NULL) { };

    HuffmanNode(std::string str, int weight)
        : str(str), weight(weight), leftChild(NULL), rightChild(NULL) { };

    HuffmanNode(int weight, HuffmanNode *leftChild, HuffmanNode *rightChild)
        : weight(weight), leftChild(leftChild), rightChild(rightChild) { };

    ~HuffmanNode()
    {
        if (leftChild) {
            delete leftChild;
        }
        if (rightChild) {
            delete rightChild;
        }
    }
};

#endif // HUFFMAN_NODE
