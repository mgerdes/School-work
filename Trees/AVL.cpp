#include "AVL.h"

void AVLTree::insert(const std::string &value) 
{
    if (!root) 
    {
        root = new AVLTreeNode(value, NULL, NULL, NULL);
        return;
    }

    AVLTreeNode *currentNode = root;
    while (true) 
    {
        int comparison = value.compare(currentNode->value);
        if (comparison == 0) 
        {
            currentNode->weight++;
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
                currentNode->rightChild = new AVLTreeNode(value, currentNode, NULL, NULL);
                fixTree(currentNode->rightChild);
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
                currentNode->leftChild = new AVLTreeNode(value, currentNode, NULL, NULL);
                fixTree(currentNode->leftChild);
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
 */
void AVLTree::rightRotate(AVLTreeNode *x) 
{
    AVLTreeNode *y = x->leftChild;
    AVLTreeNode *z = y->rightChild;

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
        root = y;
    }

    x->recalculateHeight();
    y->recalculateHeight();
    if (y->parent) 
    {
        y->parent->recalculateHeight();
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
 */      
void AVLTree::leftRotate(AVLTreeNode *x) 
{
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
        root = y;
    }

    x->recalculateHeight();
    y->recalculateHeight();
    if (y->parent) 
    {
        y->parent->recalculateHeight();
    }
}

void AVLTree::fixTree(AVLTreeNode *node) 
{
    AVLTreeNode *z = node;
    AVLTreeNode *y = z->parent;

    if (!y) 
    {
        return;
    }
    y->recalculateHeight();

    AVLTreeNode *x = y->parent;

    while (x) 
    {
        x->recalculateHeight();
        
        if (abs(x->getBalanceFactor()) >= 2) 
        {
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
            break;
        }

        z = y;
        y = x;
        x = x->parent;
    }
}

void AVLTree::list() 
{
    if (root) 
    {
        root->list();    
    }
}

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
