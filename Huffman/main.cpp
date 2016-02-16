#include "huffman.h"

int main() 
{
    Huffman tree;
    tree.initializeFromFile("resources/test");
    tree.encodeFile("resources/test", "resources/enc_test");
    tree.decodeFile("resources/enc_test", "resources/dec_test");
    return 0;
}
