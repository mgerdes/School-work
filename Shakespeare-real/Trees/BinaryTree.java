package Trees;

import Storage.WordStorage;
import Node.Node;

// This is the BinaryTree approach for storing the words in Hamlet.
// It works like any other binary tree where everything to the left of a node is less then that node
// and everything to the right of a node is greater than that node.
// This gives us a huge advantage because it allows us to roughly cut the tree in half after searching each node.
// So searching for a node will be far faster.

public class BinaryTree implements WordStorage {
    private long numberOfComparisons;
    private long numberOfReferenceChanges;
    private int wordCount;
    private int distinctWordCount;
    private Node parent;

    public BinaryTree() {
        // Initialize all counts and set the parent node to null, so the tree is empty.
        numberOfComparisons = numberOfReferenceChanges = 0;
        wordCount = distinctWordCount = 0;
        parent = null;
    }

    public void insertWord(String s) {
        // This method inserts a word into the binary tree.
        if (this.isEmpty()) {
            // If the tree is empty then the string becomes the parent of the tree.
            parent = new Node(s);
        } else {
            // If the tree is not empty then we need to do some searching to find where the string belongs.
            Node curNode = parent;
            Node prevNode = null;
            // First we need to find out whether or not the word is in the the tree.
            // Looking for the string is similar to how the linked-list works except now there are 2 different links to follow.
            // And we have to be careful as to which we choose.
            while (curNode != null) {
                prevNode = curNode;
                numberOfComparisons+=2; // +=2 because we have to check if it's equal and do a compareTo
                if (s.equals(curNode.getWord())) {
                    // If we get here then we found the word we want to add so just increment its count and return.
                    curNode.incrementCount();
                    return;
                } else if (s.compareTo(curNode.getWord()) < 0) {
                    // Here we want to follow the left link.
                    curNode = curNode.getLeftChild();
                    if (curNode == null) {
                        // If the curNode is null, then theres nothing left in the tree, so we add our new node as the prevNodes leftChild.
                        prevNode.setLeftChild(new Node(s));
                        numberOfReferenceChanges++;
                    }
                } else {
                    // Here we want to follow the right link.
                    curNode = curNode.getRightChild();
                    if (curNode == null) {
                        // If the curNode is null, then theres nothing left in the tree, so we add our new node as the prevNodes rightChild.
                        prevNode.setRightChild(new Node(s));
                        numberOfReferenceChanges++;
                    }
                }
            }
        }
    }

    public void findWordAndDistinctWordCounts() {
        wordCount = 0;
        distinctWordCount = 0;

        wordCount = wordCount(parent);
    }

    public int wordCount(Node n) {
        if (n != null) {
            distinctWordCount++;
            return n.getCount() + wordCount(n.getLeftChild()) + wordCount(n.getRightChild());
        } else {
            return 0;
        }
    }

    public String metrics() {
        // this method finds the word and distinct word count of the tree.
        // To do this it traverses through the entire tree and counts the number of nodes, which is the distinct word count,
        // and it counts each nodes total count, which is the total word count.
        findWordAndDistinctWordCounts();
        return String.format("Total Word Count: %d.\n"
                           + "Distinct Word Count: %d.\n"
                           + "Number Of Comparisons: %d.\n"
                           + "Number Of Reference Changes: %d.",wordCount, distinctWordCount 
                                                               ,numberOfComparisons, numberOfReferenceChanges);
    }

    public String approachName() {
        return "Binary Tree";
    }

    public boolean isEmpty() {
        return parent == null;
    }
}
