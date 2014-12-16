package Lists;

import Storage.WordStorage;
import Node.*;

// This is the "more elegeant" self-adjusting linked-list approach.
// When we try to insert a word that is already in the list, we increment its count and then move it up one spot in the list.
// If the word is not already in the list then we simply add it to the beginning of the list.

public class MoreElegeantSelfAdjustingList implements WordStorage {
    private long numberOfComparisons;
    private long numberOfReferenceChanges;
    private int wordCount;
    private int distinctWordCount;
    private Node front;    

    public MoreElegeantSelfAdjustingList() {
        // Initialize all counts and set front to null, so the list is empty.
        numberOfComparisons = numberOfReferenceChanges = 0;
        wordCount = distinctWordCount = 0;
        front = null;
    }

    public void insertWord(String s) {
        // This method inserts a word into the list.
        if (this.isEmpty()) {
            // If the list is empty when we put the string in a node and put it at the front.
            front = new Node(s);
        } else {
            // If the list is not empty, then the logic is more complicated.
            // We need 3 different references to move a node up one. A previous node and a previous previous node.
            Node curNode = front;
            Node prevNode = null;
            Node prevPrevNode = null;
            // First we traverse the entire list to try and find if the word is already in the list.
            while (curNode != null) {
                numberOfComparisons++;
                if (curNode.getWord().equals(s)) {
                    // If we get here then we found the word.
                    curNode.incrementCount();
                    // There are 3 different cases
                    if (prevPrevNode != null) {
                        // We get here if prevPrevNode is not null, so this is the "generic" case where the word has atleast 2 words previous to it.
                        prevPrevNode.setLink(curNode);
                        prevNode.setLink(curNode.getLink());
                        curNode.setLink(prevNode);
                        numberOfReferenceChanges+=3;
                    } else if (prevNode != null) {
                        // If we get here then prevPrevNode is null, but prevNode is not null, so the word we want to add is the second word in the list. 
                        prevNode.setLink(curNode.getLink());
                        curNode.setLink(front);
                        front = curNode;
                        numberOfReferenceChanges+=3;
                    }
                    // If all the above cases failed then the word is already at the front of the list, so we don't need to do anything except increment
                    // the count.
                    return;
                }
                // The code below will go to the next node in the list.
                prevPrevNode = prevNode;
                prevNode = curNode;
                curNode = curNode.getLink();
            }
            // If we got here then the word is not in the list, so we create a new node with the word in it and place it at the front of the list.
            Node wordNode = new Node(s);
            wordNode.setLink(front);
            front = wordNode;
            numberOfReferenceChanges+=2;
        }
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
        return "More Elegeant Self-Adjusting List";
    }

    public String toString() {
        // This method converts the list to a string and then returns that string.
        // To do this it traverses through the list and then adds information about each node o the string.
        int i = 0;
        String s = "";
        Node curNode = front;
        while (i++ < 50 && curNode != null) {
            s += curNode.getWord() + " " + curNode.getCount() + "\n";
            curNode = curNode.getLink();
        }
        return s;
    }
}
