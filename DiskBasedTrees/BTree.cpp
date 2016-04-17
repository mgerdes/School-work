#include <string.h>
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>

#define TREE_DEGREE 3

struct BTreeNode 
{
    int id;

    int numKeys;
    char keys[2 * TREE_DEGREE][50];

    int children[2 * TREE_DEGREE + 1];

    bool isLeaf;
};

class BTree 
{
    private:
        BTreeNode rootNode, x, y, z;

        int numNodes;
        int numFileWrites, numFileReads;

        std::ifstream inputFile;
        std::ofstream outputFile;

        void splitChild(BTreeNode &node, int i);

        void writeNodeToFile(BTreeNode &node);

        void readNodeFromFile(BTreeNode &node, int id);

        void allocateNode(BTreeNode &node);

        void insertNonFull(BTreeNode &node, std::string key);
    public:
        BTree();

        void insert(std::string key);
};

BTree::BTree() 
{
    inputFile = std::ifstream("tree.bin", std::ios::binary);
    outputFile = std::ofstream("tree.bin", std::ios::binary);

    if (inputFile.fail()) {
        std::cout << "Problem opening input file\n";
    }
    if (outputFile.fail()) {
        std::cout << "Problem openeing output file\n";
    }

    numFileWrites = 0;
    numFileReads = 0;
    numNodes = 0;

    rootNode.isLeaf = true;
    rootNode.numKeys = 0;
    writeNodeToFile(rootNode);
}

void BTree::insertNonFull(BTreeNode &node, std::string key) 
{
    int i = node.numKeys;
    if (x.isLeaf)
    {
        while (i >= 1 && key < std::string(x.keys[i])) 
        {
            strcpy(x.keys[i+1], x.keys[i]);
            i--;
        }

        strcpy(x.keys[i+1], key.c_str());
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
        readNodeFromFile(y, x.children[i]);
        if (y.numKeys == 2 * TREE_DEGREE - 1) 
        {
            splitChild(x, i);
            if (key > std::string(x.keys[i]))
            {
                i++;
            }
        }
        insertNonFull(x, key);
    }
}

void BTree::insert(std::string key) 
{
    BTreeNode r = rootNode;
    if (r.numKeys == 2 * TREE_DEGREE - 1)
    {
        allocateNode(x);
        rootNode = x;
        x.isLeaf = false;
        x.numKeys = 0;
        x.children[0] = r.id;
        splitChild(x, 0);
        insertNonFull(x, key);
    } 
    else
    {
        insertNonFull(r, key);
    }
}

void BTree::splitChild(BTreeNode &node, int i) 
{
    allocateNode(z);
    readNodeFromFile(y, z.children[i]);

    z.isLeaf = y.isLeaf;
    z.numKeys = TREE_DEGREE - 1;

    for (int j = 0; j < TREE_DEGREE - 1; j++) 
    {
        strcpy(z.keys[j], y.keys[j + TREE_DEGREE]);
    }

    if (!y.isLeaf) 
    {
        for (int j = 0; j < TREE_DEGREE; j++) 
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
    }
    strcpy(x.keys[i], y.keys[TREE_DEGREE]);
    x.numKeys = x.numKeys + 1;

    writeNodeToFile(y);
    writeNodeToFile(z);
    writeNodeToFile(x);
}

void BTree::writeNodeToFile(BTreeNode &node) 
{
    numFileWrites++;
    outputFile.seekp((node.id - 1) * sizeof(BTreeNode));
	outputFile.write((char*)(&node), sizeof(BTreeNode)); 
	outputFile.flush();
}

void BTree::allocateNode(BTreeNode &node) 
{
    node.id = numNodes + 1;
    node.numKeys = 0;
    node.isLeaf = true;
    numNodes++;
}

void BTree::readNodeFromFile(BTreeNode &node, int id) 
{
    if (id == x.id) {
        node = x;
        return;
    }
    if (id == y.id) {
        node = y;
        return;
    }
    if (id == z.id) {
        node = z;
        return;
    }

    numFileReads++;
	inputFile.seekg((id - 1) * sizeof(BTreeNode));
	inputFile.read((char*)(&node), sizeof(BTreeNode));
}


int main() 
{
    return 0;
}
