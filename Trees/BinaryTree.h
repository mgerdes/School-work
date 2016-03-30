#include <string>
#include <iostream>

struct BinaryTreeNode 
{
    int weight;
    std::string value;
    BinaryTreeNode *leftChild, *rightChild;

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
    private:
        BinaryTreeNode *root;

        int heightHelper(BinaryTreeNode *node);

        void listHelper(BinaryTreeNode *node);
    public:
        BinaryTree();

        void insert(std::string value);

        int height(); 

        void list();
};
