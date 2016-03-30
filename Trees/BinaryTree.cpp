#include "BinaryTree.h"

/*
 * Vanilla insert function.
 * Is the same insert function as the two other
 * trees except it does no fixup after an insert.
 */
void BinaryTree::insert(std::string value) 
{
    // Set this value to be the root.
    if (!root) {
        root = new BinaryTreeNode(value, 0, 0);
        return;
    }

    // Either find the string in the tree, or find where
    // the string belongs in the tree and put it there.
    // Then fix the tree up.
    BinaryTreeNode *currentNode = root;
    while (true) 
    {
        int comparison = value.compare(currentNode->value);
        numComparisons++;
        if (comparison == 0) 
        {
            // Found the node in the tree so just increment its weight.
            currentNode->weight++;
            // We are finished so break
            break;
        } 
        else if (comparison > 0) 
        {
            if (currentNode->rightChild) 
            {
                currentNode = currentNode->rightChild;
            } 
            else 
            {
                // Found where to place the node.
                currentNode->rightChild = new BinaryTreeNode(value, 0, 0);
                numPointerChanges++;
                // We are finished so break
                break;
            }
        } 
        else 
        {
            if (currentNode->leftChild) 
            {
                currentNode = currentNode->leftChild;
            } 
            else 
            {
                // Found where to place the node.
                currentNode->leftChild = new BinaryTreeNode(value, 0, 0);
                numPointerChanges++;
                // We are finished so break
                break;
            }
        }
    }
}

/*
 * Returns the height of the tree.
 * It simply call the heightHelper function which does all the work
 */
int BinaryTree::height() 
{
    return heightHelper(root);
}

/*
 * This calculates the height of the tree using
 * the definition of height:
 * height(tree) = max(height(tree.leftTree), height(tree.rightTree)) + 1
 */
int BinaryTree::heightHelper(BinaryTreeNode *node) 
{
    // Height of null tree is zero.
    // This is the base case of the recursion
    if (!node) 
    {
        return 0;
    }
    // Use the definition of height
    return 1 + std::max(heightHelper(node->rightChild), heightHelper(node->leftChild));
}

/*
 * Prints an inorder traversal of the tree.
 * It simply call the listHelper function which does all the work
 */
void BinaryTree::list()
{
    listHelper(root);
}

void BinaryTree::listHelper(BinaryTreeNode *node)
{
    // Null tree has no nodes so return
    // This is the base case of the recursion
    if (!node) 
    {
        return;
    }
    // First print the left-subtree.
    listHelper(node->leftChild);
    // Then print the nodes value
    std::cout << node->value << std::endl;
    // First print the right-subtree.
    listHelper(node->rightChild);
}

/*
 * Does an inorder traversal of the tree to get the number of 
 * nodes in the tree rooted at the inserted node
 */
int BinaryTree::uniqueItemsInTreeHelper(BinaryTreeNode *node)
{
    if (!node) 
    {
        return 0;
    }
    return 1 + uniqueItemsInTreeHelper(node->leftChild) + uniqueItemsInTreeHelper(node->rightChild);
}

/*
 * Method simply calls the helper function with the root
 */
int BinaryTree::uniqueItemsInTree() 
{
    return uniqueItemsInTreeHelper(root);
}

/*
 * Similar to uniqueItemsTreeHlper but adds the nodes->weight, instead of just 1, 
 * to get the total number of nodes inserted into the tree rooted at the
 * inserted node.
 */
int BinaryTree::itemsInTreeHelper(BinaryTreeNode *node)
{
    if (!node)
    {
        return 0;
    }
    return 1 + node->weight + itemsInTreeHelper(node->leftChild) + itemsInTreeHelper(node->rightChild);
}

/*
 * This simply calls the helper function
 */
int BinaryTree::itemsInTree()
{
    return itemsInTreeHelper(root);
}
