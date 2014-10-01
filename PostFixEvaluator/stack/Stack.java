package stack;

public class Stack<T> implements StackInterface<T> {
	Node<T> topOfStack;

	public Stack() {
		topOfStack = new Node<T>(null);
	}

	public void push(T element) {
		Node<T> newNode = new Node<T>(element);
		newNode.link = topOfStack;
		topOfStack = newNode; 
	}

	public T pop() {
		if (this.isEmpty()) {
			throw new StackUnderflowExcpetion("UNDERFLOW"); 
		}

		Node<T> returnNode = topOfStack;
		topOfStack = topOfStack.link;	
		return returnNode.contents;
	}

	public T top() {
		if (this.isEmpty()) {
			throw new StackUnderflowExcpetion("UNDERFLOW"); 
		}

		return topOfStack.contents;
	}

	public boolean isEmpty() {
		return topOfStack.link == null;
	}
}

class Node<T> {
	T contents;
	Node<T> link;

	Node(T contents) {
		this.contents = contents;
		link = null;
	}

	@Override
	public String toString() {
		return contents.toString();
	}
}

interface StackInterface<T> {
	void push(T element);
	T pop() throws StackUnderflowExcpetion;
	boolean isEmpty();
}

@SuppressWarnings("serial")
class StackUnderflowExcpetion extends RuntimeException {
	public StackUnderflowExcpetion() {
		super();
	}

	public StackUnderflowExcpetion(String message) {
		super(message);
	}
}
