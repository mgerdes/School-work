#include "multi_character_huffman.h"

MultiCharacterHuffman::MultiCharacterHuffman()
{

}

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

            if (stringToHuffmanNode.count(strings[i]) == 0)
            {
                stringToHuffmanNode[strings[i]] = new HuffmanNode(strings[i], i);
            }
            else
            {
                stringToHuffmanNode[strings[i]]->weight += i;
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
    unsigned long long *parentPointer = new unsigned long long[file.length()];

    minCodeLength[file.length() - 1] = stringToHuffmanCode[file.substr(file.length() - 1, 1)]->length();
    parentPointer[file.length() - 1] = -1;

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
                parentPointer[i] = i + j;
                minCodeLength[i] = c;
            }
        }
    }

    std::cout << minCodeLength[0] << std::endl;

    decodedFile.close();
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
