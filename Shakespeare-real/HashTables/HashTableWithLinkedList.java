package HashTables;

import Storage.WordStorage;
import Lists.LinkedList;

public class HashTableWithLinkedList implements WordStorage {
    private int wordCount;
    private int distinctWordCount;
    private int tableSize;
    private LinkedList[] table;

    public HashTableWithLinkedList(int tableSize) {
        wordCount = distinctWordCount = 0;
        this.tableSize = tableSize;
        table = new LinkedList[tableSize];

        for (int i = 0; i < tableSize; i++) {
            table[i] = new LinkedList();
        }
    }

    public void insertWord(String word) {
        int position = hashCode(word);
        table[position].insertWord(word);
    }

    public void findWordAndDistinctWordCounts() {
        wordCount = 0;
        distinctWordCount = 0;

        for (int i = 0; i < tableSize; i++) {
            table[i].findWordAndDistinctWordCounts();
            distinctWordCount += table[i].getDistinctWordCount();
            wordCount += table[i].getWordCount();
        }
    }

    public String metrics() {
        findWordAndDistinctWordCounts();
        return String.format("Total Word Count: %d.\n"
                           + "Distinct Word Count: %d.", wordCount, distinctWordCount);
    }

    public String approachName() {
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
