package Node;

// This is my node class.
// It works for both linked-lists and binary trees.
// It contains a String object to store the word.
// It also contains a count integer to store the amount of times the word occured.

public class Node {
    private Node link;
    private Node leftChild;
    private Node rightChild;
    private String word;
    private int count;

    public Node(String word) {
        this.word = word;
        this.count = 1;
        this.link = null;
    }

    public void incrementCount() {
        this.count++;
    }

    public void setLink(Node link) {
        this.link = link;
    }

    public void setLeftChild(Node leftChild) {
        this.leftChild = leftChild;
    }

    public void setRightChild(Node rightChild) {
        this.rightChild = rightChild;
    }
    
    public String getWord() {
        return this.word;
    }

    public Node getLink() {
        return this.link;
    }

    public Node getLeftChild() {
        return this.leftChild;
    }

    public Node getRightChild() {
        return this.rightChild;
    }

    public int getCount() {
        return this.count;
    }
}
