#ifndef GRAPH
#define GRAPH

#include <string>

struct Node
{
    int key;
    Node *predecessor;
    std::string data;
};

struct Edge
{
    int w;
    Node *n1, *n2;
};

class Graph 
{
    public:
        int numEdges, numNodes;
        Edge *edges;
        Node *nodes;

        Graph(int numNodes);

        ~Graph();

        void addEdge(Edge e);

        void addNode(Node n);

        Edge *getEdge(Node *n1, Node *n2);

        void sortEdgesByWeight();
};

#endif
