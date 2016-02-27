/*
 * Name : Michael Gerdes
 * Date : February 20, 2016
 * Class : Non-Linear Data Structures
 *
 * This file contains the interface for a priority queue.
 */

#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE

#include "huffman_node.h"

class PriorityQueue 
{
    private:
        // Keep track of the size of the heap and the array that represents it.
        int size;
        HuffmanNode **heap;

        /*
         * Methods for moving around in the tree (which is really an array).
         */
        int parent(int i);
        int leftChild(int i);
        int rightChild(int i);

        // Method to fix up a heap.
        void minHeapify(int i);

        // Method to swap two indices in the heap array.
        void swap(int i, int j);
        
    public:
        // Constructor takes in a maximum size for the priority queue.
        PriorityQueue(int size);

        ~PriorityQueue();

        // Insert a huffmanNode into the priority queue.
        void insert(HuffmanNode *huffmanNode);

        // Extract the huffmanNode with the smallest weight.
        HuffmanNode *extractMin();

        // Returns the size of the priority queue.
        int getSize();
};

#endif // PRIORITY_QUEUE
