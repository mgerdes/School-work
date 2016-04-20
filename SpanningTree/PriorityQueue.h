#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE

#include "Graph.h"

class PriorityQueue
{
    private:
        int numNodes;
        Node **nodes;
    public:
        PriorityQueue(int maxNumNodes);

        ~PriorityQueue();

        bool isEmpty();

        void addNode(Node *n);

        Node *extractMin();

        bool contains(Node *n);
};

#endif
