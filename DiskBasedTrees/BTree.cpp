/*
 * File Name: BTree.cpp
 * Name: Michael Gerdes
 * Date: 4/19/2016
 * Class: Linear Data Structures
 *
 * This file is the implementation for the Disk Based BTree
 */

#include "BTree.h"

/*
 * Constructor for the BTree
 */
BTree::BTree() 
{
    // Open up the input and output files.
    inputFile.open("tree.bin", std::ios::binary);
    outputFile.open("tree.bin", std::ios::binary);

    // Do some error checking.
    if (inputFile.fail()) 
    {
        std::cout << "Problem opening input file\n";
        char c;
        std::cin.get(c);
    }
    if (outputFile.fail()) 
    {
        std::cout << "Problem opening output file\n";
        char c;
        std::cin.get(c);
    }

    // Zero out all the statistics.
    numFileWrites = 0;
    numFileReads = 0;
    numNodes = 0;
    numTotalKeys = 0;
    numUniqueKeys = 0;

    // Allocate the rootNode and write it to the file.
    allocateNode(rootNode);
    writeNodeToFile(rootNode);
}

/*
 * Helps find the height of the tree.
 */
int BTree::heightHelper(int id)
{
    // If the node is null then it's height is 0.
    if (id == 0) 
    {
        return 0;
    }

    BTreeNode node;
    readNodeFromFile(node, id);

    // The height of the tree is now 1 + height(leftMostNode).
    return 1 + heightHelper(node.children[1]);
}

/*
 * Returns the height of the tree.
 */
int BTree::height()
{
    // Call heightHelper with the rootNode's id.
    return heightHelper(rootNode.id);
}

/*
 * Finds the count of a key in the tree.
 */
int BTree::count(std::string key)
{
    int index;
    BTreeNode node;
    
    // First found the node in the tree.
    findNode(node, index, key, rootNode.id);

    if (index != 0) 
    {
        // We found the node so return its count.
        return node.counts[index];
    }
    else
    {
        // We could not find the node so return 0.
        return 0;
    }
}

/*
 * Function helps to list each key in the tree.
 */
void BTree::listHelper(int id) 
{
    // If the node is null then return.
    if (id == 0) 
    {
        return;
    }

    BTreeNode node;
    readNodeFromFile(node, id);

    for (int i = 1; i <= node.numKeys; i++) 
    {
        // Print each key to the left.
        listHelper(node.children[i]);

        // Print the current key.
        std::cout << node.keys[i] << std::endl;
    }

    // Print each key to the far right.
    listHelper(node.children[node.numKeys + 1]);
}

/*
 * Lists each key in the tree.
 */
void BTree::list() 
{
    // Simply calls the helper using the root
    listHelper(rootNode.id);
}

/*
 * Function inserts the key into a non-full node.
 * It is the same function from the book.
 */
void BTree::insertNonFull(BTreeNode &x, std::string key) 
{
    int i = x.numKeys;
    if (x.isLeaf)
    {
        while (i >= 1 && key < std::string(x.keys[i])) 
        {
            strcpy(x.keys[i+1], x.keys[i]);
            x.counts[i+1] = x.counts[i];
            i--;
        }

        strcpy(x.keys[i+1], key.c_str());
        x.counts[i+1]++;
        x.numKeys++; 
        writeNodeToFile(x);
    }
    else 
    {
        while (i >= 1 && key < std::string(x.keys[i])) 
        {
            i--;
        }
        i++;

        BTreeNode y;
        readNodeFromFile(y, x.children[i]);

        if (y.numKeys == 2 * TREE_DEGREE - 1) 
        {
            splitChild(x, i);
            if (key > std::string(x.keys[i]))
            {
                i++;
            }
        }

        BTreeNode z;
        readNodeFromFile(z, x.children[i]);

        insertNonFull(z, key);
    }
}

/*
 * Function inserts a key into the tree.
 * It is the same function from the book.
 */
void BTree::insert(std::string key) 
{
    numTotalKeys++;

    BTreeNode node;
    int index;

    findNode(node, index, key, rootNode.id);

    if (index != 0) 
    {
        node.counts[index]++;
        return;
    }

    numUniqueKeys++;

    int rootId = rootNode.id;
    if (rootNode.numKeys == 2 * TREE_DEGREE - 1)
    {
        BTreeNode s;
        allocateNode(s);

        rootNode = s;
        rootNode.isLeaf = false;
        rootNode.children[1] = rootId;

        splitChild(rootNode, 1);
        insertNonFull(rootNode, key);
    } 
    else
    {
        insertNonFull(rootNode, key);
    }
}

/*
 * Function splits a node in the tree.
 * It is the same from the book.
 */
void BTree::splitChild(BTreeNode &x, int i) 
{
    BTreeNode z;
    allocateNode(z);

    BTreeNode y;
    readNodeFromFile(y, x.children[i]);

    z.isLeaf = y.isLeaf;
    z.numKeys = TREE_DEGREE - 1;

    for (int j = 1; j <= TREE_DEGREE - 1; j++) 
    {
        strcpy(z.keys[j], y.keys[j + TREE_DEGREE]);
        z.counts[j] = y.counts[j + TREE_DEGREE];
    }

    if (!y.isLeaf) 
    {
        for (int j = 1; j <= TREE_DEGREE; j++) 
        {
            z.children[j] = y.children[j + TREE_DEGREE];
        }
    }
    y.numKeys = TREE_DEGREE - 1;

    for (int j = x.numKeys + 1; j >= i + 1; j--) 
    {
        x.children[j+1] = x.children[j];
    }
    x.children[i+1] = z.id;

    for (int j = x.numKeys; j >= i; j--) 
    {
        strcpy(x.keys[j+1], x.keys[j]);
        x.counts[j+1] = x.counts[j];
    }
    strcpy(x.keys[i], y.keys[TREE_DEGREE]);
    x.counts[i] = y.counts[TREE_DEGREE];
    x.numKeys++;

    writeNodeToFile(y);
    writeNodeToFile(z);
    writeNodeToFile(x);
}

/*
 * Write a node to the file.
 */
void BTree::writeNodeToFile(BTreeNode &node) 
{
    numFileWrites++;
    outputFile.seekp((node.id - 1) * sizeof(BTreeNode));
	outputFile.write((char*)(&node), sizeof(BTreeNode)); 
	outputFile.flush();
}

/*
 * Allocate a node, and set up all of it's attributes.
 */
void BTree::allocateNode(BTreeNode &node) 
{
    node.id = numNodes + 1;
    node.numKeys = 0;
    node.isLeaf = true;
    for (int i = 0; i < 2 * TREE_DEGREE; i++) {
        node.counts[i] = 0;
        node.children[i] = 0;
    }
    node.children[2 * TREE_DEGREE] = 0;
    numNodes++;
}

/*
 * Given an id, read that node from the file.
 */
void BTree::readNodeFromFile(BTreeNode &node, int id) 
{
    numFileReads++;
	inputFile.seekg((id - 1) * sizeof(BTreeNode));
	inputFile.read((char*)(&node), sizeof(BTreeNode));
}

/*
 * Print the results for the tree.
 */
void BTree::printResults()
{
    std::cout << "--- B-Tree Analysis ---\n";
    std::cout << "Number of File Reads: " << numFileReads << std::endl;
    std::cout << "Number of File Writes: " << numFileWrites << std::endl;
    std::cout << "Height: " << height() << std::endl;
    std::cout << "Number of Nodes: " << numNodes << std::endl;
    std::cout << "Number of Total Keys Inserted: " << numTotalKeys << std::endl;
    std::cout << "Number of Unique Keys Inserted: " << numUniqueKeys << std::endl;
    //list();
}

/*
 * Finds the node with the key in the tree.
 * It also gives you the index that the key is at.
 *
 * You have to pass in a reference to the node and index.
 */
void BTree::findNode(BTreeNode &node, int &index, std::string key, int nodeId)
{
    if (nodeId == 0) 
    {
        // Could not find the key.
        index = 0;
        return;
    }

    BTreeNode x;
    readNodeFromFile(x, nodeId);

    // Look at each key in the node.

    int i = 1;
    while (i <= x.numKeys && key > std::string(x.keys[i]))
    {
        i++;
    }
    if (i <= x.numKeys && key == std::string(x.keys[i]))
    {
        // Found the node so set the input references.
        index = i;
        node = x;
        return;
    }
    else
    {
        // Look for the node in the children nodes.
        findNode(node, index, key, x.children[i]);
    }
}
