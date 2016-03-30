#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>

#include "AVL.h"
#include "RedBlackTree.h"
#include "BinaryTree.h"

double timeToReadInFile;
std::string fileName;

/*
 * Read through the whole file to get the time it takes to read it in
 */
void setTimeToReadInFile() {
    std::chrono::time_point<std::chrono::system_clock> startTime, endTime;
    startTime = std::chrono::system_clock::now();

    // The below code is from the slides.
    char c;
    char chari[50]; // assumes no word is longer than 49 characters
    int iPtr;
    bool isDelimiter = false, wasDelimiter = false;
    for (int i = 0; i < 50; i++) 
    {
        chari[i] = '\0';
    }

    std::ifstream inFile(fileName, std::ios::binary);
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
            
            // Don't do anything with this string now

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

    endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedTime = endTime - startTime;
    
    // Set the elapsed time and print it out
    timeToReadInFile = elapsedTime.count();

    std::cout << "Time to read in file: " << timeToReadInFile << std::endl;
    std::cout << std::endl;
}

/*
 * Analyze the running of the AVL Tree.
 * It then prints out some stats.
 */
void analyzeAVLTree() {
    std::chrono::time_point<std::chrono::system_clock> startTime, endTime;
    startTime = std::chrono::system_clock::now();

    AVLTree avlTree;

    // The below code is from the slides.
    char c;
    char chari[50]; // assumes no word is longer than 49 characters
    int iPtr;
    bool isDelimiter = false, wasDelimiter = false;
    for (int i = 0; i < 50; i++) 
    {
        chari[i] = '\0';
    }

    std::ifstream inFile(fileName, std::ios::binary);
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

    endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedTime = endTime - startTime;

    // Print out each of the statistics for the AVL Tree
    std::cout << "--- Analysis of AVL Tree ---\n";
    std::cout << "Height: " << avlTree.height() << std::endl;
    std::cout << "Number of BF Changes: " << avlTree.numBFChanges << std::endl;
    std::cout << "Number of Comparisons: " << avlTree.numComparisons << std::endl;
    std::cout << "Number of Pointer Changes: " << avlTree.numPointerChanges << std::endl;
    std::cout << "Number of Items: " << avlTree.itemsInTree() << std::endl;
    std::cout << "Unique Number of Items: " << avlTree.uniqueItemsInTree() << std::endl;
    std::cout << "Time: " << elapsedTime.count() - timeToReadInFile << std::endl;
    std::cout << std::endl;
}

/*
 * Analyze the running of the Red Black Tree.
 * It then prints out some stats.
 */
void analyzeRedBlackTree() {
    std::chrono::time_point<std::chrono::system_clock> startTime, endTime;
    startTime = std::chrono::system_clock::now();

    RedBlackTree redBlackTree;

    // The below code is from the slides.
    char c;
    char chari[50]; // assumes no word is longer than 49 characters
    int iPtr;
    bool isDelimiter = false, wasDelimiter = false;
    for (int i = 0; i < 50; i++) 
    {
        chari[i] = '\0';
    }

    std::ifstream inFile(fileName, std::ios::binary);
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

    endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedTime = endTime - startTime;

    // Print out each of the statistics for the Red Black Tree
    std::cout << "--- Analysis of Red Black Tree ---\n";
    std::cout << "Height: " << redBlackTree.height() << std::endl;
    std::cout << "Number of Re-Colorings: " << redBlackTree.numReColorings << std::endl;
    std::cout << "Number of Comparisons: " << redBlackTree.numComparisons << std::endl;
    std::cout << "Number of Pointer Changes: " << redBlackTree.numPointerChanges << std::endl;
    std::cout << "Number of Items: " << redBlackTree.itemsInTree() << std::endl;
    std::cout << "Unique Number of Items: " << redBlackTree.uniqueItemsInTree() << std::endl;
    std::cout << "Time: " << elapsedTime.count() - timeToReadInFile << std::endl;
    std::cout << std::endl;
}


/*
 * Analyze the running of the Vanilla Binary Tree.
 * It then prints out some stats.
 */
void analyzeBinaryTree() {
    std::chrono::time_point<std::chrono::system_clock> startTime, endTime;
    startTime = std::chrono::system_clock::now();

    BinaryTree binaryTree;

    // The below code is from the slides.
    char c;
    char chari[50]; // assumes no word is longer than 49 characters
    int iPtr;
    bool isDelimiter = false, wasDelimiter = false;
    for (int i = 0; i < 50; i++) 
    {
        chari[i] = '\0';
    }

    std::ifstream inFile(fileName, std::ios::binary);
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

    endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedTime = endTime - startTime;

    // Print out each of the statistics for the Vanilla Binary Tree
    std::cout << "--- Analysis of Vanilla Binary Tree ---\n";
    std::cout << "Height: " << binaryTree.height() << std::endl;
    std::cout << "Number of Comparisons: " << binaryTree.numComparisons << std::endl;
    std::cout << "Number of Pointer Changes: " << binaryTree.numPointerChanges << std::endl;
    std::cout << "Number of Items: " << binaryTree.itemsInTree() << std::endl;
    std::cout << "Unique Number of Items: " << binaryTree.uniqueItemsInTree() << std::endl;
    std::cout << "Time: " << elapsedTime.count() - timeToReadInFile << std::endl;
}

int main() {
    // Set the filename that should be read in.
    fileName = "numbers.txt";

    // First set the time to read in the file.
    setTimeToReadInFile();

    // Then analyze each of the trees.
    analyzeAVLTree();
    analyzeRedBlackTree();
    analyzeBinaryTree();
    return 0;
}

