package Lists;

import Storage.WordStorage;
import Node.*;

public class LinkedList implements WordStorage {
    private int numberOfComparisons;
    private int numberOfReferenceChanges;
    private int wordCount;
    private int distinctWordCount;
    private Node front;    

    public LinkedList() {
        numberOfComparisons = numberOfReferenceChanges = 0;
        wordCount = distinctWordCount = 0;
        front = null;
    }

    public void insertWord(String word) {
        Node wordNode = this.find(word);
        if (wordNode == null) {
           this.insert(new Node(word)); 
        } else {
            wordNode.incrementCount();
        }
    }

    public void insert(Node node) {
        if (this.isEmpty()) {
            front = node;
            numberOfReferenceChanges++;
        } else {
            node.setLink(front);
            front = node;
            numberOfReferenceChanges++;
        }
    }

    public Node find(String s) {
        Node curNode = front;
        while (curNode != null) {
            if (curNode.getWord().equals(s)) {
                numberOfComparisons++;
                return curNode;
            }
            curNode = curNode.getLink();
        }
        return null;
    }

    public boolean isEmpty() {
        return front == null;
    }

    public void findWordAndDistinctWordCounts() {
        wordCount = 0;
        distinctWordCount = 0;

        Node curNode = front;
        while (curNode != null) {
            wordCount += curNode.getCount(); 
            distinctWordCount++;
            curNode = curNode.getLink();
        }
    }

    public int getDistinctWordCount() {
        return distinctWordCount;
    }

    public int getWordCount() {
        return wordCount;
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
        return "Linked List";
    }

    public String toString() {
        String s = "";
        Node curNode = front;
        while (curNode != null) {
            s += curNode.getWord() + "\n";
            curNode = curNode.getLink();
        }
        return s;
    }
}
