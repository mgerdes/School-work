#include <string.h>
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "DiskBasedTree.h"

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

class AVLTree : public DiskBasedTree 
{
    private:
        std::ifstream inputFile;
        std::ofstream outputFile;

        AVLTreeNode node1, node2, node3;

        int rootNode;
        unsigned int numKeys, numNodes, numFileWrites, numFileReads;

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

        void insert(std::string data);

        int count(std::string data);

        void list();

        int height();

        void printResults();
};

