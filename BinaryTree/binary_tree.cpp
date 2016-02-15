#include "binary_tree.h"

BinaryTree::BinaryTree() : root(NULL) { };

BinaryTreeNode *BinaryTree::findBinaryTreeNode(const std::string &str)
{
    BinaryTreeNode *currentNode = root; 

    while (true)
    {
        int comparison = currentNode->value->compare(str);
        if (comparison == 0)
        {
            return currentNode;
        }
        else if (comparison < 0)
        {
            if (currentNode->rightChild)
            {
                currentNode = currentNode->rightChild; 
            }
            else
            {
                return NULL;
            }
        }
        else if (comparison > 0) 
        {
            if (currentNode->leftChild)
            {
                currentNode = currentNode->leftChild;
            }
            else 
            {
                return NULL;
            }
        }
    }
}

void BinaryTree::remove(const std::string &str)
{

}

void BinaryTree::insert(const std::string &str) 
{
    if (!root) 
    {
        root = new BinaryTreeNode(str);
        return;
    }

    BinaryTreeNode *currentNode = root; 

    while (true)
    {
        int comparison = currentNode->value->compare(str);
        if (comparison == 0)
        {
            currentNode->count++;
            return;
        }
        else if (comparison < 0)
        {
            if (currentNode->rightChild)
            {
                currentNode = currentNode->rightChild; 
            }
            else
            {
                currentNode->rightChild = new BinaryTreeNode(str);
                currentNode->rightChild->parent = currentNode;
                return;
            }
        }
        else if (comparison > 0) 
        {
            if (currentNode->leftChild)
            {
                currentNode = currentNode->leftChild;
            }
            else 
            {
                currentNode->leftChild = new BinaryTreeNode(str);
                currentNode->leftChild->parent = currentNode;
                return;
            }
        }
    }
}

int BinaryTree::search(const std::string &str) 
{
    BinaryTreeNode *node = findBinaryTreeNode(str);
    if (node)
    {
        return node->count;
    }
    return 0;
}

std::string BinaryTree::min() 
{
    BinaryTreeNode *currentNode = root;
    while (currentNode->leftChild) 
    {
        currentNode = currentNode->leftChild;
    }
    return *currentNode->value;
}

std::string BinaryTree::max() 
{
    BinaryTreeNode *currentNode = root;
    while (currentNode->rightChild) 
    {
        currentNode = currentNode->rightChild;
    }
    return *currentNode->value;
}

std::string BinaryTree::next(const std::string &str)
{
    BinaryTreeNode *node = findBinaryTreeNode(str);

    if (node->rightChild) 
    {
        BinaryTreeNode *lastNode = node;
        BinaryTreeNode *currentNode = node->rightChild;

        while (currentNode) 
        {
            lastNode = currentNode;
            currentNode = currentNode->leftChild;
        }

        return *lastNode->value;
    } 
    else
    {
        BinaryTreeNode *previousNode = node;         
        BinaryTreeNode *currentNode = node->parent;         
        while (currentNode) 
        {
            if (currentNode->leftChild == previousNode)
            {
                return *currentNode->value;
            }
            previousNode = currentNode;
            currentNode = currentNode->parent;
        }
    }

    return "";
}

std::string BinaryTree::prev(const std::string &str)
{
    BinaryTreeNode *node = findBinaryTreeNode(str);

    if (node->leftChild) 
    {
        BinaryTreeNode *lastNode = node;
        BinaryTreeNode *currentNode = node->leftChild;

        while (currentNode) 
        {
            lastNode = currentNode;
            currentNode = currentNode->rightChild;
        }

        return *lastNode->value;
    } 
    else
    {
        BinaryTreeNode *previousNode = node;         
        BinaryTreeNode *currentNode = node->parent;         
        while (currentNode) 
        {
            if (currentNode->rightChild == previousNode)
            {
                return *currentNode->value;
            }
            previousNode = currentNode;
            currentNode = currentNode->parent;
        }
    }

    return "";
}

void BinaryTree::list() 
{
    if (root)
    {
        root->list();    
    }
}
