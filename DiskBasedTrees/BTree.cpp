#include "BTree.h"

BTree::BTree() 
{
    inputFile.open("tree.bin", std::ios::binary);
    outputFile.open("tree.bin", std::ios::binary);

    if (inputFile.fail()) 
    {
        std::cout << "Problem opening input file\n";
    }
    if (outputFile.fail()) 
    {
        std::cout << "Problem openeing output file\n";
    }

    numFileWrites = 0;
    numFileReads = 0;
    numNodes = 0;
    numTotalKeys = 0;
    numUniqueKeys = 0;

    allocateNode(rootNode);
    writeNodeToFile(rootNode);
}

int BTree::heightHelper(int id)
{
    if (id == 0) 
    {
        return 0;
    }

    int largestChildHeight = 0;

    BTreeNode node;
    readNodeFromFile(node, id);

    for (int i = 1; i <= node.numKeys + 1; i++) 
    {
        int h = heightHelper(node.children[i]);
        if (h > largestChildHeight)
        {
            largestChildHeight = h;
        }
    }

    return largestChildHeight + 1;
}

int BTree::height()
{
    return heightHelper(rootNode.id);
}

int BTree::count(std::string key)
{
    int index;
    BTreeNode node;
    
    findNode(node, index, key, rootNode.id);

    if (index != 0) 
    {
        return node.counts[index];
    }
    else
    {
        return 0;
    }
}

void BTree::listHelper(int id) 
{
    if (id == 0) 
    {
        return;
    }

    BTreeNode node;
    readNodeFromFile(node, id);

    for (int i = 1; i <= node.numKeys; i++) 
    {
        listHelper(node.children[i]);
        std::cout << node.keys[i] << std::endl;
    }
    listHelper(node.children[node.numKeys + 1]);
}

void BTree::list() 
{
    if (rootNode.numKeys == 0) {
        return;
    }
    listHelper(rootNode.id);
}

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
    for (int i = 0; i < 2 * TREE_DEGREE; i++) {
        node.counts[i] = 0;
        node.children[i] = 0;
    }
    node.children[2 * TREE_DEGREE] = 0;
    numNodes++;
}

void BTree::readNodeFromFile(BTreeNode &node, int id) 
{
    numFileReads++;
	inputFile.seekg((id - 1) * sizeof(BTreeNode));
	inputFile.read((char*)(&node), sizeof(BTreeNode));
}

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

void BTree::findNode(BTreeNode &node, int &index, std::string key, int nodeId)
{
    if (nodeId == 0) 
    {
        index = 0;
        return;
    }

    BTreeNode x;
    readNodeFromFile(x, nodeId);

    int i = 1;
    while (i <= x.numKeys && key > std::string(x.keys[i]))
    {
        i++;
    }
    if (i <= x.numKeys && key == std::string(x.keys[i]))
    {
        index = i;
        node = x;
        return;
    }
    else
    {
        findNode(node, index, key, x.children[i]);
    }
}
