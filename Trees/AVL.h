#include <string>
#include <iostream>
#include <stdlib.h>

/*
 * This is the interface for the AVLTree and AVLTreeNode
 * These interfaces are very similar to those for the other 2 trees.
 *
 * The rotations it uses are different from your slides. I got the idea
 * from the book. They have a problem at the end of one of the sections
 * for implementing AVL and they give a hint that you can use the same rotations
 * from the RedBlackTree. 
 *
 * I felt doing it this way made more sense to me. And it still maintains the same
 * speed: O(lg(n))
 */

struct AVLTreeNode 
{
    // The implementation I used needed a parent pointer
    AVLTreeNode *parent;
    AVLTreeNode *leftChild;
    AVLTreeNode *rightChild;

    // I also store the height of the node in the tree. 
    // I felt doing this made more sense to me.
    int height;
    int weight;
    std::string value;

    // Simple constructor to set things up.
    AVLTreeNode(const std::string &value, AVLTreeNode *parent, AVLTreeNode *leftChild, AVLTreeNode *rightChild) 
        : value(value), height(0), weight(0), parent(parent), leftChild(leftChild), rightChild(rightChild) { }

    // Calculate the balance factor by subtracting height of subtrees
    int getBalanceFactor() 
    {
        int leftHeight = leftChild ? leftChild->height : -1;
        int rightHeight = rightChild ? rightChild->height : -1;

        return leftHeight - rightHeight;
    }

    // Fix the heights of the tree, if the height of the
    // left or right tree changed.
    void recalculateHeight() 
    {
        int leftHeight = leftChild ? leftChild->height : -1;
        int rightHeight = rightChild ? rightChild->height : -1;

        height = std::max(leftHeight, rightHeight) + 1;
    }
};

class AVLTree 
{
    private:
        // The root of the entire tree
        AVLTreeNode *root;

        // Left rotate function is same from RedBlackTree
        void leftRotate(AVLTreeNode *node);

        // Right rotate function is same from RedBlackTree
        void rightRotate(AVLTreeNode *node);

        // Helper function to fix the tree if there are any inbalances.
        void fixTree(AVLTreeNode *node);

        // Helpler function to do an inorder traversal of the tree.
        void listHelper(AVLTreeNode *node);

        int uniqueItemsInTreeHelper(AVLTreeNode *node);

        int itemsInTreeHelper(AVLTreeNode *node);
    public:
        int numPointerChanges; 
        int numBFChanges;
        int numComparisons;

        // Constructor just sets root to be null
        AVLTree() :
            root(NULL), 
            numPointerChanges(0),
            numBFChanges(0),
            numComparisons(0) { }

        void insert(const std::string &value);

        // Return the height of the root node
        int height();

        // Do an inorder traversal of the tree
        void list();

        int uniqueItemsInTree();

        int itemsInTree();
};
