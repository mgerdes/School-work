/*
 * Name : Michael Gerdes
 * Date : February 20, 2016
 * Class : Non-Linear Data Structures
 *
 * This files contains the definition of a HuffmanNode. 
 */

#ifndef HUFFMAN_NODE
#define HUFFMAN_NODE

#include <string>

struct HuffmanNode 
{
    // This str member is used for the multiCharacterHuffman.
    std::string str;

    // This is the character that corresponds to the node.
    unsigned char ch; 

    // The weight of the node is essentially how many times it's character occurs.
    int weight;

    // Two points to reach the left and right children.
    HuffmanNode *leftChild;
    HuffmanNode *rightChild;

    // Theres a few different constructors which are convenient in varying cirumstances.
    HuffmanNode()
        : weight(0), leftChild(NULL), rightChild(NULL) { };

    HuffmanNode(char ch)
        : ch(ch), weight(0), leftChild(NULL), rightChild(NULL) { };

    HuffmanNode(std::string str, int weight)
        : str(str), weight(weight), leftChild(NULL), rightChild(NULL) { };

    HuffmanNode(int weight, HuffmanNode *leftChild, HuffmanNode *rightChild)
        : weight(weight), leftChild(leftChild), rightChild(rightChild) { };

    ~HuffmanNode()
    {
        // When deleting we only delete nodes that are not leaves.
        // This is because the leaves are not allocated on the heap, they
        // are allocated on the stack when the Huffman class is constructed.
        if (leftChild && leftChild->leftChild)
        {
            delete leftChild;                 
        }
        if (rightChild && rightChild->rightChild)
        {
            delete rightChild;
        }
    }
};

#endif // HUFFMAN_NODE
