/*
 * File Name: BTree.h
 * Name: Michael Gerdes
 * Date: 4/19/2016
 * Class: Linear Data Structures
 *
 * This file is the interface for the Disk Based BTree
 */

#include <string.h>
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "DiskBasedTree.h"

// Constant for the degree of the tree.
#define TREE_DEGREE 12

/*
 * BTreeNode is pretty simple.
 * It's the same node that the book uses.
 * There is also a counts array which stores 
 * the count of each key in the node.
 */
struct BTreeNode 
{
    int id;

    int numKeys;
    char keys[2 * TREE_DEGREE][50];
    int counts[2 * TREE_DEGREE];

    int children[2 * TREE_DEGREE + 1];

    bool isLeaf;
};

/*
 * This BTree is an implementation of the DiskBasedTree 
 */
class BTree : public DiskBasedTree 
{
    private:
        // Keep the rootNode in memory.
        BTreeNode rootNode;

        // Store some statistics for the tree.
        unsigned int numNodes, numTotalKeys, numUniqueKeys;
        unsigned int numFileWrites, numFileReads;

        // Need an input and output file.
        std::ifstream inputFile;
        std::ofstream outputFile;

        // Lots of helper functions for the BTree.
        void splitChild(BTreeNode &node, int i);

        void writeNodeToFile(BTreeNode &node);

        void readNodeFromFile(BTreeNode &node, int id);

        void allocateNode(BTreeNode &node);

        void insertNonFull(BTreeNode &node, std::string key);

        void listHelper(int id);
        
        int heightHelper(int id);

        void findNode(BTreeNode &node, int &index, std::string key, int nodeId);
    public:
        BTree();

        // BTree implements each of the methods from the DiskBasedTree interface.
        void insert(std::string key);

        int count(std::string key);

        void list();

        int height();

        void printResults();
};
