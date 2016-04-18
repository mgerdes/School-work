/*
 * File Name: AVLTree.h
 * Name: Michael Gerdes
 * Date: 4/19/2016
 * Class: Linear Data Structures
 *
 * This file is the interface for the Disk Based AVL Tree
 */

#include <string.h>
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "DiskBasedTree.h"

/*
 * AVLTreeNode is pretty simple.
 * parent, leftChild, and rightChild are now ids, not pointers.
 */
struct AVLTreeNode 
{
    int id;

    char data[50];
    int count;
    int height;

    int parent;
    int leftChild;
    int rightChild;
};

/*
 * The AVLTree is an implementation of the DiskBasedTree.
 */
class AVLTree : public DiskBasedTree 
{
    private:
        // Need an inputFile and an outputFile.
        std::ifstream inputFile;
        std::ofstream outputFile;

        // Here are the three nodes to keep in memory.
        AVLTreeNode node1, node2, node3;

        // Store the id of the rootNode.
        int rootNode;

        // Store some statistics for the tree.
        unsigned int numNodes, numTotalKeys, numUniqueKeys;
        unsigned int numFileWrites, numFileReads;

        // Lots of helper methods below.
        void setUpNewAVLTreeNode(AVLTreeNode &node, std::string data);

        void writeNodeToFile(AVLTreeNode &node); 

        void readNodeFromFile(AVLTreeNode &node, int id); 

        void leftRotate();

        void rightRotate();

        void fixTree();

        void listHelper(int nodeId);

        int heightHelper(int nodeId);

        void fixHeight(AVLTreeNode &node);

        int balanceFactor(AVLTreeNode &node);
    public:
        AVLTree();

        // AVLTree implements each of the methods from the DiskBasedTree interface.
        void insert(std::string data);

        int count(std::string data);

        void list();

        int height();

        void printResults();
};
