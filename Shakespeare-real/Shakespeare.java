import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;

import Storage.WordStorage;
import Lists.LinkedList;
import Lists.SortedLinkedList;
import Lists.HeavyHandedSelfAdjustingList;
import Lists.MoreElegeantSelfAdjustingList;
import Trees.BinaryTree;
import HashTables.HashTableWithLinkedList;

public class Shakespeare {
    static final String FILE_NAME = "Hamlet.txt"; // This is the file name we will read input from.
    static File file = new File(FILE_NAME);

    public static void main(String[] args) throws FileNotFoundException {
        // Here we just create each of the different types of lists and send them to the run method.
        // Test out the Linked-List Approach.
        run(new LinkedList());
        // Test out the Sorted Linked-List Approach.
        run(new SortedLinkedList());
        // Test out the first more "heavy handed" Self-Adjusting Linked-List Approach.
        run(new HeavyHandedSelfAdjustingList());
        // Test out the second more "elegeant" Self-Adjusting Linked-List Approach.
        run(new MoreElegeantSelfAdjustingList());
        // Test out the Binary Tree approach.
        run(new BinaryTree());
        // Test out a Hash Table approach.
        int tableSize = 1000;
        run(new HashTableWithLinkedList(tableSize));
    }

    public static void run(WordStorage storage) throws FileNotFoundException {
        // This method takes in a WordStorage object, which simply stores words.
        // It then adds each of the words from the file to this object and we measure how long this takes.
        // When this is all finished we then print out the lists metrics, i.e. unique word count, reference changes, etc.
        Scanner in = createScanner();
        Long startTime = System.currentTimeMillis(); // Mark the start time to measure the run time.
        // Keep going while the file has more words.
        while (in.hasNext()) { 
            String s = format(in.next()); // Get the next word from the file and format it. I.e. remove not wanted puncuation.
            if (s.equals("")) continue; // If the word is blank, I.e. it equals "", then we do not add this word to the list.
            storage.insertWord(s); // Insert the word we just retrieved to the storage mechanism.
        }
        System.out.println(storage.approachName() + " Approach:\n" + storage.metrics()); // Print out the metrics and approach name.
        Long endTime = System.currentTimeMillis(); // Mark the end time.
        double runTime = (endTime - startTime) / 1000D; // Calculate the run time, which we divide by 1000 to convert from milliseconds to seconds.
        System.out.println("Runtime: " + runTime + " seconds.\n"); // Print out the run time.
    }

    // This method creates the scanner we will use.
    public static Scanner createScanner() throws FileNotFoundException {
        return new Scanner(file).useDelimiter("\\s|--");
    }

    public static String format(String s) {
        // This method will format our string, the regex first regex removes all leading non-letters and the second regex removes all trailing non-letters.
        return s.toLowerCase().replaceAll("^[^a-z]*", "").replaceAll("[^a-z]*$", "");
    }
}
