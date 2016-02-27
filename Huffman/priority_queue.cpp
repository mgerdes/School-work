/*
 * Name : Michael Gerdes
 * Date : February 20, 2016
 * Class : Non-Linear Data Structures
 *
 * This file contains the implementation of a priority queue. It uses a heap.
 */

#include "priority_queue.h"

/*
 * Simple helper method for swapping two elements in an array.
 */
void PriorityQueue::swap(int i, int j) 
{
    HuffmanNode *temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
}

/*
 * Get the index of the left child of an index i. Is 2 * i + 1 because i'm using a 0 indexed array.
 */
int PriorityQueue::leftChild(int i) 
{
    return 2 * i + 1;
}

/*
 * Get the index of the right child of an index i. Is 2 * i + 2 because i'm using a 0 indexed array.
 */
int PriorityQueue::rightChild(int i) 
{
    return 2 * i + 2;
}

/*
 * Get the parent index of an index i. 
 */
int PriorityQueue::parent(int i) 
{
    return (i - 1) / 2;
}

/*
 * MinHeapify will fix a violation in the heap.
 * It keeps 'floating' nodes down the heap. Fixing any violation it see's along the way.
 */
void PriorityQueue::minHeapify(int i) 
{
    int left = leftChild(i);
    int right = rightChild(i);

    // Find the index child with the smallest weight.
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

    // If this is true then there are no problems with the heap, so just return.
    if (i == smallestIndex) return;

    // Else we need to swap these two elements, because they represent a problem in the heap.
    swap(i, smallestIndex);
    if (smallestIndex > (size - 2) / 2) return;

    // Recurse to find more problems.
    minHeapify(smallestIndex);
}

/*
 * The constructor simply creates the array and initializes the size to 0.
 */
PriorityQueue::PriorityQueue(int size)
{
    this->size = 0;
    this->heap = new HuffmanNode*[size];
}

/*
 * Destroctor deletes the array we created in the constructor.
 */
PriorityQueue::~PriorityQueue()
{
    delete[] heap;
}

/*
 * Method for inserting a huffmanNode into the priorityQueue.
 * It places the node at the very back of the array, and then 'floats' it up.
 */
void PriorityQueue::insert(HuffmanNode *node) 
{
    // Place node at end of array.
    heap[size] = node;

    int i = size;
    int p = parent(size);

    // Keep floating the node up for as long as it is greater than it's parent.
    while (heap[p]->weight > node->weight && i > 0) {
        swap(p, i); 
        i = p;
        p = parent(i);
    }

    // Increment the size because now there is one more node in the priority queue.
    size++;
}

/*
 * Returns the min huffmanNode in the priority queue. Also removes that node.
 */
HuffmanNode *PriorityQueue::extractMin() 
{
    // The min node is easily found as the first element in the array.
    HuffmanNode *min = heap[0]; 

    // Place this node at the very end of the array, and decrement the size of the priority queue.
    // This effectively removes the node from the priority queue.
    swap(0, size - 1);
    size--;

    // Fix up the heap now by calling minHeapify.
    minHeapify(0);
    return min;
}

/*
 * Method for getting the size of the priority queue.
 */
int PriorityQueue::getSize()
{
    return size;
}
