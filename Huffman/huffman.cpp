#include "huffman.h"

Huffman::Huffman() : root(NULL)
{ 
    for (int i = 0; i < 256; i++) 
    {
        charToNode[i].ch = (unsigned char) i;
    }
}

Huffman::~Huffman()
{
    delete root;
}

void Huffman::initializeFromFile(std::string fileName)
{
    for (int i = 0; i < 256; i++)
    {
        charToNode[i].weight = 0;
    }

    std::ifstream inputFile(fileName, std::ios::binary);

    if (inputFile.fail()) 
    {
        std::cout << "Failed to initialze from file " << fileName << std::endl; 
        return;
    }

    while (!inputFile.eof())
    {
        char c;
        inputFile.get(c);
        charToNode[c].weight++;
    }
    inputFile.close();

    createHuffmanTree();
    setCodes(root, "");

    if (!isLength7NonLeafCodeSet)
    {
        length7NonLeafCode = "0000000";
    }
}

void Huffman::encodeFile(std::string decodedFileName, std::string encodedFileName)
{
    if (!root)
    {
        std::cout << "You must first initialize the tree with a file\n";
        return;
    }

    std::ifstream decodedFile(decodedFileName, std::ios::binary);
    if (decodedFile.fail())
    {
        std::cout << "Failed to open file " << decodedFileName << std::endl; 
        return;
    }

    std::ofstream encodedFile(encodedFileName, std::ios::binary);
    if (encodedFile.fail())
    {
        std::cout << "Failed to open file " << encodedFileName << std::endl; 
        return;
    }

    int currentBitPosition = 0;
    char outputChar = 0;
    while(true)
    {
        char inputChar;
        decodedFile.get(inputChar);
        if (decodedFile.eof())
        {
            break;
        }

        std::string code = charToCode[inputChar];
        for (int j = 0; j < code.length(); j++)
        {
            int currentBytePosition = currentBitPosition >> 3;         
            int currentBytesBitPosition = currentBitPosition % 8;

            if (currentBytesBitPosition == 0 && currentBitPosition != 0) 
            {
                encodedFile.put(outputChar);
                outputChar = 0;
            }

            if (code.at(j) == '1')
            {
                outputChar |= 1 << currentBytesBitPosition;
            }

            currentBitPosition++;
        }
    }

    int currentBytePosition = currentBitPosition >> 3;         
    int bitsLeftToFill = 8 - (currentBitPosition % 8);
    for (int i = 0; i < bitsLeftToFill; i++)
    {
        int currentBytesBitPosition = currentBitPosition % 8;
        if (length7NonLeafCode.at(i) == '1')
        {
            outputChar |= 1 << currentBytesBitPosition;
        }
        currentBitPosition++;
    }
    encodedFile.put(outputChar);

    decodedFile.close();
    encodedFile.close();
}

void Huffman::decodeFile(std::string encodedFileName, std::string decodedFileName)
{
    if (!root)
    {
        std::cout << "You must first initialize the tree with a file\n";
        return;
    }

    std::ifstream encodedFile(encodedFileName, std::ios::binary);
    if (encodedFile.fail())
    {
        std::cout << "Failed to open file " << encodedFileName << std::endl; 
        return;
    }

    std::ofstream decodedFile(decodedFileName, std::ios::binary);
    if (decodedFile.fail())
    {
        std::cout << "Failed to open file " << decodedFileName << std::endl; 
        return;
    }

    HuffmanNode *currentNode = root;

    while(true)
    {
        char inputChar;
        encodedFile.get(inputChar);
        if (encodedFile.eof())
        {
            break;
        }

        for (int j = 0; j < 8; j++)
        {
            if ((inputChar & (1 << j)) >> j) 
            {
                currentNode = currentNode->rightChild; 
            }
            else
            {
                currentNode = currentNode->leftChild;
            }

            if (!currentNode->rightChild && !currentNode->leftChild)
            {
                decodedFile.put(currentNode->ch);
                currentNode = root;
            }
        }
    }

    encodedFile.close();
    decodedFile.close();
}

void Huffman::createHuffmanTree()
{
    PriorityQueue priorityQueue = PriorityQueue(256);
    for (int i = 0; i < 256; i++)
    {
        priorityQueue.insert(&charToNode[(unsigned char) i]);
    }
    while (priorityQueue.getSize() > 1) 
    {
        HuffmanNode *n1 = priorityQueue.extractMin();
        HuffmanNode *n2 = priorityQueue.extractMin();
        priorityQueue.insert(new HuffmanNode(n1->weight + n2->weight, n1, n2));
    }
    root = priorityQueue.extractMin();
}

void Huffman::setCodes(HuffmanNode *node, std::string currentCode) 
{
    if (!node->leftChild && !node->rightChild)
    {
        charToCode[node->ch] = currentCode;
    }
    else
    {
        if (!isLength7NonLeafCodeSet && currentCode.length() >= 7)
        {
            isLength7NonLeafCodeSet = true;
            length7NonLeafCode = currentCode; 
        }

        currentCode.push_back('0');
        setCodes(node->leftChild, currentCode);
        currentCode.pop_back();

        currentCode.push_back('1');
        setCodes(node->rightChild, currentCode);
        currentCode.pop_back();
    }
}
