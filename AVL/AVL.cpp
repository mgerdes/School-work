#include <string>
#include <iostream>
#include <stdlib.h>

struct AVLTreeNode 
{
    AVLTreeNode *parent;
    AVLTreeNode *leftChild;
    AVLTreeNode *rightChild;

    int height;
    int weight;
    std::string value;

    AVLTreeNode(const std::string &value, AVLTreeNode *parent, AVLTreeNode *leftChild, AVLTreeNode *rightChild) 
        : value(value), height(0), weight(0), parent(parent), leftChild(leftChild), rightChild(rightChild) { }

    int getBalanceFactor() 
    {
        int leftHeight = leftChild ? leftChild->height : -1;
        int rightHeight = rightChild ? rightChild->height : -1;

        return leftHeight - rightHeight;
    }

    void recalculateHeight() 
    {
        int leftHeight = leftChild ? leftChild->height : -1;
        int rightHeight = rightChild ? rightChild->height : -1;

        height = std::max(leftHeight, rightHeight) + 1;
    }

    void list()
    {
        if (leftChild) 
        {
            leftChild->list();
        }
        std::cout << value << ", " << getBalanceFactor() << std::endl;
        if (rightChild) 
        {
            rightChild->list();
        }
    }
};

class AVLTree 
{
    private:
        AVLTreeNode *root;

        void leftRotate(AVLTreeNode *node);

        void rightRotate(AVLTreeNode *node);

        void fixTree(AVLTreeNode *node);

        int height(AVLTreeNode *node);

    public:
        AVLTree() 
            : root(NULL) { }

        void insert(const std::string &value);

        void list();
};

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

int main() 
{
    AVLTree tree;

    for (int i = 0; i < 1000; i++) {
        std::string s;
        for (int i = 0; i < 3; i++) {
            char c = '1' + (rand() % 9);
            s.push_back(c);
        }
        tree.insert(s);
    }

    tree.list();

    return 0;
}
