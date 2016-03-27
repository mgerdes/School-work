#include <string>
#include <iostream>
#include <stdio.h>
#include <math.h>

enum Color {
    RED, BLACK
};

class RedBlackTreeNode 
{
    public:
        Color color;
        int weight;
        std::string value;
        RedBlackTreeNode *leftChild, *rightChild, *parent;

        RedBlackTreeNode(std::string value, 
                Color color, 
                RedBlackTreeNode *parent, 
                RedBlackTreeNode *leftChild, 
                RedBlackTreeNode *rightChild)
            : value(value), 
            color(color), 
            parent(parent), 
            leftChild(leftChild), 
            rightChild(rightChild),
            weight(0) { };
};

class RedBlackTree 
{
    private:
        RedBlackTreeNode *root, *null;

        void fixTree(RedBlackTreeNode *node);

        void leftRotate(RedBlackTreeNode *node);

        void rightRotate(RedBlackTreeNode *node);

        int heightHelper(RedBlackTreeNode *node);
    public:
        RedBlackTree();

        void insert(std::string value);

        int height(); 
};

int RedBlackTree::height() {
    return heightHelper(root);
}

int RedBlackTree::heightHelper(RedBlackTreeNode *node) {
    if (!node || node == null) {
        return 0;
    }
    return 1 + std::max(heightHelper(node->rightChild), heightHelper(node->leftChild));
}

RedBlackTree::RedBlackTree() 
{
    null = new RedBlackTreeNode("", BLACK, 0, 0, 0);
    root = 0;
}

void RedBlackTree::insert(std::string value) 
{
    if (!root) 
    {
        root = new RedBlackTreeNode(value, BLACK, null, null, null);
        return;
    }

    RedBlackTreeNode *currentNode = root;
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
            if (currentNode->rightChild != null) 
            {
                currentNode = currentNode->rightChild;
            } 
            else 
            {
                currentNode->rightChild = new RedBlackTreeNode(value, RED, currentNode, null, null);
                fixTree(currentNode->rightChild);
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
                currentNode->leftChild = new RedBlackTreeNode(value, RED, currentNode, null, null);
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
void RedBlackTree::rightRotate(RedBlackTreeNode *x) 
{
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
 */      
void RedBlackTree::leftRotate(RedBlackTreeNode *x) 
{
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
        root = y;
    }
}

void RedBlackTree::fixTree(RedBlackTreeNode *z) 
{
    while (z->parent->color == RED) 
    {
        if (z->parent == z->parent->parent->leftChild) 
        {
            RedBlackTreeNode *y = z->parent->parent->rightChild;
            if (y->color == RED) 
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else 
            {
                if (z == z->parent->rightChild) 
                {
                    z = z->parent;
                    leftRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(z->parent->parent);
            }
        }
        else 
        {
            RedBlackTreeNode *y = z->parent->parent->leftChild;
            if (y->color == RED) 
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else 
            {
                if (z == z->parent->leftChild) 
                {
                    z = z->parent;
                    rightRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(z->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

int main() 
{
    char chari[10];
    RedBlackTree tree;
    for (int i = 1000; i < 9999; i++) {
        sprintf(chari, "%4i", i);
        tree.insert(chari);
    }
    std::cout << tree.height() << std::endl;
    return 0;
}
