import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;

import WordStorage.WordStorage;
import Node.Node;
import Lists.LinkedList;
import Lists.SortedLinkedList;
import Lists.HeavyHandedSelfAdjustingList;
import Lists.MoreElegeantSelfAdjustingList;
import Trees.BinaryTree;
import HashTable.HashTable;

public class Shakespeare {
    static final String FILE_NAME = "Hamlet.txt";
    static File file = new File(FILE_NAME);

    public static void main(String[] args) throws FileNotFoundException {
        // Linked List Approach.
        run(new LinkedList());

        // Sorted Linked List Approach.
        run(new SortedLinkedList());

        // Heavy Handed Self-Adjusting List Approach.
        run(new HeavyHandedSelfAdjustingList());

        // More Elegeant Self-Adjusting List Approach.
        run(new MoreElegeantSelfAdjustingList());

        // Binary Tree Approach.
        run(new BinaryTree());

        // Hash Table Approach.
        int tableSize = 1000;
        run(new HashTable(tableSize));
    }

    public static void run(WordStorage storage) throws FileNotFoundException {
        Scanner in = new Scanner(file);
        Long startTime = System.currentTimeMillis();
        while (in.hasNext()) {
            String s = format(in.next());
            if (s.equals("")) continue;
            storage.insertWord(s);
        }
        double runTime = convertMilliSecondsToSeconds(System.currentTimeMillis() - startTime);
        System.out.println(storage.approachName() + " Approach:\n" + storage.metrics());
        System.out.println("Runtime: " + runTime + " seconds.\n");
    }

    public static double convertMilliSecondsToSeconds(long milliSeconds) {
        return (milliSeconds / 1000D);
    }

    public static String format(String s) {
        return s.replaceAll("[^a-zA-Z]", "").toLowerCase();
    }
}
