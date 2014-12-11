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
    static final String FILE_NAME = "Hamlet.txt";
    static File file = new File(FILE_NAME);

    public static void main(String[] args) throws FileNotFoundException {
        run(new LinkedList());
        run(new SortedLinkedList());
        run(new HeavyHandedSelfAdjustingList());
        run(new MoreElegeantSelfAdjustingList());
        run(new BinaryTree());
        System.out.print(storage);int tableSize = 1000;
        run(new HashTableWithLinkedList(tableSize));
    }

    public static void run(WordStorage storage) throws FileNotFoundException {
        Scanner in = new Scanner(file);
        in.useDelimiter("\\s|--");
        Long startTime = System.currentTimeMillis();
        while (in.hasNext()) {
            String s = format(in.next());
            if (s.equals("")) continue;
            storage.insertWord(s);
        }
        System.out.println(storage);
        double runTime = convertMilliSecondsToSeconds(System.currentTimeMillis() - startTime);
        System.out.println(storage.approachName() + " Approach:\n" + storage.metrics());
        System.out.println("Runtime: " + runTime + " seconds.\n");
    }

    public static double convertMilliSecondsToSeconds(long milliSeconds) {
        return (milliSeconds / 1000D);
    }

    public static String format(String s) {
        return s.toLowerCase().replaceAll("^[^a-z]*", "").replaceAll("[^a-z]*$", "");
    }
}
