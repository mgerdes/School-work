package Lists;

import Storage.WordStorage;
import Node.*;

// This is the basic linked list approach.
// Here we just put any new word to the front of the list and any word that is already in the list 
// simply has its count incremented.

public class LinkedList implements WordStorage {
    private long numberOfComparisons;
    private long numberOfReferenceChanges;
    private int wordCount;
    private int distinctWordCount;
    private Node front;    

    public LinkedList() {
        // Initialize all counts and set front to null, so the list is empty.
        numberOfComparisons = numberOfReferenceChanges = 0;
        wordCount = distinctWordCount = 0;
        front = null;
    }

    public void insertWord(String word) {
        // This method will insert a word into the list.
        // The find method will attempt to find the given word in the list. If it finds the word then it returns the node that the word 
        // is in, if it does not find the node then it returns null.
        Node wordNode = this.find(word); 
        if (wordNode == null) {
            // If wordNode is null then the word does not exist in the list, so we create a new node with this word and add
            // it to the front of the list.
            this.insert(new Node(word)); 
        } else {
            // We found the word so simply increment the nodes that contains the word's count.
            wordNode.incrementCount();
        }
    }

    public void insert(Node node) {
        // Thie method will insert a node to the front of the list.
        if (this.isEmpty()) {
            // If the list is empty then we set the node to be the front of the list.
            front = node;
            numberOfReferenceChanges++;
        } else {
            // The list is not empty so we link the node to the front node, then set the node to be the front of the list.
            node.setLink(front);
            front = node;
            numberOfReferenceChanges+=2;
        }
    }

    public Node find(String s) {
        // This method will attempt to find a string in the list.
        // First we loop through the list.
        Node curNode = front;
        while (curNode != null) { 
            if (curNode.getWord().equals(s)) {
                // If we found the word then we return the node that contains this node.
                return curNode;
            }
            numberOfComparisons++;
            curNode = curNode.getLink();
        }
        // If we didn't find the word then we return null.
        return null;
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

    public long getNumberOfReferenceChanges() {
        return numberOfReferenceChanges;
    }

    public long getNumberOfComparisons() {
        return numberOfComparisons;
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
        return "Linked List";
    }

    public String toString() {
        // This method converts the list to a string and then returns that string.
        // To do this it traverses through the list and then adds information about each node o the string.
        String s = "";
        Node curNode = front;
        while (curNode != null) {
            s += curNode.getWord() + "\n";
            curNode = curNode.getLink();
        }
        return s;
    }
}
