#include <string>
#include <iostream>

/*
 * This is the interface for the vanilla BinaryTree and BinaryTreeNode.
 *
 * It is very similar to the other 2 trees except it has no private
 * fixup function.
 */

struct BinaryTreeNode 
{
    // Vanilla node has nothing special like a color or balance factor
    int weight;
    std::string value;
    BinaryTreeNode *leftChild, *rightChild;

    // Simple constructor to set things up
    BinaryTreeNode(std::string value, 
            BinaryTreeNode *leftChild,
            BinaryTreeNode *rightChild)
        : value(value), 
        leftChild(leftChild), 
        rightChild(rightChild),
        weight(0) { };
};

class BinaryTree 
{
    // The vanilla BinaryTree has no special fixup function
    private:
        BinaryTreeNode *root;

        // Function to find height of tree rooted at node
        int heightHelper(BinaryTreeNode *node);

        // Function to do inorder traversal of tree rooted at node
        void listHelper(BinaryTreeNode *node);

        int uniqueItemsInTreeHelper(BinaryTreeNode *node);

        int itemsInTreeHelper(BinaryTreeNode *node);
    public:
        int numComparisons;
        int numPointerChanges;

        // Simple constructor just sets the root to be null
        BinaryTree() :
            root(0),
            numComparisons(0),
            numPointerChanges(0) { };

        void insert(std::string value);

        // Returns the height of the entire tree
        int height(); 

        // Does an inorder traversal of the entire tree 
        void list();

        // Get the unique items in the tree (i.e number of nodes)
        int uniqueItemsInTree();

        // Get the number of items in the tree (i.e. number of things inserted)
        int itemsInTree();
};
