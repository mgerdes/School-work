/*
 * Name : Michael Gerdes
 * Date : February 20, 2016
 * Class : Non-Linear Data Structures
 *
 * This file is the code for the implementation of the MultiCharacterHuffman interface.
 *
 * It is similar to the vanilla Huffman class but will allow for k-character strings to be
 * compressed as well, instead of just single characters. 
 * For instance the word 'the' occurs often so this scheme will take that entire word and
 * encode it if it produces a shorter output than encoding each character individually. 
 *
 * All of the file input and output is the same. The huffman tree that it builds is essentially the same.
 * The biggest difference is that I implemented a dynamic programming algorithm here to find the 
 * optimal way of partitioning the input file for encoding. 
 */

#include "multi_character_huffman.h"

/*
 * This intialize from file method is a little different from the other Huffman class.
 * Instead of just getting the frequency counts of single characters, it also gets the frequency
 * counts of each k-length contiguous string.
 * It then uses that frequency table to build the huffman tree.
 */
void MultiCharacterHuffman::initializeFromFile(std::string fileName) 
{
    // Keep track of startTime.
    std::chrono::time_point<std::chrono::system_clock> startTime, endTime;
    startTime = std::chrono::system_clock::now();

    std::ifstream inputFile(fileName, std::ios::binary);

    if (inputFile.fail()) 
    {
        std::cout << "Failed to initialze from file " << fileName << std::endl; 
        return;
    }

    long bytesRead = 0;

    // This array holds each k-length string.
    // For instance strings[0] holds the current 1 length string.
    std::string strings[maxLengthStrings];

    // Initialize the array with strings from the input file.
    for (int i = 0; i < maxLengthStrings; i++)
    {
        char c;
        inputFile.get(c);
        bytesRead++;

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

        bytesRead++;

        // For each string in the strings array we remove the first character,
        // then push the next character onto the back of the string.
        // By doing this for each character in the file, we are able to
        // figure out every k-length string in the file.
        for (int i = 0; i < maxLengthStrings; i++)
        {
            strings[i] = strings[i].substr(1); // Remove first character
            strings[i].push_back(c); // Append current character.

            // Get the huffmanNode corresponding to this string.
            HuffmanNode *node = stringToHuffmanNode[strings[i]];
            if (!node)
            {
                // If it does not exist then create a new one.
                stringToHuffmanNode[strings[i]] = new HuffmanNode(strings[i], i);
            }
            else
            {
                // If it does exist then increase it's frequency.
                node->weight += i;
            }
        }

    }

    // Once we've build the frequency table then create the huffman tree.
    makeHuffmanTree();
    // Then set the codes corresponding to each leaf in the huffman tree. 
    setCodes(root, "");

    inputFile.close();

    // Print out how many bytes were read from the file.
    printf("\nThe initializeFromFile method was run with %s.\n", fileName.c_str());
    printf("Bytes read: %d\n", bytesRead);

    // Calculate time it took to run and print out that time.
    endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> duration = endTime - startTime;
    printf("Elapsed time: %.3f seconds\n", duration.count());
}

/*
 * Method for creating the huffman tree is the exact same.
 */
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

/*
 * Encode file is quite different. This is because multiple characters may be grouped
 * together now to be encoded.
 * To find the optimal way of grouping together characters I implemented a Dynamic Programming
 * algorithm.
 * Once this task is completed though, then the actuall process of outputting the optimal encodings
 * to the file is exactly the same.
 */
void MultiCharacterHuffman::encodeFile(std::string decodedFileName, std::string encodedFileName)
{
    // Keep track of startTime.
    std::chrono::time_point<std::chrono::system_clock> startTime, endTime;
    startTime = std::chrono::system_clock::now();

    std::ifstream decodedFile(decodedFileName, std::ios::binary);
    std::string file((std::istreambuf_iterator<char>(decodedFile)),
            std::istreambuf_iterator<char>());

    /*
     * Below is the DP algorithm for finding the optimal partitioning of the input file.
     *
     * minCodeLength[i] represents minimum number of bytes needed to represent the file 
     * starting at the i'th byte. For example minCodeLength[file.length()-1] would be
     * whatever the number of bytes are needed to encode the last character, because
     * that's the only option. Also minCodeLength[0] is the output size of the entire file.
     */
    unsigned int *minCodeLength = new unsigned int[file.length()];
    /*
     * bestLength[i] represents the optimal number of characters to group together if starting
     * at the i'th character. For example bestLength[file.length()-1] = 1, because the only
     * option is to group together just that last character (if your starting there).
     */
    unsigned int *bestLength = new unsigned int[file.length() + 1];

    // This value just signifies when the end of the array is. No length can be -1.
    bestLength[file.length()] = -1;

    // The two base cases (explained above).
    minCodeLength[file.length() - 1] = stringToHuffmanCode[file.substr(file.length() - 1, 1)]->length();
    bestLength[file.length() - 1] = 1;

    // Now we start at the second to last character of the file and keep decreasing until the beginning.
    // We then keep looking to find a better minCodeLength if starting at i.
    for (int i = file.length() - 2; i >= 0; i--)
    {
        minCodeLength[i] = UINT_MAX; // Start with the max value, this will get overwritten.

        // Look at each k-length string starting at i.
        // Then check if it's better than any other.
        for (int j = 1; j < maxLengthStrings + 1; j++)
        {
            if (i + j > file.length())
            {
                break;
            }
            // The cost of starting at i and including j characters is calculated here.
            int c = minCodeLength[i + j] + stringToHuffmanCode[file.substr(i, j)]->length();

            // If that cost is better than one previously found then overwrite it.
            if (c < minCodeLength[i])
            {
                minCodeLength[i] = c;
                bestLength[i] = j;
            }
        }
    }
    // By now the algorithm has completed and we know the optimal way of grouping together characters
    // to produce the smallest output file.
    // The running time of the algorithm isn't that bad either. I think it's the O(n*k). Where n is the size
    // of the file and k is the the maxLength of a grouping. So if k is kept relativley small then it's
    // essentially linear time.

    std::ofstream encodedFile(encodedFileName, std::ios::binary);

    // This code outputs the optimal encoding. 
    // It is very similar to the other Huffman's code, but it uses the previously created
    // arrays from the DP algorithm to find the next string to encode.
    int currentBitPosition = 0;
    char outputChar = 0;
    int currentPosition = 0;
    while (bestLength[currentPosition] != -1) // -1 was set previously to signify the end of the array.
    {
        // The optimal string to encode starts at currentPosition and goes to bestLength[currentPosition]
        std::string *code = stringToHuffmanCode[file.substr(currentPosition, bestLength[currentPosition])];

        // Output this string to the file.
        for (int j = 0; j < code->length(); j++)
        {
            if (currentBitPosition == 8) 
            {
                encodedFile.put(outputChar);
                outputChar = 0;
                currentBitPosition = 0; 
            }

            if (code->at(j) == '1')
            {
                outputChar |= 1 << currentBitPosition;
            }

            currentBitPosition++;
        }

        currentPosition = currentPosition + bestLength[currentPosition];
    }

    // Need to pad the last bit with the length7NonLeafCode. 
    // Same thing in other huffman.
    int bitsLeftToFill = 8 - currentBitPosition; 
    for (int i = 0; i < bitsLeftToFill; i++)
    {
        if (length7NonLeafCode.at(i) == '1')
        {
            outputChar |= 1 << currentBitPosition;
        }
        currentBitPosition++;
    }

    encodedFile.put(outputChar);

    // Clean up.
    encodedFile.close();
    decodedFile.close();

    long bytesRead = file.length(), bytesOutput = minCodeLength[0] / 8 + 1; // + 1 for the last byte.

    // Print out how many bytes were read and output.
    printf("\n");
    printf("The encoder encoded %s and placed it in %s.\n", decodedFileName.c_str(), encodedFileName.c_str());
    printf("Bytes read: %d\nBytes output: %d\nLevel of compression: %.3f\n", 
            bytesRead, bytesOutput, (double) bytesOutput / bytesRead);

    // Calculate time it took to run and print out that time.
    endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> duration = endTime - startTime;
    printf("Elapsed time: %.3f seconds\n", duration.count());
}

/*
 * The decode method is essentially the same. All it does is look to find
 * an encoded string in the tree, and then output the decoded string once it
 * finds it. Just like the single character huffman.
 */
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

/*
 * The set codes method is also essentially the same.
 */
void MultiCharacterHuffman::setCodes(HuffmanNode *node, std::string currentCode) 
{
    if (!node->leftChild && !node->rightChild)
    {
        stringToHuffmanCode[node->str] = new std::string(currentCode);
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
