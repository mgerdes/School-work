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
    int counts[2 * TREE_DEGREE];

    int children[2 * TREE_DEGREE + 1];

    bool isLeaf;
};

class BTree 
{
    private:
        BTreeNode rootNode;

        int numNodes;

        std::ifstream inputFile;
        std::ofstream outputFile;

        void splitChild(BTreeNode &node, int i);

        void writeNodeToFile(BTreeNode &node);

        void readNodeFromFile(BTreeNode &node, int id);

        void allocateNode(BTreeNode &node);

        void insertNonFull(BTreeNode &node, std::string key);

        void inOrderHelper(int id);
    public:
        int numFileWrites, numFileReads;

        BTree();

        void insert(std::string key);

        void inOrder();
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

    allocateNode(rootNode);
    writeNodeToFile(rootNode);
}

void BTree::inOrderHelper(int id) 
{
    BTreeNode node;
    readNodeFromFile(node, id);

    for (int i = 1; i <= node.numKeys; i++) 
    {
        if (!node.isLeaf) 
        {
            inOrderHelper(node.children[i]);
        }
        std::cout << std::string(node.keys[i]) << std::endl;
    }
    if (!node.isLeaf)
    {
        inOrderHelper(node.children[node.numKeys + 1]);
    }
}

void BTree::inOrder() 
{
    if (rootNode.numKeys == 0) {
        return;
    }
    inOrderHelper(rootNode.id);
}

void BTree::insertNonFull(BTreeNode &x, std::string key) 
{
    for (int i = 1; i <= x.numKeys; i++) {
        if (key == std::string(x.keys[i]))
        {
            x.counts[i]++;
            return;
        }
    }

    int i = x.numKeys;
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

void BTree::insert(std::string key) 
{
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
    }
    strcpy(x.keys[i], y.keys[TREE_DEGREE]);
    x.numKeys++;

    writeNodeToFile(x);
    writeNodeToFile(y);
    writeNodeToFile(z);
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
    for (int i = 0; i < TREE_DEGREE; i++) {
        node.counts[i] = 1;
    }
    numNodes++;
}

void BTree::readNodeFromFile(BTreeNode &node, int id) 
{
    numFileReads++;
	inputFile.seekg((id - 1) * sizeof(BTreeNode));
	inputFile.read((char*)(&node), sizeof(BTreeNode));
}

int main() 
{
    BTree tree;

    for (int i = 999; i >= 0; i--) {
        std::string s = std::to_string(i);
        tree.insert(s);
    }
    std::string s = std::to_string(9);
    tree.insert(s);

    std::cout << "Num file reads: " << tree.numFileReads << std::endl;
    std::cout << "Num file writes: " << tree.numFileWrites << std::endl;

    tree.inOrder();
    //std::cout << "Height: " << tree.height() << std::endl;

    return 0;
}
