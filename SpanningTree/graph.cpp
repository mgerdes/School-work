#include <string>
#include <iostream>
#include <stdio.h>

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
};

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

class PriorityQueue
{
    private:
        int numEdges;
        Edge **edges;
    public:
        PriorityQueue(int maxNumEdges);

        ~PriorityQueue();

        bool isEmpty();

        void addEdge(Edge *e);

        Edge *extractMin();
};

PriorityQueue::PriorityQueue(int maxNumEdges)
{
    edges = new Edge*[maxNumEdges];
    numEdges = 0;
}

PriorityQueue::~PriorityQueue() 
{
    delete[] edges;
}

bool PriorityQueue::isEmpty()
{
    return numEdges == 0;
}

void PriorityQueue::addEdge(Edge *e)
{
    edges[numEdges] = e;
    numEdges++;
}

Edge *PriorityQueue::extractMin()
{
    Edge *minEdge = edges[0];
    int minEdgeIndex = 0;
    for (int i = 1; i < numEdges; i++) 
    {
        Edge *e = edges[i];
        if (e->w < minEdge->w)
        {
            minEdge = e;
            minEdgeIndex = i;
        }
    }

    for (int i = minEdgeIndex + 1; i < numEdges; i++)
    {
        edges[i - 1] = edges[i];
    }

    numEdges--;

    return minEdge;
}

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

Sets::Sets(int numNodes)
{
    sets = new Set*[numNodes];
    numSets = 0;
}

Set *Sets::findSetWithNode(Node *n, int &i)
{
    for (int j = 0; j < numSets; j++)
    {
        if (isNodeInSet(n, sets[j]))
        {
            i = j;
            break;
        }
    }
    return sets[i];
}

bool Sets::isNodeInSet(Node *n, Set *s)
{
    while (s)
    {
        if (s->n->data == n->data)
        {
            return true;
        }
        s = s->rest;        
    }
    return false;
}

void Sets::addNode(Node *n)
{
    sets[numSets] = new Set();
    sets[numSets]->n = n;
    sets[numSets]->rest = 0;
    numSets++;
}

void Sets::appendToSet(Set *s1, Set *s2)
{
    while(s1->rest)
    {
        s1 = s1->rest; 
    }
    s1->rest = s2;
}

void Sets::removeSet(Set *s)
{
    for (int i = 0; i < numSets; i++)
    {
        if (sets[i] == s)
        {
            sets[i] = 0;

            for (int j = i + 1; j < numSets; j++)
            {
                sets[j - 1] = sets[j];
            }
            numSets--;

            break;
        }
    }
}

void Sets::combineNodes(Node *n1, Node *n2)
{
    int setWithN1, setWithN2;

    Set *s1 = findSetWithNode(n1, setWithN1);
    Set *s2 = findSetWithNode(n2, setWithN2);

    appendToSet(s1, s2);

    removeSet(s2);
}

bool Sets::areNodesInSameSet(Node *n1, Node *n2)
{
    for (int i = 0; i < numSets; i++)
    {
        if (isNodeInSet(n1, sets[i]) && isNodeInSet(n2, sets[i]))
        {
            return true;
        }
    }
    return false;
}

void sortEdges(Edge **edges, int numEdges)
{
    for (int i = 0; i < numEdges; i++)
    {
        int k = i;
        for (int j = i; j < numEdges; j++)
        {
            if (edges[j]->n1->data > edges[j]->n2->data)
            {
                std::string temp = edges[j]->n1->data;
                edges[j]->n1->data = edges[j]->n2->data;
                edges[j]->n2->data = temp;
            }
            if (edges[j]->n1->data < edges[k]->n1->data)
            {
                k = j;
            }
            else if (edges[j]->n1->data == edges[k]->n1->data)
            {
                if (edges[j]->n2->data < edges[k]->n2->data)
                {
                    k = j;
                }
            }
        }
        Edge *temp = edges[i];
        edges[i] = edges[k];
        edges[k] = temp;
    }
}

void doKruskals(Graph *g)
{
    PriorityQueue q(g->numEdges);

    for (int i = 0; i < g->numEdges; i++)
    {
        q.addEdge(&g->edges[i]);
    }

    Sets s(g->numNodes);
    for (int i = 0; i < g->numNodes; i++)
    {
        s.addNode(&g->nodes[i]);
    }

    Edge *minSpanningTree[g->numNodes - 1];

    for (int i = 0; i < g->numNodes - 1; i++)
    {
        Edge *e = q.extractMin();
        while (s.areNodesInSameSet(e->n1, e->n2))
        {
            e = q.extractMin();
        }
        s.combineNodes(e->n1, e->n2);
        minSpanningTree[i] = e;
    }

    sortEdges(minSpanningTree, g->numNodes - 1);

    printf("Kruskals's Algorithm\n");

    int minWeight = 0;
    for (int i = 0; i < g->numNodes - 1; i++)
    {
        Edge *e = minSpanningTree[i];
        minWeight += e->w;
        printf("%s - %s, %d\n", e->n1->data.c_str(), e->n2->data.c_str(), e->w);
    }

    printf("%d\n", minWeight);
}

class NodePriorityQueue
{
    private:
        int numNodes;
        Node **nodes;
    public:
        NodePriorityQueue(int maxNumNodes);

        ~NodePriorityQueue();

        bool isEmpty();

        void addNode(Node *n);

        Node *extractMin();

        bool contains(Node *n);
};

NodePriorityQueue::NodePriorityQueue(int maxNumNodes)
{
    nodes = new Node*[maxNumNodes];
    numNodes = 0;
}

NodePriorityQueue::~NodePriorityQueue() 
{
    delete[] nodes;
}

bool NodePriorityQueue::isEmpty()
{
    return numNodes == 0;
}

void NodePriorityQueue::addNode(Node *n)
{
    nodes[numNodes] = n;
    numNodes++;
}

Node *NodePriorityQueue::extractMin()
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

bool NodePriorityQueue::contains(Node *n)
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

void doPrims(Graph *g)
{
    NodePriorityQueue q(g->numNodes);

    for (int i = 0; i < g->numNodes; i++)
    {
        q.addNode(&g->nodes[i]); 
    }

    g->nodes[0].key = 0;

    while (!q.isEmpty())
    {
        Node *u = q.extractMin();

        for (int i = 0; i < g->numEdges; i++)
        {
            Node *v = 0;
            if (g->edges[i].n1 == u)
            {
                v = g->edges[i].n2;
            }
            if (g->edges[i].n2 == u)
            {
                v = g->edges[i].n1;
            }
            if (v && q.contains(v) && g->edges[i].w < v->key)
            {
                v->predecessor = u;
                v->key = g->edges[i].w;
            }
        }
    }

    Edge *minSpanningTree[g->numNodes - 1];

    for (int i = 1; i < 9; i++)
    {
        Node *n1 = &g->nodes[i]; 
        Node *n2 = n1->predecessor;
        minSpanningTree[i - 1] = g->getEdge(n1, n2);
    }

    sortEdges(minSpanningTree, g->numNodes - 1);

    printf("Prim's Algorithm\n");

    int minWeight = 0;
    for (int i = 0; i < g->numNodes - 1; i++)
    {
        Edge *e = minSpanningTree[i];
        minWeight += e->w;
        printf("%s - %s, %d\n", e->n1->data.c_str(), e->n2->data.c_str(), e->w);
    }

    printf("%d\n", minWeight);
}

int main() 
{
    int n;
    std::cin >> n;

    Graph g(n);

    for (int i = 0; i < n; i++)
    {
        std::string data;
        std::cin >> data;

        g.addNode({999999, 0, data});
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int weight;
            std::cin >> weight;

            if (weight != -1)
            {
                g.addEdge({weight, &g.nodes[i], &g.nodes[j]});
            }
        }
    }

    doKruskals(&g);
    doPrims(&g);

    return 0;
}
