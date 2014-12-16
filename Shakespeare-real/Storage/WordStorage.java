package Storage;

// This is an interface for classes that store words.
// These classes need to implement a way of inserting the word,
// a way for returning the metrics, and a method that returns the name of the approach.
// This makes it convenient when testing each of the different approaches.

public interface WordStorage {
    public void insertWord(String word);
    public String metrics();
    public String approachName();
}
