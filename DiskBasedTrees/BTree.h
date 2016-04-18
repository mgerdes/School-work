#include <string.h>
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "DiskBasedTree.h"

#define TREE_DEGREE 12

struct BTreeNode 
{
    int id;

    int numKeys;
    char keys[2 * TREE_DEGREE][50];
    int counts[2 * TREE_DEGREE];

    int children[2 * TREE_DEGREE + 1];

    bool isLeaf;
};

class BTree : public DiskBasedTree 
{
    private:
        BTreeNode rootNode;

        unsigned int numNodes, numTotalKeys, numUniqueKeys;
        unsigned int numFileWrites, numFileReads;

        std::ifstream inputFile;
        std::ofstream outputFile;

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

        void insert(std::string key);

        int count(std::string key);

        void list();

        int height();

        void printResults();
};
