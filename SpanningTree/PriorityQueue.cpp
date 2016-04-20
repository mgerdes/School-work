#include "PriorityQueue.h"

PriorityQueue::PriorityQueue(int maxNumNodes)
{
    nodes = new Node*[maxNumNodes];
    numNodes = 0;
}

PriorityQueue::~PriorityQueue() 
{
    delete[] nodes;
}

bool PriorityQueue::isEmpty()
{
    return numNodes == 0;
}

void PriorityQueue::addNode(Node *n)
{
    nodes[numNodes] = n;
    numNodes++;
}

Node *PriorityQueue::extractMin()
{
    Node *minNode = nodes[0];
    int minNodeIndex = 0;
    for (int i = 1; i < numNodes; i++) 
    {
        Node *n = nodes[i];
        if (n->key < minNode->key)
        {
            minNode = n;
            minNodeIndex = i;
        }
    }

    for (int i = minNodeIndex + 1; i < numNodes; i++)
    {
        nodes[i - 1] = nodes[i];
    }

    numNodes--;

    return minNode;
}

bool PriorityQueue::contains(Node *n)
{
    for (int i = 0; i < numNodes; i++)
    {
        if (nodes[i] == n)
        {
            return true;
        }
    }
    return false;
}

