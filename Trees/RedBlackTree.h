#include <string>
#include <iostream>
#include <stdio.h>
#include <math.h>

/*
 * This is the interface for the RedBlackTree and RedBlackTreeNode
 * These interfaces are very similar to those for the other 2 trees.
 *
 * Most of the the RedBlackTree code comes straight from the book. 
 */

enum Color {
    RED, BLACK
};

struct RedBlackTreeNode 
{
    RedBlackTreeNode *leftChild, *rightChild, *parent;
    std::string value;

    // Need to store the color of the node
    Color color;
    int weight;

    // Simple constructor to set up the node 
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
        // Need to store the root of the tree and the special 'null' node.
        RedBlackTreeNode *root, *null;

        // Function used to fix the tree if there are any of rules broken  
        void fixTree(RedBlackTreeNode *node);

        // LeftRotate around the node. Same from the book 
        void leftRotate(RedBlackTreeNode *node);

        // RightRotate around the node. Same from the book 
        void rightRotate(RedBlackTreeNode *node);

        // Function to help calculate the height of the tree
        int heightHelper(RedBlackTreeNode *node);

        // Function to help do an inorder traversal of the tree
        void listHelper(RedBlackTreeNode *node);

        int uniqueItemsInTreeHelper(RedBlackTreeNode *node);

        int itemsInTreeHelper(RedBlackTreeNode *node);
    public:
        int numPointerChanges; 
        int numReColorings;
        int numComparisons;

        RedBlackTree();

        void insert(std::string value);

        // Get the height of the tree
        int height(); 

        // Do an inorder traversal of the tree
        void list();

        int uniqueItemsInTree();

        int itemsInTree();
};
