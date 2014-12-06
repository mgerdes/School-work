package Lists;

import WordStorage.WordStorage;
import Node.*;

public class SortedLinkedList implements WordStorage {
    public String approachName = "Sorted List";
    private int numberOfComparisons;
    private int numberOfReferenceChanges;
    private int wordCount;
    private int distinctWordCount;
    private Node front;

    public SortedLinkedList() {
        numberOfComparisons = numberOfReferenceChanges = 0;
        wordCount = distinctWordCount = 0;
        front = new Node("AAAAAAA");
        front.setLink(new Node("zzzzzzz"));
    }

    public void insertWord(String s) {
        Node curNode = front.getLink();
        Node prevNode = front;
        while (s.compareTo(curNode.getWord()) > 0) {
            prevNode = curNode;
            curNode = curNode.getLink();
        }
        if (s.equals(curNode.getWord())) {
            curNode.incrementCount();
            numberOfComparisons++;
        } else {
            Node wordNode = new Node(s);
            prevNode.setLink(wordNode);
            wordNode.setLink(curNode);
            numberOfReferenceChanges += 2;
        }
    }

    public void add(Node node) {
        Node curNode = front;
        Node prevNode = front;
        while (node.getWord().compareTo(curNode.getWord()) > 0) {
            prevNode = curNode;
            curNode = curNode.getLink();
        }
        prevNode.setLink(node);
        node.setLink(curNode);
    }

    public Node find(String s) {
        Node curNode = front;
        while (s.compareTo(curNode.getWord()) > 0) {
            curNode = curNode.getLink();
        }
        return curNode;
    }

    public boolean isEmpty() {
        return front == null;
    }

    public void findWordAndDistinctWordCounts() {
        wordCount = 0;
        distinctWordCount = 0;

        Node curNode = front.getLink();
        while (curNode.getLink() != null) {
            wordCount += curNode.getCount(); 
            distinctWordCount++;
            curNode = curNode.getLink();
        }
    }

    public int getNumberOfRefenceChanges() {
        return numberOfReferenceChanges;
    }

    public int getNumberOfComparisons() {
        return numberOfComparisons;
    }

    public String metrics() {
        findWordAndDistinctWordCounts();
        return String.format("Total Word Count: %d.\n"
                           + "Distinct Word Count: %d.\n"
                           + "Number Of Comparisons: %d.\n"
                           + "Number Of Reference Changes: %d.",wordCount, distinctWordCount 
                                                               ,numberOfComparisons, numberOfReferenceChanges);
    }

    public String approachName() {
        return "Sorted Linked List";
    }

    public String toString() {
        String s = "";
        Node curNode = front.getLink();
        while (!curNode.getWord().equals("zzzzzzz")) {
            s += curNode.getWord() + "(" + curNode.getCount() + "), ";
            curNode = curNode.getLink();
        }
        return s;
    }
}

