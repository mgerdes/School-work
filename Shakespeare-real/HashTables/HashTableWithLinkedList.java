package HashTables;

import Storage.WordStorage;
import Lists.LinkedList;

// This implementation is a Hash Table that solves collisions using chaining.
// The hash table essentially consists of a big array where each of the elements contains a linked list.
// The hash function I used was found online at http://research.cs.vt.edu/AVresearch/hashing/strings.php and it was created by Clifford Shaffer. 
// So what happens is the string is converted to an int, then it is placed in the linked list that this int points to.
// This creates alot of linked lists but each of these will be fairly small.

public class HashTableWithLinkedList implements WordStorage {
    private int wordCount;
    private int distinctWordCount;
    private long numberOfComparisons;
    private long numberOfReferenceChanges;
    private int tableSize;
    private LinkedList[] table; // The hash table consists of "buckets" of linked lists.

    public HashTableWithLinkedList(int tableSize) {
        numberOfComparisons = numberOfReferenceChanges = 0;
        wordCount = distinctWordCount = 0; // Begin with a word count and distinct word count of 0.
        this.tableSize = tableSize; // The user picks how big the table should be and we set that here.
        table = new LinkedList[tableSize]; // Here we create the table with the given size.

        // Here we initialize our table by going to each of the "buckets" and instantiating a new linked list.
        for (int i = 0; i < tableSize; i++) {
            table[i] = new LinkedList();
        }
    }

    public void insertWord(String word) {
        // This method adds a given string to our hash table.
        // To do this we simply calculate the position it should be in, then put it in the linked-list at this position in the table.
        int position = hashCode(word); // Find the position of the word.
        table[position].insertWord(word); // Insert the word into the linked list at the previously calculated position.
    }

    public void findWordAndDistinctWordCounts() {
        // This method finds the total word count and distinct word count of the file.
        // First start the counts at zero.
        wordCount = 0;
        distinctWordCount = 0;
        numberOfComparisons = 0;
        numberOfReferenceChanges = 0;

        // Now go to each "bucket" in the table and get the word count and distinct word count of each of these linked lists.
        for (int i = 0; i < tableSize; i++) {
            table[i].findWordAndDistinctWordCounts();
            distinctWordCount += table[i].getDistinctWordCount();
            wordCount += table[i].getWordCount();
            numberOfComparisons += table[i].getNumberOfComparisons();
            numberOfReferenceChanges += table[i].getNumberOfReferenceChanges();
        }
    }

    public String metrics() {
        // To find the metrics we first need to calculate them all and then return a string containing them.
        findWordAndDistinctWordCounts();
        return String.format("Total Word Count: %d.\n"
                           + "Distinct Word Count: %d.\n"
                           + "Number of Comparisons: %d.\n"
                           + "Number of Reference Changes: %d.", wordCount, distinctWordCount, numberOfComparisons, numberOfReferenceChanges);
    }

    public String approachName() {
        // This method returns the name of this approach.
        return "Hash Table With Linked List";
    }

    public int hashCode(String word) {
        // This hash function was created by Clifford A. Shaffer.
        // More info here: http://research.cs.vt.edu/AVresearch/hashing/strings.php
        int intLength = word.length() / 4;
        long sum = 0;
        for (int j = 0; j < intLength; j++) {
            char c[] = word.substring(j * 4, (j * 4) + 4).toCharArray();
            long mult = 1;
            for (int k = 0; k < c.length; k++) {
                sum += c[k] * mult;
                mult *= 256;
            }
        }
        char c[] = word.substring(intLength * 4).toCharArray();
        long mult = 1;
        for (int k = 0; k < c.length; k++) {
            sum += c[k] * mult;
            mult *= 256;
        }
        return(Math.abs((int)sum) % tableSize);
    }
}
