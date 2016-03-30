#include "BinaryTree.h"

BinaryTree::BinaryTree()
{
    this->root = 0;    
}

void BinaryTree::insert(std::string value) 
{
    if (!this->root) {
        this->root = new BinaryTreeNode(value, 0, 0);
        return;
    }
    
    BinaryTreeNode *currentNode = this->root;
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
                currentNode->rightChild = new BinaryTreeNode(value, 0, 0);
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
                currentNode->leftChild = new BinaryTreeNode(value, 0, 0);
                break;
            }
        }
    }
}

int BinaryTree::height() 
{
    return heightHelper(root);
}

int BinaryTree::heightHelper(BinaryTreeNode *node) 
{
    if (!node) 
    {
        return 0;
    }
    return 1 + std::max(heightHelper(node->rightChild), heightHelper(node->leftChild));
}

void BinaryTree::list()
{
    if (!root)
    {
        return;
    }
    listHelper(root);
}

void BinaryTree::listHelper(BinaryTreeNode *node)
{
    if (!node) 
    {
        return;
    }
    listHelper(node->leftChild);
    std::cout << node->value << std::endl;
    listHelper(node->rightChild);
}
