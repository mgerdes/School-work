#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE

#include "huffman_node.h"
#include "stdio.h"

class PriorityQueue 
{
    private:
        int size;
        HuffmanNode **heap;

        int parent(int i);

        int leftChild(int i);

        int rightChild(int i);

        void minHeapify(int i);

        void swap(int i, int j);
        
    public:
        PriorityQueue(HuffmanNode **nodes, int size);

        ~PriorityQueue();

        void insert(HuffmanNode *huffmanNode);

        HuffmanNode *extractMin();

        int getSize();
};

#endif // PRIORITY_QUEUE
