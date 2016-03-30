#include <iostream>
#include <fstream>

#include "AVL.h"
#include "RedBlackTree.h"
#include "BinaryTree.h"

int main() {
    AVLTree avlTree;
    RedBlackTree redBlackTree;
    BinaryTree binaryTree;

    char c;
    char chari[50]; // assumes no word is longer than 49 characters
    int iPtr;
    bool isDelimiter = false, wasDelimiter = false;
    for (int i = 0; i < 50; i++) 
    {
        chari[i] = '\0';
    }

    std::ifstream inFile("shakespeare.txt", std::ios::binary);
    if (inFile.fail())
    {
        std::cout << "Unable to open input file\n\n"
            << "Program Exiting\n\nPress ENTER to exit\n";
        std::cin.get(c);
        return 0;
    }
    iPtr = 0;
    inFile.get(c);
    while (!inFile.eof())
    {
        isDelimiter = c == 32 || c == 10 || c == 13 || c == 9 ||
                c == '.' || c == ',' || c == '!' || c == ';' ||
                c == ':' || c == '(' || c == ')';

        if (isDelimiter && !wasDelimiter)
        {
            wasDelimiter = true;

            //insert the shiz
            redBlackTree.insert(chari); 
            avlTree.insert(chari); 
            binaryTree.insert(chari);

            for (int i = 0; i < 50; i++)
            {
                chari[i] = '\0';
            }
            iPtr = 0;
        }
        else if (!isDelimiter)
        {
            chari[iPtr] = c;
            iPtr++;
        }
        else if (isDelimiter && wasDelimiter)
        {
            // do nothing
        }
        wasDelimiter = isDelimiter;
        inFile.get(c);

    }
    inFile.close();

    std::cout << redBlackTree.height() << std::endl;
    std::cout << avlTree.height() << std::endl;
    std::cout << binaryTree.height() << std::endl;

    return 0;
}

