#include "huffman.h"
#include "multi_character_huffman.h"

int main() 
{
    MultiCharacterHuffman newTree;
    newTree.initializeFromFile("resources/shakespeare.txt");
    newTree.encodeFile("resources/shakespeare.txt", "resources/enc");

    Huffman tree;
    tree.initializeFromFile("resources/shakespeare.txt");
    tree.encodeFile("resources/shakespeare.txt", "resources/enc");
    tree.decodeFile("resources/enc", "resources/dec");
    return 0;
}
