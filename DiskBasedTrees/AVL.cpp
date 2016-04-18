#include <string.h>
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>

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

class AVLTree 
{
    private:
        std::ifstream inputFile;
        std::ofstream outputFile;

        AVLTreeNode node1, node2, node3;

        int rootNode;
        int numberNodes;

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
        int numFileReads, numFileWrites;

        AVLTree();

        void insert(std::string data);

        int count(std::string data);

        void list();

        int height();
};

AVLTree::AVLTree() 
{
    numFileReads = 0;
    numFileWrites = 0;

    rootNode = 0;
    numberNodes = 0;
    
    inputFile = std::ifstream("tree.bin", std::ios::binary);
    outputFile = std::ofstream("tree.bin", std::ios::binary);

    if (inputFile.fail()) {
        std::cout << "Problem opening input file\n";
    }
    if (outputFile.fail()) {
        std::cout << "Problem openeing output file\n";
    }
}

void AVLTree::fixHeight(AVLTreeNode &node)
{
    int leftHeight = 0;
    if (node.leftChild != 0) 
    {
        AVLTreeNode temp;
        readNodeFromFile(temp, node.leftChild);
        leftHeight = temp.height;
    }

    int rightHeight = 0;
    if (node.rightChild != 0) {
        AVLTreeNode temp;
        readNodeFromFile(temp, node.rightChild);
        rightHeight = temp.height;
    }

    if (leftHeight > rightHeight)
    {
        node.height = leftHeight + 1;
    }
    else
    {
        node.height = rightHeight + 1;
    }

    writeNodeToFile(node);
}

int AVLTree::balanceFactor(AVLTreeNode &node)
{
    int leftHeight = 0;
    if (node.leftChild != 0)
    {
        AVLTreeNode temp;
        readNodeFromFile(temp, node.leftChild);
        leftHeight = temp.height;
    }

    int rightHeight = 0;
    if (node.rightChild != 0) {
        AVLTreeNode temp;
        readNodeFromFile(temp, node.rightChild);
        rightHeight = temp.height;
    }

    return leftHeight - rightHeight;
}


/*                                     *
 *          n1               n2        *
 *         /  \             / \        *
 *        n2   D     ->    A   n1      *
 *       / \                  / \      *
 *      A   n3               n3   C    *
 *         / \              / \        *
 *        B   C            B   C       *
 *
 * x must be in node1 and y in node2 to call this method.
 */
void AVLTree::rightRotate() 
{
    node2.parent = node1.parent;
    if (node1.parent) 
    {
        readNodeFromFile(node3, node1.parent);
        if (node3.leftChild == node1.id) 
        {
            node3.leftChild = node2.id;
        } 
        else 
        {
            node3.rightChild = node2.id;
        }
        writeNodeToFile(node3);
    }

    if (node2.rightChild)
    {
        readNodeFromFile(node3, node2.rightChild);
        node3.parent = node1.id;
        writeNodeToFile(node3);
    }
    node1.leftChild = node2.rightChild;

    node1.parent = node2.id;
    node2.rightChild = node1.id;

    if (rootNode == node1.id) 
    {
        rootNode = node2.id;
    }

    fixHeight(node1);
    fixHeight(node2);
}

/*                                      *
 *          n1                 n2       *
 *         /  \               /  \      *
 *        A   n2     ->      n1   C     *
 *           /  \           /  \        *
 *          n3   D         A   n3       *
 *         / \                / \       *
 *        B   C              B   C      *
 *
 * x must be in node1 and y in node2 to call this method.
 */      
void AVLTree::leftRotate() 
{
    node2.parent = node1.parent;
    if (node1.parent) 
    {
        readNodeFromFile(node3, node1.parent);
        if (node3.rightChild == node1.id) 
        {
            node3.rightChild = node2.id;
        } 
        else 
        {
            node3.leftChild = node2.id;
        }
        writeNodeToFile(node3);
    }

    if (node2.leftChild)
    {
        readNodeFromFile(node3, node2.leftChild);
        node3.parent = node1.id;
        writeNodeToFile(node3);
    }
    node1.rightChild = node2.leftChild;

    node1.parent = node2.id;
    node2.leftChild = node1.id;

    if (rootNode == node1.id) 
    {
        rootNode = node2.id;
    }

    fixHeight(node1);
    fixHeight(node2);
}

// assumes node1, 
void AVLTree::fixTree() 
{
    while (node1.id) 
    {
        fixHeight(node1);

        if (abs(balanceFactor(node1)) >= 2) 
        {
            if (node1.leftChild == node2.id && node2.leftChild == node3.id) 
            {
                /*                                                            *
                 *          n1                n2                              *
                 *         /  \             /    \                            *
                 *        n2   D     ->    n3     n1                          *
                 *       /  \             /  \   /  \                         *
                 *      n3   C           A    B C    D                        *
                 *     / \                                                    *
                 *    A   B                                                   *
                 */
                rightRotate();
            } 
            else if (node1.leftChild == node2.id && node2.rightChild == node3.id) 
            {

                /*                                                            *
                 *          n1                  n1                  n3        *
                 *         /  \                /  \               /    \      *
                 *        n2   D     ->       n3   D     ->      n2     n1    *
                 *       / \                 /  \               / \    / \    *
                 *      A   n3              n2   C             A   B  C   D   *
                 *         / \             /  \                               *
                 *        B   C           A    B                              *
                 */      
                node1 = node2;
                node2 = node3;
                leftRotate();
                
                readNodeFromFile(node1, node2.parent);
                rightRotate();
            } 
            else if (node1.rightChild == node2.id && node2.rightChild == node3.id) 
            {
                /*                                                            *
                 *          n1                 n2                             *
                 *         /  \               /  \                            *
                 *        A   n2     ->      n1   n3                          *
                 *           /  \           / \   / \                         *
                 *          B   n3         A   B C   D                        *
                 *             /  \                                           *
                 *            C    D                                          *
                 */      
                leftRotate();
            } 
            else if (node1.rightChild == node2.id && node2.leftChild == node3.id) 
            {
                /*                                                            *
                 *         n1               n1                      n3        *
                 *        /  \             /  \                   /    \      *
                 *       A   n2      ->   A   n3         ->      n1     n2    *
                 *          /  \             /  \               /  \   /  \   *
                 *         n3   D           B   n2             A    B C    D  *
                 *        /  \                 /  \                           *
                 *       B    C               C    D                          *
                 */      
                node1 = node2;
                node2 = node3;
                rightRotate();

                readNodeFromFile(node1, node2.parent);
                leftRotate();
            }
            return;
        }

        node3 = node2;
        node2 = node1;
        if (node2.parent == 0) {
            return;
        }
        readNodeFromFile(node1, node2.parent);
    }
}

void AVLTree::insert(std::string data) 
{
    if (!rootNode) 
    {
        rootNode = 1;

        setUpNewAVLTreeNode(node1, data);
        writeNodeToFile(node1);

        return;
    }

    int currentNode = rootNode;

    while(true) 
    {
        readNodeFromFile(node1, currentNode);

        int compare = data.compare(std::string(node1.data));
        if (compare == 0) 
        {
            node1.count++;
            writeNodeToFile(node1);
            return;
        }
        else if (compare < 0) 
        {
            if (node1.leftChild) 
            {
                currentNode = node1.leftChild;
            }
            else 
            {
                setUpNewAVLTreeNode(node2, data);
                node2.parent = node1.id;
                writeNodeToFile(node2);
                node1.leftChild = node2.id;
                fixHeight(node1);

                node3 = node2;
                node2 = node1;
                if (node2.parent) 
                {
                    readNodeFromFile(node1, node2.parent);
                    fixTree();
                }
                return;
            }
        } 
        else 
        {
            if (node1.rightChild) 
            {
                currentNode = node1.rightChild;
            }
            else 
            {
                setUpNewAVLTreeNode(node2, data);
                node2.parent = node1.id;
                writeNodeToFile(node2);
                node1.rightChild = node2.id;
                fixHeight(node1);

                node3 = node2;
                node2 = node1;
                if (node2.parent) 
                {
                    readNodeFromFile(node1, node2.parent);
                    fixTree();
                }
                return;
            }
        }
    }
}

int AVLTree::heightHelper(int nodeId) 
{
    readNodeFromFile(node1, nodeId);
    AVLTreeNode currentNode = node1;
    
    int leftHeight = 0;
    if (currentNode.leftChild)
    {
        leftHeight = heightHelper(currentNode.leftChild);
    }

    int rightHeight = 0;
    if (currentNode.rightChild) 
    {
        rightHeight = heightHelper(currentNode.rightChild);
    }

    if (leftHeight > rightHeight) 
    {
        return leftHeight + 1;
    }
    else
    {
        return rightHeight + 1;
    }
}

int AVLTree::height() 
{
    if (!rootNode)
    {
        return 0; 
    }
    return heightHelper(rootNode);
}

void AVLTree::listHelper(int nodeId) 
{
    readNodeFromFile(node1, nodeId);
    AVLTreeNode currentNode = node1;

    if (currentNode.leftChild) 
    {
        listHelper(currentNode.leftChild);
    }

    std::cout << "Data = " << std::string(currentNode.data) << ", Balance Factor = " << balanceFactor(currentNode) << std::endl;

    if (currentNode.rightChild) 
    {
        listHelper(currentNode.rightChild);
    }
}

void AVLTree::list() 
{
    if (!rootNode) 
    {
        return;
    }
    listHelper(rootNode);
}

int AVLTree::count(std::string data) 
{
    if (!rootNode) 
    {
        return 0;
    }

    int currentNode = rootNode;

    while(true) 
    {
        readNodeFromFile(node1, currentNode);

        int compare = data.compare(std::string(node1.data));
        if (compare == 0) 
        {
            return node1.count;
        }
        else if (compare < 0) 
        {
            if (node1.leftChild) 
            {
                currentNode = node1.leftChild;
            }
            else 
            {
                return 0;
            }
        } 
        else 
        {
            if (node1.rightChild) 
            {
                currentNode = node1.rightChild;
            }
            else 
            {
                return 0;
            }
        }
    }
}

void AVLTree::writeNodeToFile(AVLTreeNode &node) 
{
    numFileWrites++;
    outputFile.seekp((node.id - 1) * sizeof(AVLTreeNode));
	outputFile.write((char*)(&node), sizeof(AVLTreeNode)); 
	outputFile.flush();
}

void AVLTree::readNodeFromFile(AVLTreeNode &node, int id) 
{
    if (id == node1.id) {
        node = node1;
        return;
    }
    if (id == node2.id) {
        node = node2;
        return;
    }
    if (id == node3.id) {
        node = node3;
        return;
    }

    numFileReads++;
	inputFile.seekg((id - 1) * sizeof(AVLTreeNode));
	inputFile.read((char*)(&node), sizeof(AVLTreeNode));
}

void AVLTree::setUpNewAVLTreeNode(AVLTreeNode &node, std::string data) 
{
    node.id = numberNodes + 1;
    strcpy(node.data, data.c_str());
    node.count = 1;
    node.height = 0;
    node.parent = 0;
    node.leftChild = 0;
    node.rightChild = 0;
    numberNodes++;
}

int main() 
{
    AVLTree tree;

    for (int i = 0; i < 999; i++) {
        std::string s = std::to_string(i);
        tree.insert(s);
    }

    std::cout << "Num file reads: " << tree.numFileReads << std::endl;
    std::cout << "Num file writes: " << tree.numFileWrites << std::endl;
    std::cout << "Height: " << tree.height() << std::endl;

    tree.list();

    return 0;
}
