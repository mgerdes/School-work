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

        void listHelper(RedBlackTreeNode *node);
    public:
        RedBlackTree();

        void insert(std::string value);

        int height(); 

        void list();
};
