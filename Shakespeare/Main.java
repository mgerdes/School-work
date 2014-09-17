
import java.util.*;

class BinaryTree {

	int height;
	int numOfValues = 1;
	BinaryLeaf root;

	BinaryTree(String word) {
		this.root = new BinaryLeaf(word);
	}

	BinaryTree(BinaryLeaf root) {
		this.root = root;
	}

	void addValue(String value) {
		addLeaf(new BinaryLeaf(value));
	}

	void addLeaf(BinaryLeaf leaf) {
		addLeaf(root, leaf, this);
	}

	static void addLeaf(BinaryLeaf root, BinaryLeaf leaf, BinaryTree tree) {
		if (leaf.value.equals(root.value)) {
			root.occurences++;
			leaf = null;
			return;
		}

		if (leaf.value.compareToIgnoreCase(root.value) > 0) {
			if (root.rightChild == null) {
				tree.numOfValues++;
				root.rightChild = leaf;
			} else {
				addLeaf(root.rightChild, leaf, tree);
			}
		} else {
			if (root.leftChild == null) {
				tree.numOfValues++;
				root.leftChild = leaf;
			} else {
				addLeaf(root.leftChild, leaf, tree);
			}
		}
	}

	int getOccurences(String value) {
		return getOccurences(root, value);
	}

	static int getOccurences(BinaryLeaf curLeaf, String value) {
		if (curLeaf != null) {
			if (curLeaf.value.equals(value)) {
				return curLeaf.occurences;
			}
			if (value.compareToIgnoreCase(curLeaf.value) > 0) {
				return getOccurences(curLeaf.rightChild, value);
			} else {
				return getOccurences(curLeaf.leftChild, value);
			}
		}
		return -1;
	}

	boolean contains(String value) {
		return contains(root, value);
	}

	static boolean contains(BinaryLeaf curLeaf, String value) {
		if (curLeaf != null) {
			if (curLeaf.value.equals(value)) {
				return true;
			}
			if (value.compareToIgnoreCase(curLeaf.value) > 0) {
				return contains(curLeaf.rightChild, value);
			} else {
				return contains(curLeaf.leftChild, value);
			}
		}
		return false;
	}

}

class BinaryLeaf {

	String value;
	int occurences = 1;
	BinaryLeaf rightChild;
	BinaryLeaf leftChild;

	BinaryLeaf(String value) {
		this.value = value;
	}

}

class HashTable {

	int size;
	BinaryTree table[];

	HashTable(int size) {
		this.size = size;
		table = new BinaryTree[size];
	}

	int hashValue(String word) {

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

		return(Math.abs((int)sum) % size);
	}

	void addValue(String word) {
		int hash = hashValue(word);

		if (table[hash] == null) {
			table[hash] = new BinaryTree(word);
		} else {
			table[hash].addValue(word);
		}
	}

	int getCount(String word) {
		int hash = hashValue(word);

		if (table[hash] != null) {
			return table[hash].getOccurences(word);
		} else {
			return -1;
		}
	}

	int uniqueWords() {
		int uniqueWordCount = 0;
		int max = 0;

		for (int i = 0; i < size; i++) {
			if (table[i] != null) {
				if (table[i].numOfValues > max) max = table[i].numOfValues;
				uniqueWordCount += table[i].numOfValues;
			}
		}

		System.out.println(max);

		return uniqueWordCount;
	}

}

public class Main {

	public static void main(String[] args) {

		Scanner input = new Scanner(System.in);

		HashTable table = new HashTable(20000);
		BinaryTree tree = new BinaryTree("the");

		int totalWords = 0;

		while (input.hasNext()) {
			tree.addValue(input.next().replaceAll("[^a-zA-Z0-9]", ""));
			totalWords++;
		}

		System.out.println(totalWords);
		//System.out.println(table.uniqueWords());

	}

}
