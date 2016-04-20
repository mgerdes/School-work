#ifndef SET
#define SET

#include "Graph.h"

struct Set
{
    Node *n;
    Set *rest;
};

class Sets
{
    private:
        int numSets;

        Set **sets;

        bool isNodeInSet(Node *n, Set *s);

        Set *findSetWithNode(Node *n, int &i);

        void appendToSet(Set *s1, Set *s2);

        void removeSet(Set *s);
    public:
        Sets(int numNodes);

        void addNode(Node *n);

        void combineNodes(Node *n1, Node *n2);

        bool areNodesInSameSet(Node *n1, Node *n2);
};

#endif
