#ifndef HUFFMAN_NODE
#define HUFFMAN_NODE

#include "iostream"

struct HuffmanNode 
{
    unsigned char ch; 
    int weight;
    HuffmanNode *leftChild;
    HuffmanNode *rightChild;

    HuffmanNode(char ch)
        : ch(ch), weight(0), leftChild(0), rightChild(0) { };

    HuffmanNode(int weight, HuffmanNode *leftChild, HuffmanNode *rightChild)
        : weight(weight), leftChild(leftChild), rightChild(rightChild) { };
};

#endif // HUFFMAN_NODE
