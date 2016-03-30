#include <iostream>
#include <fstream>

#include "AVL.h"
#include "RedBlackTree.h"
#include "BinaryTree.h"

void analyzeAVLTree() {
    AVLTree avlTree;

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
        return;
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

            avlTree.insert(chari);

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

    std::cout << "--- Analysis of AVL Tree ---\n";
    std::cout << "Height: " << avlTree.height() << std::endl;
    std::cout << "Number of BF Changes: " << avlTree.numBFChanges << std::endl;
    std::cout << "Number of Comparisons: " << avlTree.numComparisons << std::endl;
    std::cout << "Number of Pointer Changes: " << avlTree.numPointerChanges << std::endl;
    std::cout << "Number of Items: " << avlTree.itemsInTree() << std::endl;
    std::cout << "Unique Number of Items: " << avlTree.uniqueItemsInTree() << std::endl;
    std::cout << std::endl;
}

void analyzeRedBlackTree() {
    RedBlackTree redBlackTree;

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
        return;
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

            redBlackTree.insert(chari);

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

    std::cout << "--- Analysis of Red Black Tree ---\n";
    std::cout << "Height: " << redBlackTree.height() << std::endl;
    std::cout << "Number of Re-Colorings: " << redBlackTree.numReColorings << std::endl;
    std::cout << "Number of Comparisons: " << redBlackTree.numComparisons << std::endl;
    std::cout << "Number of Pointer Changes: " << redBlackTree.numPointerChanges << std::endl;
    std::cout << "Number of Items: " << redBlackTree.itemsInTree() << std::endl;
    std::cout << "Unique Number of Items: " << redBlackTree.uniqueItemsInTree() << std::endl;
    std::cout << std::endl;
}

void analyzeBinaryTree() {
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
        return;
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


    std::cout << "--- Analysis of Vanilla Binary Tree ---\n";
    std::cout << "Height: " << binaryTree.height() << std::endl;
    std::cout << "Number of Comparisons: " << binaryTree.numComparisons << std::endl;
    std::cout << "Number of Pointer Changes: " << binaryTree.numPointerChanges << std::endl;
    std::cout << "Number of Items: " << binaryTree.itemsInTree() << std::endl;
    std::cout << "Unique Number of Items: " << binaryTree.uniqueItemsInTree() << std::endl;
}

int main() {
    analyzeAVLTree();
    analyzeRedBlackTree();
    analyzeBinaryTree();

    return 0;
}

