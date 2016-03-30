#include "RedBlackTree.h"

/*
 * RedBlackTree constructor.
 * Sets up the 'null' node and makes the root null
 */
RedBlackTree::RedBlackTree() 
{
    null = new RedBlackTreeNode("", BLACK, 0, 0, 0);
    root = 0;
    numPointerChanges = 0;
    numReColorings = 0;
    numComparisons = 0;
}

/*
 * RedBlackTree insert does the normal vanilla insert
 * and then calls the fixTree function to fix anything
 * wrong with the tree.
 *
 * This is essentially the same as the AVL one.
 */
void RedBlackTree::insert(std::string value) 
{
    // Set this value to be the root.
    if (!root) 
    {
        root = new RedBlackTreeNode(value, BLACK, null, null, null);
        return;
    }

    // Either find the string in the tree, or find where
    // the string belongs in the tree and put it there.
    // Then fix the tree up.
    RedBlackTreeNode *currentNode = root;
    while (true) 
    {
        int comparison = value.compare(currentNode->value);
        numComparisons++;
        if (comparison == 0) 
        {
            // Found the node in the tree so just increment its weight.
            currentNode->weight++;
            // Were finished so break
            break;
        } 
        else if (comparison > 0) 
        {
            if (currentNode->rightChild != null) 
            {
                currentNode = currentNode->rightChild;
            } 
            else 
            {
                // Found where to place the node.
                currentNode->rightChild = new RedBlackTreeNode(value, RED, currentNode, null, null);
                numPointerChanges++;
                // Fix up the tree
                fixTree(currentNode->rightChild);
                // Were finished so break
                break;
            }
        } 
        else 
        {
            if (currentNode->leftChild != null) 
            {
                currentNode = currentNode->leftChild;
            } 
            else 
            {
                // Found where to place the node.
                currentNode->leftChild = new RedBlackTreeNode(value, RED, currentNode, null, null);
                numPointerChanges++;
                // Fix up the tree
                fixTree(currentNode->leftChild);
                // Were finished so break
                break;
            }
        }
    }
}

/*                                     *
 *          x               y          *
 *         / \             / \         *
 *        y   D     ->    A   x        *
 *       / \                 / \       *
 *      A   z               z   C      *
 *         / \             / \         *
 *        B   C           B   C        *
 * This is the same RightRotate from the AVLTree
 * It is also the same from the CLRS book.
 */
void RedBlackTree::rightRotate(RedBlackTreeNode *x) 
{
    // The pointer changes are shown schematically above.
    RedBlackTreeNode *y = x->leftChild;
    RedBlackTreeNode *z = y->rightChild;

    y->parent = x->parent; 
    numPointerChanges++;
    if (x->parent) 
    {
        if (x->parent->leftChild == x) 
        {
            x->parent->leftChild = y;
            numPointerChanges++;
        } 
        else 
        {
            x->parent->rightChild = y;
            numPointerChanges++;
        }
    }

    x->parent = y;
    numPointerChanges++;
    y->rightChild = x;
    numPointerChanges++;

    if (z) 
    {
        z->parent = x;
        numPointerChanges++;
    }
    x->leftChild = z;
    numPointerChanges++;

    if (root == x) 
    {
        // Might need to change the root aswell.
        root = y;
        numPointerChanges++;
    }
}

/*                                      *
 *          x                 y         *
 *         / \               / \        *
 *        A   y     ->      x   C       *
 *           / \           / \          *
 *          z   D         A   z         *
 *         / \               / \        *
 *        B   C             B   C       *
 *
 * This is the same LeftRotate from the AVLTree
 * It is also the same from the CLRS book.
 */      
void RedBlackTree::leftRotate(RedBlackTreeNode *x) 
{
    // The pointer changes are shown schematically above.
    RedBlackTreeNode *y = x->rightChild;
    RedBlackTreeNode *z = y->leftChild;

    y->parent = x->parent; 
    numPointerChanges++;
    if (x->parent) 
    {
        if (x->parent->leftChild == x) 
        {
            x->parent->leftChild = y;
            numPointerChanges++;
        } 
        else 
        {
            x->parent->rightChild = y;
            numPointerChanges++;
        }
    }

    x->parent = y;
    numPointerChanges++;
    y->leftChild = x;
    numPointerChanges++;

    if (z) 
    {
        z->parent = x;
        numPointerChanges++;
    }
    x->rightChild = z;
    numPointerChanges++;

    if (root == x) 
    {
        // Might need to change the root aswell.
        root = y;
        numPointerChanges++;
    }
}

/*
 * The fixTree code is basically the same from the book.
 *
 * It first tries to find a problem in the tree (either case 1, 2, or 3)
 * and then it fixes these problems and goes further up the tree to fix
 * any more problems.
 */
void RedBlackTree::fixTree(RedBlackTreeNode *z) 
{
    while (z->parent->color == RED) 
    {
        if (z->parent == z->parent->parent->leftChild) 
        {
            // This is the code that they give in the book
            // for when z's parent is z's grand-parents left-child.
            RedBlackTreeNode *y = z->parent->parent->rightChild;
            if (y->color == RED) 
            {
                // Case 1 problem
                z->parent->color = BLACK;
                numReColorings++;
                y->color = BLACK;
                numReColorings++;
                z->parent->parent->color = RED;
                numReColorings++;
                z = z->parent->parent;
            }
            else 
            {
                if (z == z->parent->rightChild) 
                {
                    // Case 2 problem
                    z = z->parent;
                    leftRotate(z);
                }
                // Case 3 problem
                z->parent->color = BLACK;
                numReColorings++;
                z->parent->parent->color = RED;
                numReColorings++;
                rightRotate(z->parent->parent);
            }
        }
        else 
        {
            // This code was not in the book
            // Its for when z's parent is z's grand-parents right-child
            // // It is basically symetric to the previous case.
            RedBlackTreeNode *y = z->parent->parent->leftChild;
            if (y->color == RED) 
            {
                // Case 1 problem
                z->parent->color = BLACK;
                numReColorings++;
                y->color = BLACK;
                numReColorings++;
                z->parent->parent->color = RED;
                numReColorings++;
                z = z->parent->parent;
            }
            else 
            {
                if (z == z->parent->leftChild) 
                {
                    // Case 2 problem
                    z = z->parent;
                    rightRotate(z);
                }
                // Case 3 problem
                z->parent->color = BLACK;
                numReColorings++;
                z->parent->parent->color = RED;
                numReColorings++;
                leftRotate(z->parent->parent);
            }
        }
    }
    // Make sure that the root of the tree stays black 
    root->color = BLACK;
    numReColorings++;
}

/*
 * Prints an inorder traversal of the tree.
 * It simply call the listHelper function which does all the work
 */
void RedBlackTree::list() 
{
    listHelper(root);
}

/*
 * Prints an inorder traversal using node as the
 * root of the tree.
 */
void RedBlackTree::listHelper(RedBlackTreeNode *node) 
{
    // Null tree has no nodes so return
    // This is the base case of the recursion
    if (node == null) 
    {
        return;
    }
    // First print the left-subtree.
    listHelper(node->leftChild);
    // Next print the nodes value.
    std::cout << node->value << std::endl;
    // Then print the nodes right-subtree.
    listHelper(node->rightChild);
}

/*
 * Calculates the height of the tree.
 * It simply calls the heightHelper function using the root.
 */
int RedBlackTree::height() 
{
    return heightHelper(root);
}

/*
 * This calculates the height of the tree using
 * the definition of height:
 * height(tree) = max(height(tree.leftTree), height(tree.rightTree)) + 1
 */
int RedBlackTree::heightHelper(RedBlackTreeNode *node) 
{
    // Height of null tree is zero.
    // This is the base case of the recursion
    if (!node || node == null) {
        return 0;
    }
    // Use the definition of height here
    return 1 + std::max(heightHelper(node->rightChild), heightHelper(node->leftChild));
}

/*
 * Does an inorder traversal of the tree to get the number of 
 * nodes in the tree rooted at the inserted node
 */
int RedBlackTree::uniqueItemsInTreeHelper(RedBlackTreeNode *node)
{
    if (node == null) 
    {
        return 0;
    }
    return 1 + uniqueItemsInTreeHelper(node->leftChild) + uniqueItemsInTreeHelper(node->rightChild);
}

/*
 * Method simply calls the helper function with the root
 */
int RedBlackTree::uniqueItemsInTree() 
{
    return uniqueItemsInTreeHelper(root);
}

/*
 * Similar to uniqueItemsTreeHlper but adds the nodes->weight, instead of just 1, 
 * to get the total number of nodes inserted into the tree rooted at the
 * inserted node.
 */
int RedBlackTree::itemsInTreeHelper(RedBlackTreeNode *node)
{
    if (node == null)
    {
        return 0;
    }
    return 1 + node->weight + itemsInTreeHelper(node->leftChild) + itemsInTreeHelper(node->rightChild);
}

/*
 * This simply calls the helper function
 */
int RedBlackTree::itemsInTree()
{
    return itemsInTreeHelper(root);
}
