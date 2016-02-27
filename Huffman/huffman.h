/*
 * Name : Michael Gerdes
 * Date : February 20, 2016
 * Class : Non-Linear Data Structures
 *
 * This file defines the interface for the Huffman class. 
 */

#ifndef HUFFMAN
#define HUFFMAN

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

#include "huffman_node.h"
#include "priority_queue.h"

class Huffman
{
    private: 
        HuffmanNode *root;

        // This is essentially a map from each character to a HuffmanNode corresponding to that character.
        // It has 256 slots because there are 256 characters.
        HuffmanNode charToNode[256]; 

        // This a map from each character to a string corresponding to that characters encoding.
        // It has 256 slots because there are 256 characters.
        std::string charToCode[256];

        // The length-7 non-leaf code is a code for a node which is at least 7 bits long, and
        // is for a non-leaf node.
        // This is needed to pad out the final character encoded.
        std::string length7NonLeafCode;

        // Here is a bool to make sure the code is only set once.
        bool isLength7NonLeafCodeSet; 

        // Here is the private helper method which creates the huffmanTree 
        void createHuffmanTree();

        // Here is the private helper method which sets the encodings for each character.
        // It's recursive and can be kicked off by calling it with the root of the huffman tree
        // and the empty string.
        void setCodes(HuffmanNode *node, std::string currentCode);

    public:
        Huffman();

        ~Huffman();

        // This method creates the huffman tree based on a given file.
        // It must be called before the encodeFile or decodeFile methods can be called.
        void initializeFromFile(std::string fileName);

        // This method encodes a given file. 
        // It must be called after initializeFromFile has been called.
        void encodeFile(std::string decodedFileName, std::string encodedFileName);

        // This method decodes a give file.
        // It must be called after initializeFromFile has been called.
        void decodeFile(std::string encodedFileName, std::string decodedFileName);
};

#endif // HUFFMAN
