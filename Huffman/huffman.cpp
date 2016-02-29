/*
 * Name : Michael Gerdes
 * Date : February 20, 2016
 * Class : Non-Linear Data Structures
 *
 * This file is the code for the implementation of the Huffman interface.
 * It allows the user to input a file to "train" the huffman tree. Then allows the user to
 * input another file to be decoded or encoded. Based on the created huffman tree.
 */

#include "huffman.h"

/*
 * The constructor for the Huffman class sets the root pointer to NULL
 * and initializes the array which converts a char to a Huffman node.
 */
Huffman::Huffman() : root(NULL)
{ 
    for (int i = 0; i < 256; i++) // There are 256 characters. So do this for each character.
    {
        /*
         * For each Huffman node in the array set it's ch member to it's corresponding position in the array.
         * This essentially creates a map from a character to the node with that character.
         * For example charToNode[97] will return the node for the character 'a'. 
         */
        charToNode[i].ch = (unsigned char) i;
    }
}

/*
 * The destructor for the Huffman class simply deletes the root node.
 */
Huffman::~Huffman()
{
    delete root;
}

/*
 * The initializeFromFile method takes in a fileName and creates a frequency table which corresponds to how
 * often each character occurs in the file.
 * It then uses that frequency table to create the corresponding huffman tree.
 * It also sets the encoding string for every character.
 * The method will also print out the number of bytes it read and how long it took to complete (in seconds).
 */
void Huffman::initializeFromFile(std::string fileName)
{
    // Keep track of the start time.
    std::chrono::time_point<std::chrono::system_clock> startTime, endTime;
    startTime = std::chrono::system_clock::now();

    // Create the ifstream corresponding to the given fileName.
    std::ifstream inputFile(fileName, std::ios::binary);

    // Do some error checking to make sure the file is legit.
    if (inputFile.fail()) 
    {
        std::cout << "Failed to initialze from file " << fileName << std::endl; 
        return;
    }

    // Reset each of the nodes weights to 0. The weight corresponds to that characters frequency.
    // The reason this is done here and not in the constructor is because this method may be called
    // a second time, which we would again want the weights to be reset.
    for (int i = 0; i < 256; i++)
    {
        charToNode[i].weight = 0; 
    }

    // Used to keep track of how many bytes are read from the file.
    long bytesRead = 0;

    // This seemingly infinite loop will break when the end of file is reached.
    // It will also read in each character from the file and increase the weight of 
    // the corresponding node by 1. Effectively creating the frequency table.
    while (true)
    {
        char c;
        // Read in the next character.
        inputFile.get(c);

        // Break when we reach the end of the file.
        if (inputFile.eof()) 
        {
            break;
        }
        bytesRead++;

        // Increase the weight of the node that corresponds to that character. 
        charToNode[c].weight++;
    }

    // After creating the frequency table, create the huffman tree.
    createHuffmanTree();

    // After the huffman tree is set then store the encodings for each of the characters.
    // The setCodes method is recursive, so to kick it off start with the root and an empty 
    // string as the code.
    setCodes(root, "");

    // Do some clean up work by closing the input file.
    inputFile.close();

    // Print out how many bytes were read from the file.
    printf("The initializeFromFile method was run with %s.\n", fileName.c_str());
    printf("Bytes read: %d\n", bytesRead);

    // Calculate time it took to run and print out that time.
    endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> duration = endTime - startTime;
    printf("Elapsed time: %.3f seconds\n", duration.count());
}

/*
 * The encodeFile method takes in a decodedFileName and an encodedFileName. 
 * It then encodes the decodedFile and stores the result in the encodedFile.
 * To do this we go through the decodedFile character by character and encode each character, 
 * this encoding is then sent to the encodedFile.
 * Before this is called the initializeFromFile method must have been called by the user.
 * Then it prints out how many bytes it read and output, the level of compression (bytesOutput / bytesRead), 
 * and how long it took to complete (in seconds).
 */
void Huffman::encodeFile(std::string decodedFileName, std::string encodedFileName)
{
    // Keep track of the start time.
    std::chrono::time_point<std::chrono::system_clock> startTime, endTime;
    startTime = std::chrono::system_clock::now();

    // Make sure that the root is not null, if it is then the user did not call the initializeFromFile method.
    if (!root)
    {
        std::cout << "You must first initialize the tree with a file\n";
        return;
    }

    // Get the ifstream for the decodedFile and encodedFile.
    std::ifstream decodedFile(decodedFileName, std::ios::binary);
    std::ofstream encodedFile(encodedFileName, std::ios::binary);

    // Do some error checking on the two files.
    if (decodedFile.fail())
    {
        std::cout << "Failed to open file " << decodedFileName << std::endl; 
        return;
    }
    if (encodedFile.fail())
    {
        std::cout << "Failed to open file " << encodedFileName << std::endl; 
        return;
    }


    // Used to keep track of how many bytes are read and output. 
    long bytesRead = 0, bytesOutput = 0; 

    // I use the following two variables to keep track of the next (encoded) character to output and 
    // the currentBitPosition for that character. We need this information because potentially multiple
    // decoded characters could be encoded and placed in the same output character.
    char outputChar = 0;
    int currentBitPosition = 0;
    
    // This infinite loop breaks when the end of the decoded file is reached.
    while(true)
    {
        // Get the next character from the decodedFile.
        char inputChar;
        decodedFile.get(inputChar);

        // Check if we've reached the end of the file and break if so.
        if (decodedFile.eof())
        {
            break;
        }
        bytesRead++;

        // Here we get the encoding corresponding to the character just extracted from the file.
        std::string code = charToCode[inputChar];
        // This is a string of 1's and 0's, which we now loop through to set each of the corresponding 
        // bits in the character to output next.
        for (int j = 0; j < code.length(); j++)
        {
            // If the currentBitPosition is 8, then that means we've filled up the current outputCharacter,
            // so output it to the encoded file and reset the outputChar and currentBitPosition.
            if (currentBitPosition == 8)  
            {
                encodedFile.put(outputChar);
                outputChar = 0;
                currentBitPosition = 0;
                bytesOutput++;
            }

            // If the characters encoding has a 1 in the current position, then we need to set the 
            // bit in currentBitPosition 
            // for the outputChar to be on.
            if (code.at(j) == '1')
            {
                // Set the bit on by or'ing the outputChar and 1 shifted to the left currentBitPosition times.
                outputChar |= 1 << currentBitPosition;
            }
            // If the characters encoding has a 0 in the current position, then we do not need 
            // to do anything because
            // the outputChar starts with all 0's in it.
            
            currentBitPosition++;
        }
    }

    // The final encoded character to output has not actually been put into the encodedFile yet.
    // This is because we may not have actually filled all of the bits in the last character.
    // If this is the case then we still have to fill those remaining bits and then output the last character. 
    // We use the bits from the length-7 non-leaf encoding to fill them up because this encoding 
    // corresponds to no character. 
    int bitsLeftToFill = 8 - currentBitPosition; 
    for (int i = 0; i < bitsLeftToFill; i++)
    {
        // If this code contains a '1', then set the outputChar's bit to on using the same method shown above. 
        if (length7NonLeafCode.at(i) == '1')
        {
            outputChar |= 1 << currentBitPosition;
        }
        currentBitPosition++;
    }

    // Finally we are ready to safely put the last character into the encodedFile.
    encodedFile.put(outputChar);
    bytesOutput++;

    // Clean things up by closing the two files.
    decodedFile.close();
    encodedFile.close();

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
 * The decodeFile takes in an encodedFileName and a decodedFileName.
 * It then uses the huffman tree to decode the encodedFile and stores the result into the decodedFile.
 * To do this we go through each character in the encodedFile and use the tree to figure out 
 * the corresponding decoded characters.
 * Before this is called the initializeFromFile method must have been called by the user.
 * It will also print out how many bytes it read and input and how long it took to run (in seconds).
 */
void Huffman::decodeFile(std::string encodedFileName, std::string decodedFileName)
{
    // Keep track of the start time.
    std::chrono::time_point<std::chrono::system_clock> startTime, endTime;
    startTime = std::chrono::system_clock::now();

    // Make sure that the root is not null, if it is then the user did not call the initializeFromFile method.
    if (!root)
    {
        std::cout << "You must first initialize the tree with a file\n";
        return;
    }

    // Create ifstream's for both the encoded and decoded files.
    std::ifstream encodedFile(encodedFileName, std::ios::binary);
    std::ofstream decodedFile(decodedFileName, std::ios::binary);

    // Do some error checking on the two files.
    if (encodedFile.fail())
    {
        std::cout << "Failed to open file " << encodedFileName << std::endl; 
        return;
    }
    if (decodedFile.fail())
    {
        std::cout << "Failed to open file " << decodedFileName << std::endl; 
        return;
    }

    // To decode the file we repeatedly get each character from the input file. For each character
    // we then go through each of it's 8 bits, and at a 0 go left in the huffman tree, and at a 1 
    // go right in the huffman tree until we reach a leaf node. Once we reach a leaf we output
    // the chararacter corresponding to that node and reset the currentNode in the huffman tree
    // to be the root.
    
    long bytesRead = 0, bytesOutput = 0;
    
    // We start with the currentNode at the root.
    HuffmanNode *currentNode = root;

    // Loop will break when the end of the encoded file is reached.
    while(true) 
    {
        // Get the next character from the encoded file.
        char inputChar;
        encodedFile.get(inputChar);

        // If we reached the end of the file then break.
        if (encodedFile.eof())
        {
            break;
        }
        bytesRead++;

        // Go through each of the 8 bits in the character we just got from the encoded file.
        for (int j = 0; j < 8; j++)
        {
            // This checks if the j'th bit in the character is a 1 or a 0.
            // It does it by first shifting the inputChar to the left j times.
            // This effectively moves the j'th bit in the input char to now be the first bit.
            // We then and this result with 1 (to 0 out every bit but the first) and check if it's not zero.
            if ((inputChar >> j) & 1) 
            {
                // If the bit is not zero (aka 1) then go right in the tree.
                currentNode = currentNode->rightChild; 
            }
            else
            {
                // Else the bit is 0 and we go left in the tree.
                currentNode = currentNode->leftChild;
            }
            
            // If we reached a leaf (which has no children) then stop and output the char corresponding
            // to the leaf we reached. Then reset the currentNode to be the root to repeat the process.
            if (!currentNode->rightChild && !currentNode->leftChild)
            {
                decodedFile.put(currentNode->ch);
                currentNode = root;
                bytesOutput++;
            }
        }
    }

    // Clean up by closing the two files.
    encodedFile.close();
    decodedFile.close();

    // Print out how many bytes were read and output.
    printf("\n");
    printf("The decoder decoded %s and placed it in %s.\n", encodedFileName.c_str(), decodedFileName.c_str());
    printf("Bytes read: %d\nBytes output: %d\n", 
            bytesRead, bytesOutput, (double) bytesOutput / bytesRead);

    // Calculate time it took to run and print out that time.
    endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> duration = endTime - startTime;
    printf("Elapsed time: %.3f seconds\n", duration.count());
}

/*
 * The createHuffmanTree creates the huffman tree for a previously created frequency table.
 * It works using a priority queue.
 */
void Huffman::createHuffmanTree()
{
    // Create a priority queue with size 256, the number of possible characters.
    PriorityQueue priorityQueue = PriorityQueue(256);

    // Next insert each node into the priority queue.
    for (int i = 0; i < 256; i++)
    {
        priorityQueue.insert(&charToNode[(unsigned char) i]);
    }

    // This loops continuosly until there is only 1 node left in the priority queue.
    // This last remaining node is then known to be the root of the tree.
    while (priorityQueue.getSize() > 1) 
    {
        // Get the two remaining nodes with the smallest frequencies.
        HuffmanNode *n1 = priorityQueue.extractMin();
        HuffmanNode *n2 = priorityQueue.extractMin();

        // Insert a new node which has a weight of the sum of the other two nodes. 
        // Also it has each of the other two nodes as its children.
        priorityQueue.insert(new HuffmanNode(n1->weight + n2->weight, n1, n2));
    }

    // Set the root to be the remaining node.
    root = priorityQueue.extractMin();
}

/*
 * The setCodes method sets the encodings for each of the characters.
 * IT MUST BE CALLED AFTER THE HUFFMAN TREE HAS BEEN CREATED. Because otherwise there is no 
 * way to know the encodings.
 * It does in inorder traversal of the huffman tree to set the encoding for each character.
 */
void Huffman::setCodes(HuffmanNode *node, std::string currentCode) 
{
    // If we reached a leaf (which has no children), then set that nodes characters encoding.
    if (!node->leftChild && !node->rightChild)
    {
        charToCode[node->ch] = currentCode;
    }
    else 
    // If the node is not a leaf then theres no need to set any encoding. Instead we just 
    // keep recursing through the tree.
    {
        // Set the length-7 non-leaf encoding if possible.
        if (!isLength7NonLeafCodeSet && currentCode.length() >= 7)
        {
            isLength7NonLeafCodeSet = true;
            length7NonLeafCode = currentCode; 
        }

        // Before going left append a '0' to the encoding. 
        currentCode.push_back('0');
        setCodes(node->leftChild, currentCode);
        // Now remove the '0' because we finished traversing the nodes left sub-tree.
        currentCode.pop_back();

        // Before going right append a '1' to the encoding. 
        currentCode.push_back('1');
        setCodes(node->rightChild, currentCode);
        // Now remove the '1' because we finished traversing the nodes right sub-tree.
        currentCode.pop_back();
    }
}
