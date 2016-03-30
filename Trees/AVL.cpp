#include "AVL.h"

/*
 * AVL Insert first does the "dumb" vaniilla insert and then calls 
 * the fix tree function to fix an inbalances.
 */
void AVLTree::insert(const std::string &value) 
{
    // Set this value to be the root.
    if (!root) 
    {
        root = new AVLTreeNode(value, NULL, NULL, NULL);
        return;
    }

    // Either find the string in the tree, or find where
    // the string belongs in the tree and put it there.
    // Then fix the tree up.
    AVLTreeNode *currentNode = root;
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
            if (currentNode->rightChild) 
            {
                currentNode = currentNode->rightChild;
            } 
            else 
            {
                // Found where to place the node.
                currentNode->rightChild = new AVLTreeNode(value, currentNode, NULL, NULL);
                numPointerChanges++;
                // Fix up the tree
                fixTree(currentNode->rightChild);
                // Were finished so break
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
                currentNode->leftChild = new AVLTreeNode(value, currentNode, NULL, NULL);
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
 *
 * This is the same rightRotate from the RedBlackTree.
 */
void AVLTree::rightRotate(AVLTreeNode *x) 
{
    // The pointer changes are shown schematically above.
    AVLTreeNode *y = x->leftChild;
    AVLTreeNode *z = y->rightChild;

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

    // Make sure to recalculate the heights in case they changed.
    x->recalculateHeight();
    numBFChanges++;
    y->recalculateHeight();
    numBFChanges++;
    if (y->parent) 
    {
        y->parent->recalculateHeight();
        numBFChanges++;
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
 * This is the same leftRotate from the RedBlackTree.
 */      
void AVLTree::leftRotate(AVLTreeNode *x) 
{
    // The pointer changes are shown schematically above.
    AVLTreeNode *y = x->rightChild;
    AVLTreeNode *z = y->leftChild;

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

    // Make sure to recalculate the heights in case they changed.
    x->recalculateHeight();
    numBFChanges++;
    y->recalculateHeight();
    numBFChanges++;
    if (y->parent) 
    {
        y->parent->recalculateHeight();
        numBFChanges++;
    }
}

/*
 * The fix tree method goes up the tree from the node that was inserted
 * to the root.
 * It recalculates all the heights of the nodes as it goes up and 
 * it looks for a balance factor that is +2 or -2.
 * It then fixes the tree using the rotations if it finds one.
 *
 * The rotations it uses are different from your slides. I got the idea
 * from the book. They have a problem at the end of one of the sections
 * for implementing AVL and they give a hint that you can use the same rotations
 * from the RedBlackTree. 
 *
 * I felt doing it this way made more sense to me. And it still maintains the same
 * speed: O(lg(n))
 */
void AVLTree::fixTree(AVLTreeNode *node) 
{
    // Start at the node.
    AVLTreeNode *z = node;

    // Get parent of the node
    AVLTreeNode *y = z->parent;

    if (!y) 
    {
        return;
    }
    y->recalculateHeight();
    numBFChanges++;

    // Get grand-parent of the node
    AVLTreeNode *x = y->parent;

    // X will be null when y is the root. So stop then
    while (x) 
    {
        x->recalculateHeight();
        numBFChanges++;
        
        // Check if the balance factor is off
        if (abs(x->getBalanceFactor()) >= 2) 
        {
            // Figure out which type of rotation to do.
            if (x->leftChild == y && y->leftChild == z) 
            {
                /*                                                            *
                 *          x                y                                *
                 *         / \             /   \                              *
                 *        y   D     ->    z     x                             *
                 *       / \             / \   / \                            *
                 *      z   C           A   B C   D                           *
                 *     / \                                                    *
                 *    A   B                                                   *
                 */
                rightRotate(x);
            } 
            else if (x->leftChild == y && y->rightChild == z) 
            {

                /*                                                            *
                 *          x                  x                  z           *
                 *         / \                / \               /   \         *
                 *        y   D     ->       z   D     ->      y     x        *
                 *       / \                / \               / \   / \       *
                 *      A   z              y   C             A   B C   D      *
                 *         / \            / \                                 *
                 *        B   C          A   B                                *
                 */      
                leftRotate(y);
                rightRotate(x);
            } 
            else if (x->rightChild == y && y->rightChild == z) 
            {
                /*                                                            *
                 *          x                  y                              *
                 *         / \               /   \                            *
                 *        A   y     ->      x     z                           *
                 *           / \           / \   / \                          *
                 *          B   z         A   B C   D                         *
                 *             / \                                            *
                 *            C   D                                           *
                 */      
                leftRotate(x);
            } 
            else if (x->rightChild == y && y->leftChild == z) 
            {
                /*                                                            *
                 *         x               x                      z           *
                 *        / \             / \                   /   \         *
                 *       A   y      ->   A   z         ->      x     y        *
                 *          / \             / \               / \   / \       *
                 *         z   D           B   y             A   B C   D      *
                 *        / \                 / \                             *
                 *       B   C               C   D                            *
                 */      
                rightRotate(y);
                leftRotate(x);
            }

            // Only one rotation is needed to fix the tree so we can now break.
            break;
        }

        // Change pointers to move up in the tree.
        z = y;
        y = x;
        x = x->parent;
    }
}

/*
 * Prints an inorder traversal of the tree.
 * It simply call the listHelper function which does all the work
 */
void AVLTree::list() 
{
    if (root) 
    {
        listHelper(root);
    }
}

/*
 * Prints an inorder traversal using node as the
 * root of the tree.
 */
void AVLTree::listHelper(AVLTreeNode *node)
{
    if (!node) 
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
 * The nodes store their heights so this is easy, just return the height of the root.
 */
int AVLTree::height()
{
    if (root) 
    {
        return root->height;
    }
    else
    {
        return 0;
    }
}

int AVLTree::uniqueItemsInTreeHelper(AVLTreeNode *node)
{
    if (!node) 
    {
        return 0;
    }
    return 1 + uniqueItemsInTreeHelper(node->leftChild) + uniqueItemsInTreeHelper(node->rightChild);
}

int AVLTree::uniqueItemsInTree() 
{
    return uniqueItemsInTreeHelper(root);
}

int AVLTree::itemsInTreeHelper(AVLTreeNode *node)
{
    if (!node)
    {
        return 0;
    }
    return node->weight + itemsInTreeHelper(node->leftChild) + itemsInTreeHelper(node->rightChild);
}

int AVLTree::itemsInTree()
{
    return itemsInTreeHelper(root);
}
