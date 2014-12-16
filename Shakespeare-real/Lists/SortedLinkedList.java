package Lists;

import Storage.WordStorage;
import Node.*;

// This is the sorted linked-list approach.
// I used a header node containing "AAAAAAA" and a trailer node containing "zzzzzzz" to ensure that all of the operations
// take place in the middle of the list.

public class SortedLinkedList implements WordStorage {
    public String approachName = "Sorted List";
    private long numberOfComparisons;
    private long numberOfReferenceChanges;
    private int wordCount;
    private int distinctWordCount;
    private Node front;

    public SortedLinkedList() {
        // Initialize all counts and set front to null, so the list is empty.
        numberOfComparisons = numberOfReferenceChanges = 0;
        wordCount = distinctWordCount = 0;
        front = new Node("AAAAAAA");
        front.setLink(new Node("zzzzzzz"));
    }

    public void insertWord(String s) {
        // This method will insert a word into the list.
        // It needs a prevNode reference in order to place the node into the correct spot in the list.
        Node curNode = front.getLink();
        Node prevNode = front;
        // Below we traverse the list until we get to a node that contains a word that is greater then the word we want to add.
        while (s.compareTo(curNode.getWord()) > 0) {
            numberOfComparisons++;
            prevNode = curNode;
            curNode = curNode.getLink();
        }
        if (s.equals(curNode.getWord())) {
            // If the node we got to is the same as the word we want to add, then we simply increment the nodes count.
            curNode.incrementCount();
        } else {
            // If not then we have to insert the word right before this node.
            Node wordNode = new Node(s);
            prevNode.setLink(wordNode);
            wordNode.setLink(curNode);
            numberOfReferenceChanges += 2;
        }
        numberOfComparisons++;
    }

    public boolean isEmpty() {
        return front == null;
    }

    public void findWordAndDistinctWordCounts() {
        // this method finds the word and distinct word count of the list.
        // To do this it traverses through the entire list and counts the number of nodes, which is the distinct word count,
        // and it counts each nodes total count, which is the total word count.
        wordCount = 0;
        distinctWordCount = 0;

        Node curNode = front.getLink();
        while (curNode.getLink() != null) {
            wordCount += curNode.getCount(); 
            distinctWordCount++;
            curNode = curNode.getLink();
        }
    }

    public String metrics() {
        // To find the metrics we first need to calculate them all and then return a string containing them.
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
        // This method converts the list to a string and then returns that string.
        // To do this it traverses through the list and then adds information about each node o the string.
        String s = "";
        Node curNode = front.getLink();
        while (!curNode.getWord().equals("zzzzzzz")) {
            s += curNode.getWord() + "(" + curNode.getCount() + "), ";
            curNode = curNode.getLink();
        }
        return s;
    }
}

