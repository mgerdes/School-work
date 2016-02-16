#include "priority_queue.h"

void PriorityQueue::swap(int i, int j) 
{
    HuffmanNode *temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
}

int PriorityQueue::leftChild(int i) 
{
    return 2 * i + 1;
}

int PriorityQueue::rightChild(int i) 
{
    return 2 * i + 2;
}

int PriorityQueue::parent(int i) 
{
    return (i - 1) / 2;
}

void PriorityQueue::minHeapify(int i) 
{
    int left = leftChild(i);
    int right = rightChild(i);

    int smallestWeight = heap[i]->weight;
    int smallestIndex = i;

    if (left < size && smallestWeight > heap[left]->weight) 
    {
        smallestIndex = left;
        smallestWeight = heap[left]->weight;
    }
    if (right < size && smallestWeight > heap[right]->weight) 
    {
        smallestIndex = right;
        smallestWeight = heap[right]->weight;
    }

    if (i == smallestIndex) return;
    swap(i, smallestIndex);
    if (smallestIndex > (size - 2) / 2) return;
    minHeapify(smallestIndex);
}

PriorityQueue::PriorityQueue(HuffmanNode **nodes, int size) 
{
    this->size = size;
    this->heap = new HuffmanNode*[size];

    for (int i = 0; i < size; i++) 
    {
        heap[i] = nodes[i];
    }

    for (int i = (size - 2) / 2; i >= 0; i--) 
    {
        minHeapify(i);
    }
}

PriorityQueue::~PriorityQueue()
{
    delete[] heap;
}

void PriorityQueue::insert(HuffmanNode *node) 
{
    heap[size] = node;
    int i = size;
    int p = parent(size);
    while (heap[p]->weight > node->weight && i > 0) {
        swap(p, i); 
        i = p;
        p = parent(i);
    }

    size++;
}

HuffmanNode *PriorityQueue::extractMin() 
{
    HuffmanNode *min = heap[0]; 
    swap(0, size - 1);
    size--;
    minHeapify(0);
    return min;
}

int PriorityQueue::getSize()
{
    return size;
}
