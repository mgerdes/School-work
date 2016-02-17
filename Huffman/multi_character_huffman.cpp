#include "multi_character_huffman.h"

MultiCharacterHuffman::MultiCharacterHuffman()
    : stringToHuffmanNode(1000000), stringToHuffmanCode(1000000) { }

void MultiCharacterHuffman::initializeFromFile(std::string fileName) 
{
    std::ifstream inputFile(fileName, std::ios::binary);

    if (inputFile.fail()) 
    {
        std::cout << "Failed to initialze from file " << fileName << std::endl; 
        return;
    }

    std::string strings[maxLengthStrings];

    for (int i = 0; i < maxLengthStrings; i++)
    {
        char c;
        inputFile.get(c);

        for (int j = 0; j < i + 1; j++)
        {
            strings[maxLengthStrings - j - 1].push_back(c);
        }
    }

    while (true)
    {
        char c;
        inputFile.get(c);

        if (inputFile.eof())
        {
            break;
        }

        for (int i = 0; i < maxLengthStrings; i++)
        {
            strings[i] = strings[i].substr(1);
            strings[i].push_back(c);

            HuffmanNode *node = stringToHuffmanNode[strings[i]];
            if (!node)
            {
                stringToHuffmanNode[strings[i]] = new HuffmanNode(strings[i], i);
            }
            else
            {
                node->weight += i;
            }
        }

    }

    makeHuffmanTree();
    setCodes(root, "");

    inputFile.close();
}

void MultiCharacterHuffman::makeHuffmanTree()
{
    PriorityQueue priorityQueue = PriorityQueue(stringToHuffmanNode.size());

    for (auto bucket : stringToHuffmanNode)
    {
        priorityQueue.insert(bucket.second);
    }

    while (priorityQueue.getSize() > 1) 
    {
        HuffmanNode *n1 = priorityQueue.extractMin();
        HuffmanNode *n2 = priorityQueue.extractMin();
        priorityQueue.insert(new HuffmanNode(n1->weight + n2->weight, n1, n2));
    }
    root = priorityQueue.extractMin();
}

void MultiCharacterHuffman::encodeFile(std::string decodedFileName, std::string encodedFileName)
{
    std::ifstream decodedFile(decodedFileName, std::ios::binary);
    std::string file((std::istreambuf_iterator<char>(decodedFile)),
            std::istreambuf_iterator<char>());

    unsigned long long *minCodeLength = new unsigned long long[file.length()];
    unsigned long long *bestLength = new unsigned long long[file.length() + 1];

    bestLength[file.length()] = -1;

    minCodeLength[file.length() - 1] = stringToHuffmanCode[file.substr(file.length() - 1, 1)]->length();
    bestLength[file.length() - 1] = 1;

    for (int i = file.length() - 2; i >= 0; i--)
    {
        minCodeLength[i] = ULLONG_MAX;

        for (int j = 1; j < maxLengthStrings + 1; j++)
        {
            if (i + j > file.length())
            {
                break;
            }
            int c = minCodeLength[i + j] + stringToHuffmanCode[file.substr(i, j)]->length();
            if (c < minCodeLength[i])
            {
                minCodeLength[i] = c;
                bestLength[i] = j;
            }
        }
    }

    std::ofstream encodedFile(encodedFileName, std::ios::binary);

    int lengthOnes = 0;
    int lengthTwos = 0;
    int lengthThrees = 0;
    int lengthFours = 0;

    int currentBitPosition = 0;
    char outputChar = 0;
    int currentPosition = 0;
    while (bestLength[currentPosition] != -1)
    {
        std::string *code = stringToHuffmanCode[file.substr(currentPosition, bestLength[currentPosition])];

        if (bestLength[currentPosition] == 1)
        {
            lengthOnes++;
        }
        if (bestLength[currentPosition] == 2)
        {
            lengthTwos++;
        }
        if (bestLength[currentPosition] == 3)
        {
            lengthThrees++;
        }
        if (bestLength[currentPosition] == 4)
        {
            lengthFours++;
        }

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

        currentPosition = currentPosition + bestLength[currentPosition];
    }

    std::cout << lengthOnes << " - " << lengthTwos << " - " << lengthThrees << " - " << lengthFours << std::endl;

    encodedFile.close();
    decodedFile.close();
}

void MultiCharacterHuffman::decodeFile(std::string encodedFileName, std::string decodedFileName)
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
                for (int i = 0; i < currentNode->str.length(); i++)
                {
                    decodedFile.put(currentNode->str[i]);
                }
                currentNode = root;
            }
        }
    }
}

void MultiCharacterHuffman::setCodes(HuffmanNode *node, std::string currentCode) 
{
    if (!node->leftChild && !node->rightChild)
    {
        stringToHuffmanCode[node->str] = new std::string(currentCode);
    }
    else
    {
        currentCode.push_back('0');
        setCodes(node->leftChild, currentCode);
        currentCode.pop_back();

        currentCode.push_back('1');
        setCodes(node->rightChild, currentCode);
        currentCode.pop_back();
    }
}
