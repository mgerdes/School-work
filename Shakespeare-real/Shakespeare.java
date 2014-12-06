import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;

import Node.Node;
import Lists.LinkedList;
import Lists.SortedLinkedList;
import Lists.HeavyHandedSelfAdjustingList;
import Lists.MoreElegeantSelfAdjustingList;
import Trees.BinaryTree;

class Main {
    static final String FILE_NAME = "Shakespeare.txt";

    public static void main(String[] args) throws FileNotFoundException {
        File file = new File(FILE_NAME);
        Scanner in = new Scanner(file);

        // Linked List Approach.
        Long startTime = System.currentTimeMillis();
        LinkedList l = new LinkedList();
        while (in.hasNext()) {
            String s = format(in.next());
            if (s.equals("")) {
                continue;
            }
            l.insertWord(s);
        }
        System.out.println("Linked List Approach:\n" + l.metrics());
        double runTime = convertMilliSecondsToSeconds(System.currentTimeMillis() - startTime);
        System.out.printf("Time: %f seconds.\n\n", runTime);

        in = new Scanner(file);

        // Sorted Linked List Approach.
        startTime = System.currentTimeMillis();
        SortedLinkedList sl = new SortedLinkedList();
        while (in.hasNext()) {
            String s = format(in.next());
            if (s.equals("")) {
                continue;
            }
            sl.insertWord(s);
        }
        System.out.println("Sorted Linked List Approach:\n" + sl.metrics());
        runTime = convertMilliSecondsToSeconds(System.currentTimeMillis() - startTime);
        System.out.printf("Time: %f seconds.\n\n", runTime);

        in = new Scanner(file);

        // Heavy Handed Self-Adjusting List Approach.
        startTime = System.currentTimeMillis();
        HeavyHandedSelfAdjustingList hl = new HeavyHandedSelfAdjustingList();
        while (in.hasNext()) {
            String s = format(in.next());
            if (s.equals("")) {
                continue;
            }
            hl.insertWord(s);
        }
        System.out.println("Heavy Handed Self-Adjusting List Approach:\n" + hl.metrics());
        runTime = convertMilliSecondsToSeconds(System.currentTimeMillis() - startTime);
        System.out.printf("Time: %f seconds.\n\n", runTime);

        in = new Scanner(file);
        
        // More Elegeant Self-Adjusting List Approach.
        startTime = System.currentTimeMillis();
        MoreElegeantSelfAdjustingList el = new MoreElegeantSelfAdjustingList();
        while (in.hasNext()) {
            String s = format(in.next());
            if (s.equals("")) {
                continue;
            }
            el.insertWord(s);
        }
        System.out.println("More Elegeant Self-Adjusting List Approach:\n" + el.metrics());
        runTime = convertMilliSecondsToSeconds(System.currentTimeMillis() - startTime);
        System.out.printf("Time: %f seconds.\n\n", runTime);

        in = new Scanner(file);

        // Binary Tree Approach.
        startTime = System.currentTimeMillis();
        BinaryTree b = new BinaryTree();
        while (in.hasNext()) {
            String s = format(in.next());
            if (s.equals("")) {
                continue;
            }
            b.insertWord(s);
        }
        System.out.println("Binary Tree Approach:\n" + b.metrics());
        runTime = convertMilliSecondsToSeconds(System.currentTimeMillis() - startTime);
        System.out.printf("Time: %f seconds.\n", runTime);
    }

    public static double convertMilliSecondsToSeconds(long milliSeconds) {
        return (milliSeconds / 1000D);
    }

    public static String format(String s) {
        return s.replaceAll("[^a-zA-Z]", "").toLowerCase();
    }
}
