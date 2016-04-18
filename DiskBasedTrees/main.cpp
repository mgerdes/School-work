#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>

#include "DiskBasedTree.h"
#include "AVLTree.h"
#include "BTree.h"

std::string fileName = "shakespeare-back.txt";
double timeToReadInFile;

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


void analyzeTree(DiskBasedTree &tree)
{
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

            tree.insert(chari);

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

    tree.printResults();

    endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedTime = endTime - startTime;

    double runTime = elapsedTime.count() - timeToReadInFile;

    std::cout << "Run time - " << runTime << std::endl;
}

int main() 
{
    AVLTree avlTree; 
    BTree bTree;

    setTimeToReadInFile();

    analyzeTree(avlTree);
    std::cout << std::endl;
    analyzeTree(bTree);
}
