#include "RedBlackTree.h"

/*
 * RedBlackTree constructor.
 * Sets up the 'null' node and makes the root null
 */
RedBlackTree::RedBlackTree() 
{
    null = new RedBlackTreeNode("", BLACK, 0, 0, 0);
    root = 0;
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
    if (x->parent) 
    {
        if (x->parent->leftChild == x) 
        {
            x->parent->leftChild = y;
        } 
        else 
        {
            x->parent->rightChild = y;
        }
    }

    x->parent = y;
    y->rightChild = x;

    if (z) 
    {
        z->parent = x;
    }
    x->leftChild = z;

    if (root == x) 
    {
        // Might need to change the root aswell.
        root = y;
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
    if (x->parent) 
    {
        if (x->parent->leftChild == x) 
        {
            x->parent->leftChild = y;
        } 
        else 
        {
            x->parent->rightChild = y;
        }
    }

    x->parent = y;
    y->leftChild = x;

    if (z) 
    {
        z->parent = x;
    }
    x->rightChild = z;

    if (root == x) 
    {
        // Might need to change the root aswell.
        root = y;
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
                y->color = BLACK;
                z->parent->parent->color = RED;
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
                z->parent->parent->color = RED;
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
                y->color = BLACK;
                z->parent->parent->color = RED;
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
                z->parent->parent->color = RED;
                leftRotate(z->parent->parent);
            }
        }
    }
    // Make sure that the root of the tree stays black 
    root->color = BLACK;
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

