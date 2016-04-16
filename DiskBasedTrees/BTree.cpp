#define TREE_DEGREE 3

struct BTreeNode 
{
    int id;

    int numberOfKeys;
    char keys[2 * TREE_DEGREE - 1][50];

    int children[TREE_DEGREE]

    bool isLeaf;
};

class BTree {
    public:
        BTreeNode rootNode, node1, node2, node3;

        BTree();

        void splitChild(BTreeNode &node, int i);

        void writeNodeToFile(BTreeNode &node);

        void readNodeFromFile(BTreeNode &node, int id);
};

BTree::BTree() {
    rootNode.isLeaf = true;
    rootNode.numberOfKeys = 0;
    writeToDisk(rootNode);
}

void BTree::writeNodeToFile(BTreeNode &node) {

}

void BTree::splitChild(BTreeNode &node, int i) {
    allocateNode(node1);
    readNodeFromFile(node2, node.children[i]);
    node1.isLeaf = node2.isLeaf;
    node1.numberOfKeys = TREE_DEGREE - 1;
    for (int j = 1; j <= TREE_DEGREE - 1; j++) {
        node1.keys[j] = y.keys[j + 1];
    }
}
