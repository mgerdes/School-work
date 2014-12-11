package Lists;

import Storage.WordStorage;
import Node.*;

public class MoreElegeantSelfAdjustingList implements WordStorage {
    private int numberOfComparisons;
    private int numberOfReferenceChanges;
    private int wordCount;
    private int distinctWordCount;
    private Node front;    

    public MoreElegeantSelfAdjustingList() {
        numberOfComparisons = numberOfReferenceChanges = 0;
        wordCount = distinctWordCount = 0;
        front = null;
    }

    public void insertWord(String s) {
        if (this.isEmpty()) {
            front = new Node(s);
        } else {
            Node curNode = front;
            Node prevNode = null;
            Node prevPrevNode = null;
            while (curNode != null) {
                if (curNode.getWord().equals(s)) {
                    curNode.incrementCount();
                    if (prevPrevNode != null) {
                        prevPrevNode.setLink(curNode);
                        prevNode.setLink(curNode.getLink());
                        curNode.setLink(prevNode);
                    } else if (prevNode != null) {
                        prevNode.setLink(curNode.getLink());
                        curNode.setLink(front);
                        front = curNode;
                    }
                    return;
                }
                prevPrevNode = prevNode;
                prevNode = curNode;
                curNode = curNode.getLink();
            }
            Node wordNode = new Node(s);
            wordNode.setLink(front);
            front = wordNode;
        }
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

    public String metrics() {
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
        String s = "";
        Node curNode = front;
        while (curNode != null) {
            s += curNode.getWord() + "(" + curNode.getCount() + "), ";
            curNode = curNode.getLink();
        }
        return s;
    }
}
