#include "Graph.h"

Graph::Graph(int numNodes) 
{
    this->numNodes = 0;
    this->numEdges = 0;
    edges = new Edge[numNodes * numNodes];
    nodes = new Node[numNodes];
}

Graph::~Graph()
{
    delete[] edges;
    delete[] nodes;
}

Edge *Graph::getEdge(Node *n1, Node *n2)
{
    for (int i = 0; i < numEdges; i++)
    {
        if (edges[i].n1 == n1 && edges[i].n2 == n2
                || edges[i].n1 == n2 && edges[i].n2 == n1)
        {
            return &edges[i];
        }
    }
    return 0;
}

void Graph::addEdge(Edge e)
{
    edges[numEdges] = e;
    numEdges++;
}

void Graph::addNode(Node n)
{
    nodes[numNodes] = n;
    numNodes++;
}

void Graph::sortEdgesByWeight()
{
    for (int i = 0; i < this->numEdges; i++)
    {
        int k = i;
        for (int j = i; j < this->numEdges; j++)
        {
            if (this->edges[j].w < this->edges[k].w)
            {
                k = j; 
            }
        }
        Edge temp = this->edges[i];
        this->edges[i] = this->edges[k];
        this->edges[k] = temp;
    }
}


