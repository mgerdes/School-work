package Trees;

import Node.*;

public class BinaryTree {
    private int numberOfComparisons;
    private int numberOfReferenceChanges;
    private int wordCount;
    private int distinctWordCount;
    private Node parent;

    public BinaryTree() {
        numberOfComparisons = numberOfReferenceChanges = 0;
        wordCount = distinctWordCount = 0;
        parent = null;
    }

    public void insertWord(String s) {
        if (this.isEmpty()) {
            parent = new Node(s);
        } else {
            Node curNode = parent;
            Node prevNode = null;
            while (curNode != null) {
                prevNode = curNode;
                if (s.equals(curNode.getWord())) {
                    curNode.incrementCount();
                    return;
                } else if (s.compareTo(curNode.getWord()) < 0) {
                    curNode = curNode.getLeftChild();
                    if (curNode == null) {
                        prevNode.setLeftChild(new Node(s));
                    }
                } else {
                    curNode = curNode.getRightChild();
                    if (curNode == null) {
                        prevNode.setRightChild(new Node(s));
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
        findWordAndDistinctWordCounts();
        return String.format("Total Word Count: %d.\n"
                           + "Distinct Word Count: %d.\n"
                           + "Number Of Comparisons: %d.\n"
                           + "Number Of Reference Changes: %d.",wordCount, distinctWordCount 
                                                               ,numberOfComparisons, numberOfReferenceChanges);
    }

    public boolean isEmpty() {
        return parent == null;
    }
}
