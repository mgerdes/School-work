#include <string>
#include <iostream>
#include <stdio.h>

#include "Graph.h"
#include "Set.h"
#include "PriorityQueue.h"

void sortEdgesByPath(Edge **edges, int numEdges)
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
    g->sortEdgesByWeight();

    Sets s(g->numNodes);
    for (int i = 0; i < g->numNodes; i++)
    {
        s.addNode(&g->nodes[i]);
    }

    Edge *minSpanningTree[g->numNodes - 1];

    int j = 0;
    for (int i = 0; i < g->numNodes - 1; i++)
    {
        Edge *e = &g->edges[j++];
        while (s.areNodesInSameSet(e->n1, e->n2))
        {
            e = &g->edges[j++];
        }
        s.combineNodes(e->n1, e->n2);
        minSpanningTree[i] = e;
    }

    sortEdgesByPath(minSpanningTree, g->numNodes - 1);

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
void doPrims(Graph *g)
{
    PriorityQueue q(g->numNodes);

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

    sortEdgesByPath(minSpanningTree, g->numNodes - 1);

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

            if (j >= i) continue;

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
