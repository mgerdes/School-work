/*
 * Name : Michael Gerdes
 * Date : February 20, 2016
 * Class : Non-Linear Data Structures
 *
 * This file only contains main, which kicks everything off.
 */

#include "huffman.h"
#include "multi_character_huffman.h"

int main() 
{
    Huffman tree;
    tree.initializeFromFile("resources/shakespeare.txt");
    tree.encodeFile("resources/shakespeare.txt", "resources/enc");
    tree.decodeFile("resources/enc", "resources/dec");

    MultiCharacterHuffman tree2;
    tree2.initializeFromFile("resources/shakespeare.txt");
    tree2.encodeFile("resources/shakespeare.txt", "resources/enc2");
    tree2.decodeFile("resources/enc2", "resources/dec2");
    return 0;
}
