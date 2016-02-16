#include "huffman.h"

Huffman::Huffman() 
    : length7NonLeafCode(NULL),
    charToNode(new HuffmanNode*[256]),
    charToCode(new std::string*[256])
{ }

void Huffman::initializeFromFile(std::string fileName)
{
    for (int i = 0; i < 256; i++) 
    {
        charToNode[i] = new HuffmanNode((unsigned char) i);
    }

    std::ifstream inputFile(fileName, std::ios::binary);

    if (inputFile.fail()) 
    {
    }

    while (!inputFile.eof())
    {
        char c;
        inputFile.get(c);
        charToNode[c]->weight++;
    }
    inputFile.close();

    createHuffmanTree();
    setCodes(root, new std::string(""));

}

void Huffman::encodeFile(std::string decodedFileName, std::string encodedFileName)
{
    std::ifstream decodedFile(decodedFileName, std::ios::binary);
    std::ofstream encodedFile(encodedFileName, std::ios::binary);

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

        std::string *code = charToCode[inputChar];

        for (int j = 0; j < code->length(); j++)
        {
            int currentBytePosition = currentBitPosition >> 3;         
            int currentBytesBitPosition = currentBitPosition % 8;

            if (currentBytesBitPosition == 0 && currentBitPosition != 0) 
            {
                encodedFile.put(outputChar);
                outputChar = 0;
            }

            if (code->at(j) == '1')
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
        if (length7NonLeafCode->at(i) == '1')
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
    std::ifstream encodedFile(encodedFileName, std::ios::binary);
    std::ofstream decodedFile(decodedFileName, std::ios::binary);

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
}

void Huffman::createHuffmanTree()
{
    PriorityQueue priorityQueue = PriorityQueue(charToNode, 256);
    while (priorityQueue.getSize() > 1) 
    {
        HuffmanNode *n1 = priorityQueue.extractMin();
        HuffmanNode *n2 = priorityQueue.extractMin();
        priorityQueue.insert(new HuffmanNode(n1->weight + n2->weight, n1, n2));
    }
    root = priorityQueue.extractMin();
}

void Huffman::setCodes(HuffmanNode *node, std::string *currentCode) 
{
    if (!node->leftChild && !node->rightChild)
    {
        charToCode[node->ch] = new std::string(*currentCode);
    }
    else
    {
        if (!length7NonLeafCode && currentCode->length() >= 7)
        {
            length7NonLeafCode = new std::string(*currentCode); 
        }

        currentCode->push_back('0');
        setCodes(node->leftChild, currentCode);
        currentCode->pop_back();

        currentCode->push_back('1');
        setCodes(node->rightChild, currentCode);
        currentCode->pop_back();
    }
}