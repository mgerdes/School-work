#ifndef BINARY_TREE
#define BINARY_TREE

#include "binary_tree_node.h"
#include "string"

class BinaryTree {
    private:
        BinaryTreeNode *root;

        BinaryTreeNode *findBinaryTreeNode(const std::string &str);

    public:
        BinaryTree(); 

        BinaryTree(const std::string &str);

        void insert(const std::string &str);

        void remove(const std::string &str);

        int search(const std::string &str);

        std::string min();

        std::string max();

        std::string next(const std::string &str);

        std::string prev(const std::string &str);

        void list();
};

#endif // BINARY_TREE
