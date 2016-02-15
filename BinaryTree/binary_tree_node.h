#ifndef BINARY_TREE_NODE
#define BINARY_TREE_NODE

#include <string>
#include <iostream>

struct BinaryTreeNode 
{
    BinaryTreeNode *leftChild = NULL;
    BinaryTreeNode *rightChild = NULL;
    BinaryTreeNode *parent = NULL;

    std::string *value = NULL;
    int count;

    BinaryTreeNode(const std::string &value)
        : value(new std::string(value)), count(1) { };

    ~BinaryTreeNode()
    {
        delete leftChild;
        delete rightChild;
        delete value;
    }

    void list()
    {
        if (leftChild)
        {
            leftChild->list();
        }
        std::cout << *value << '\n';
        if (rightChild)
        {
            rightChild->list();
        }
    }
};

#endif
