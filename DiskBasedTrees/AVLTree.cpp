/*
 * File Name: AVLTree.cpp
 * Name: Michael Gerdes
 * Date: 4/19/2016
 * Class: Linear Data Structures
 *
 * This file is the implementation of the Disk Based AVL Tree
 */

#include "AVLTree.h"

AVLTree::AVLTree() 
{
    // Set rootNode to null.
    rootNode = 0;

    // Zero out all the statistics.
    numNodes = 0;
    numTotalKeys = 0;
    numUniqueKeys = 0;
    numFileReads = 0;
    numFileWrites = 0;
    
    // Open up the input and output files.
    inputFile.open("tree.bin", std::ios::binary);
    outputFile.open("tree.bin", std::ios::binary);

    // Do some error checking.
    if (inputFile.fail()) {
        std::cout << "Problem opening input file\n";
    }
    if (outputFile.fail()) {
        std::cout << "Problem openeing output file\n";
    }
}

/*
 * This method fixes the height for the node given.
 */
void AVLTree::fixHeight(AVLTreeNode &node)
{
    // Get the height of the leftChild.
    int leftHeight = 0;
    if (node.leftChild != 0) 
    {
        AVLTreeNode temp;
        readNodeFromFile(temp, node.leftChild);
        leftHeight = temp.height;
    }

    // Get the height of the rightChild.
    int rightHeight = 0;
    if (node.rightChild != 0) {
        AVLTreeNode temp;
        readNodeFromFile(temp, node.rightChild);
        rightHeight = temp.height;
    }

    // Update the given nodes height.
    if (leftHeight > rightHeight)
    {
        node.height = leftHeight + 1;
    }
    else
    {
        node.height = rightHeight + 1;
    }

    // Save the node to the file.
    writeNodeToFile(node);
}

/*
 * Method returns the balanceFactor of the node.
 */
int AVLTree::balanceFactor(AVLTreeNode &node)
{
    // Get the height of the leftChild.
    int leftHeight = 0;
    if (node.leftChild != 0)
    {
        AVLTreeNode temp;
        readNodeFromFile(temp, node.leftChild);
        leftHeight = temp.height;
    }

    // Get the height of the rightChild.
    int rightHeight = 0;
    if (node.rightChild != 0) {
        AVLTreeNode temp;
        readNodeFromFile(temp, node.rightChild);
        rightHeight = temp.height;
    }

    // Balance factor is the leftHeight - rightHeight.
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
 * This rightRotate is the same as the books.
 *
 * It assumes that node1 and node2 are already set.
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

    // Fix the root if needed.
    if (rootNode == node1.id) 
    {
        rootNode = node2.id;
    }

    // Fix up the heights
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
 * The leftRotate is the same as the books.
 *
 * It assumes that node1 and node2 are already set.
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

    // Fix up the root of the tree if needed.
    if (rootNode == node1.id) 
    {
        rootNode = node2.id;
    }

    // Fix the heights of the nodes
    fixHeight(node1);
    fixHeight(node2);
}

/*
 * This method fixes up the tree if needed.
 *
 * It assumes that node1, node2, and node3 are already set.
 */
void AVLTree::fixTree() 
{
    // While we are not at the top of the tree.
    while (node1.id) 
    {
        // Fix the height of the tree if it changed.
        fixHeight(node1);

        // If the balanceFactor of the node is more than 2 then there is a problem, so we fix it.
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
                 *
                 * Fix up the right-right case.
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
                 *        
                 * Fix up the left-right case.
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
                 *
                 * Fix up the right-right case.
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
                 * Fix up the right-left case.
                 */      
                node1 = node2;
                node2 = node3;
                rightRotate();

                readNodeFromFile(node1, node2.parent);
                leftRotate();
            }
            return;
        }

        // Change up all the nodes to go higher up into the tree.
        node3 = node2;
        node2 = node1;
        if (node2.parent == 0) {
            return;
        }
        readNodeFromFile(node1, node2.parent);
    }
}

/*
 * AVL Insert first does the "dumb" vaniilla insert and then calls 
 * the fix tree function to fix an inbalances.
 */
void AVLTree::insert(std::string data) 
{
    numTotalKeys++;
    numUniqueKeys++;

    // Set the data to be the root.
    if (!rootNode) 
    {
        rootNode = 1;

        setUpNewAVLTreeNode(node1, data);
        writeNodeToFile(node1);

        return;
    }

    // Either find the string in the tree, or find where
    // the string belongs in the tree and put it there.
    // Then fix the tree up.
    int currentNode = rootNode;
    while(true) 
    {
        readNodeFromFile(node1, currentNode);

        int compare = data.compare(std::string(node1.data));
        if (compare == 0) 
        {
            // Found the nood in the tree so so just increment it's count.
            node1.count++;
            writeNodeToFile(node1);
            // Decrement the numUniqueKeys because this key is not unique.
            numUniqueKeys--;
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
                // Found where to place the node.
                // Put it there and then fix up the tree.
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
                // Found where to place the node.
                // Put it there and then fix up the tree.
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

/*
 * Returns the height of the tree rooted at nodeId.
 * Height of the tree is the 1 + max(height(leftTree), height(rightTree));
 */
int AVLTree::heightHelper(int nodeId) 
{
    readNodeFromFile(node1, nodeId);
    AVLTreeNode currentNode = node1;

    // Figure out the height of the left tree.
    int leftHeight = 0;
    if (currentNode.leftChild)
    {
        leftHeight = heightHelper(currentNode.leftChild);
    }

    // Figure out the height of the right tree.
    int rightHeight = 0;
    if (currentNode.rightChild) 
    {
        rightHeight = heightHelper(currentNode.rightChild);
    }

    // Return 1 + the larger of the left and right heights.
    if (leftHeight > rightHeight) 
    {
        return leftHeight + 1;
    }
    else
    {
        return rightHeight + 1;
    }
}

/*
 * Returns the height of the tree.
 */
int AVLTree::height() 
{
    // No root means the height is 0.
    if (!rootNode)
    {
        return 0; 
    }
    // Just call heightHelper with the rootNode.
    return heightHelper(rootNode);
}

/*
 * Prints the entire subtree rooted at the input node.
 */
void AVLTree::listHelper(int nodeId) 
{
    readNodeFromFile(node1, nodeId);
    AVLTreeNode currentNode = node1;

    // First, list the left tree.
    if (currentNode.leftChild) 
    {
        listHelper(currentNode.leftChild);
    }

    // Print the current value.
    std::cout << "Data = " << std::string(currentNode.data) << ", Count= " << currentNode.count << std::endl;

    // Finally, list the right tree.
    if (currentNode.rightChild) 
    {
        listHelper(currentNode.rightChild);
    }
}

/*
 * Lists each of the items in the tree.
 */
void AVLTree::list() 
{
    // If there is no rootNode then there is nothing to list.
    if (!rootNode) 
    {
        return;
    }
    // Simply pass rootNode into listHelper.
    listHelper(rootNode);
}

/*
 * Returns the count of the key in the tree.
 */
int AVLTree::count(std::string data) 
{
    // If there is no root node then the key is not in the tree.
    if (!rootNode) 
    {
        return 0;
    }

    // Here we just traverse the tree until we find the key and
    // then return the count of that node.
    int currentNode = rootNode;
    while(true) 
    {
        readNodeFromFile(node1, currentNode);

        int compare = data.compare(std::string(node1.data));
        if (compare == 0) 
        {
            // Found the node.
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
                // Could not find the node.
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
                // Could not find the node.
                return 0;
            }
        }
    }
}

/*
 * Writes a node to the file.
 */
void AVLTree::writeNodeToFile(AVLTreeNode &node) 
{
    numFileWrites++;
    outputFile.seekp((node.id - 1) * sizeof(AVLTreeNode));
	outputFile.write((char*)(&node), sizeof(AVLTreeNode)); 
	outputFile.flush();
}

/*
 * Reads a node from the file.
 */
void AVLTree::readNodeFromFile(AVLTreeNode &node, int id) 
{
    // Small optimization to return a node already read and in memory
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

/*
 * Sets up a new AVL Tree Node.
 * Simply sets each of the variables for the node
 */
void AVLTree::setUpNewAVLTreeNode(AVLTreeNode &node, std::string data) 
{
    node.id = numNodes + 1;
    strcpy(node.data, data.c_str());
    node.count = 1;
    node.height = 0;
    node.parent = 0;
    node.leftChild = 0;
    node.rightChild = 0;
    numNodes++;
}

/*
 * Print the results for the tree.
 */
void AVLTree::printResults()
{
    std::cout << "--- AVL Tree Results ---\n";
    std::cout << "Number of File Reads: " << numFileReads << std::endl;
    std::cout << "Number of File Writes: " << numFileWrites << std::endl;
    std::cout << "Height: " << height() << std::endl;
    std::cout << "Number of Nodes: " << numNodes << std::endl;
    std::cout << "Number of Total Keys Inserted: " << numTotalKeys << std::endl;
    std::cout << "Number of Unique Keys Inserted: " << numUniqueKeys << std::endl;
    //list();
}
