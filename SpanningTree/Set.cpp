#include "Set.h"

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

