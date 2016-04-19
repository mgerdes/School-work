#include <stdio.h>

struct Edge
{
    char x, y;
    int w;
};

class Graph 
{
    public:
        int numEdges, numNodes;
        Edge *edges;

        Graph(int numNodes);

        ~Graph();

        void addEdge(Edge e);
};

Graph::Graph(int numNodes) 
{
    this->numNodes = numNodes;
    edges = new Edge[numNodes * numNodes];
    numEdges = 0;
}

Graph::~Graph()
{
    delete[] edges;
}

void Graph::addEdge(Edge e)
{
    edges[numEdges] = e;
    numEdges++;
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
    char x;   
    Set *rest;
};

class Sets
{
    private:
        int numSets;

        Set **sets;

        bool isNodeInSet(char x, Set *s);

        Set *findSetWithNode(char x, int &i);

        void appendToSet(Set *s1, Set *s2);

        void removeSet(Set *s);
    public:
        Sets(int numNodes);

        void addNode(char x);

        void combineNodes(char x, char y);

        bool areNodesInSameSet(char x, char y);
};

Sets::Sets(int numNodes)
{
    sets = new Set*[numNodes];
    numSets = 0;
}

Set *Sets::findSetWithNode(char x, int &i)
{
    for (int j = 0; j < numSets; j++)
    {
        if (isNodeInSet(x, sets[j]))
        {
            i = j;
            break;
        }
    }
    return sets[i];
}

bool Sets::isNodeInSet(char x, Set *s)
{
    while (s)
    {
        if (s->x == x)
        {
            return true;
        }
        s = s->rest;        
    }
    return false;
}

void Sets::addNode(char x)
{
    sets[numSets] = new Set();
    sets[numSets]->x = x;
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

void Sets::combineNodes(char x, char y)
{
    int setWithX, setWithY;

    Set *s1 = findSetWithNode(x, setWithX);
    Set *s2 = findSetWithNode(y, setWithY);

    appendToSet(s1, s2);

    removeSet(s2);
}

bool Sets::areNodesInSameSet(char x, char y)
{
    for (int i = 0; i < numSets; i++)
    {
        if (isNodeInSet(x, sets[i]) && isNodeInSet(y, sets[i]))
        {
            return true;
        }
    }
    return false;
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
        s.addNode('A' + i);
    }

    Edge *minSpanningTree[g->numNodes - 1];

    int minWeight = 0;
    for (int i = 0; i < g->numNodes - 1; i++)
    {
        Edge *e = q.extractMin();
        while (s.areNodesInSameSet(e->x, e->y))
        {
            e = q.extractMin();
        }
        s.combineNodes(e->x, e->y);
        minSpanningTree[i] = e;
        minWeight += e->w;
    }

    for (int i = 0; i < g->numNodes - 1; i++)
    {
        Edge *e = minSpanningTree[i];
        printf("%c - %c, %d\n", e->x, e->y, e->w);
    }

    printf("%d\n", minWeight);
}

void doPrims(Graph *g)
{
    
}

int main() 
{
    Graph g(9);
    
    g.addEdge({'A', 'B', 10});
    g.addEdge({'A', 'C', 12});
    g.addEdge({'B', 'C', 9});
    g.addEdge({'B', 'D', 8});
    g.addEdge({'C', 'E', 3});
    g.addEdge({'C', 'F', 1});
    g.addEdge({'D', 'E', 7});
    g.addEdge({'D', 'G', 8});
    g.addEdge({'D', 'H', 5});
    g.addEdge({'E', 'F', 3});
    g.addEdge({'F', 'H', 6});
    g.addEdge({'G', 'H', 9});
    g.addEdge({'G', 'I', 2});
    g.addEdge({'H', 'I', 11});

    doKruskals(&g);

    return 0;
}
