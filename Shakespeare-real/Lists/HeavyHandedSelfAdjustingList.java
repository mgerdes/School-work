package Lists;

import Storage.WordStorage;
import Node.*;

// This is the "heavy handed" implementation of the self-adjusting linked-list.
// It works by placing all new nodes to the front of the list. And is any word is added that is already in the list,
// then the node containing this string is sent to the front of the list.

public class HeavyHandedSelfAdjustingList implements WordStorage {
    private long numberOfComparisons;
    private long numberOfReferenceChanges;
    private int wordCount;
    private int distinctWordCount;
    private Node front;    

    public HeavyHandedSelfAdjustingList() {
        // Initialize all counts and set front to null, so the list is empty.
        numberOfComparisons = numberOfReferenceChanges = 0;
        wordCount = distinctWordCount = 0;
        front = null;
    }

    public void insertWord(String s) {
        // This method will add a string to this list.
        if (this.isEmpty()) {
            // If the list is empty then we just put our node at the front of the list. 
            front = new Node(s);
        } else {
            // If were here then the list is not empty.
            // So before we insert the word we have to first check to see if the word is in the list.
            Node curNode = front;
            Node prevNode = null;
            while (curNode != null) {
                // Here we traverse through the entire list to try and find the word.
                numberOfComparisons++;
                if (curNode.getWord().equals(s)) {  
                    // If were here then we found a node in the list that contains the word we want to add. So we simply increment this nodes count.
                    curNode.incrementCount();
                    if (prevNode != null) {
                        // If prevnode != null then that means the node we want to add is not the first node in the list.
                        // So we "splice" out curNode by setting the link of the previous node to be the curNodes link.
                        prevNode.setLink(curNode.getLink()); 
                        // We then have the curNode links be the first node in the list.
                        curNode.setLink(front);
                        // And finally we set the curNode to be the front of the list.
                        front = curNode;
                        numberOfReferenceChanges += 3;
                    }
                    // If prevNode == null then the curNode is already the front of the list so we don't have to do anything except increment the count.
                    // So we return.
                    return;
                }
                // We do this to go to the next link in the list.
                prevNode = curNode;
                curNode = curNode.getLink();
            }
            // If we get to this point then the word does not exist in the list.
            // So we simply put the word into a node and add the node to the front of the list.
            Node wordNode = new Node(s);
            wordNode.setLink(front);
            front = wordNode;
            numberOfReferenceChanges += 2;
        }
    }

    public boolean isEmpty() {
        return front == null;
    }

    public void findWordAndDistinctWordCounts() {
        // This methods finds the total word and distinct word count.
        // Start them both at zero.
        wordCount = 0;
        distinctWordCount = 0;

        // Traverse through the entire list and count the number of nodes, which is the distinct word count,
        // and count each nodes total count, which is the total word count.
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
        return "Total Word Count: " + wordCount + ".\n" + 
                "Distinct Word Count: " + distinctWordCount + ".\n" +
                "Number Of Comparisons: " + numberOfComparisons + ".\n" +
                "numberOfReferenceChanges: " + numberOfReferenceChanges; 
    }

    public String approachName() {
        return "Heavy Handed Self-Adjusting List";
    }

    public String toString() {
        // This method converts the list to a string and then returns that string.
        // To do this it traverses through the list and then adds information about each node o the string.
        String s = "";
        Node curNode = front;
        int i = 0;
        while (i++ < 50 && curNode != null) {
            s += curNode.getWord() + " " + curNode.getCount() + "\n";
            curNode = curNode.getLink();
        }
        return s;
    }
}
