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

    ~AVLTreeNode()
    {
        if (leftChild)
        {
            delete leftChild;
        }
        if (rightChild)
        {
            delete rightChild;
        }
    }

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

    public:
        AVLTree() 
            : root(NULL) { }

        ~AVLTree()
        {
            delete root;
        }

        void insert(const std::string &value);

        int height();

        void list();
};
