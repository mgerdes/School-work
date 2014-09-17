import java.util.*;

public class StackTest {
	public static void main(String[] args) {
		UnboundedStack<String> stack = new UnboundedStack<String>();

		stack.push("MYNAMEISMICHAEL");
		stack.push("WOWTHISISCOOL");
		stack.push("HELLO");

		System.out.println(stack.pop());
		System.out.println(stack.pop());
		System.out.println(stack.pop());
		
		BoundedStack<String> stack1 = new BoundedStack<String>();

		stack1.push("HELLO");
		stack1.push("WOW");
		stack1.push("WEREEERE");

		System.out.println(stack1.pop());

	}
}

class BoundedStack<T> implements BoundedStackInterface<T> {
	T[] stack;
	static final int DEFAULT_MAX_SIZE = 10;
	int topIndex, maxSize;
	
	BoundedStack() {
		this(DEFAULT_MAX_SIZE);
	}

	@SuppressWarnings("unchecked")
	BoundedStack(int maxSize) {
		topIndex = -1;
		this.maxSize = maxSize;
		stack = (T[]) new Object[maxSize];	
	}

	public void push(T element) {
		if (this.isFull()) {
			throw new StackOverflowException("OVERFLOW");
		} else {
			stack[++topIndex] = element;
		}
	}

	public T pop() {
		if (this.isEmpty()) {
			throw new StackUnderflowExcpetion("UNDERFLOW");
		}

		return stack[topIndex--];
	}

	public boolean isEmpty() {
		return topIndex == -1;
	}
	
	public boolean isFull() {
		return topIndex == maxSize - 1;
	}
}

class UnboundedStack<T> implements StackInterface<T> {
	Node<T> topOfStack = new Node<T>(null);

	UnboundedStack() {

	}

	public void push(T element) {
		Node<T> newNode = new Node<T>(element);
		newNode.link = topOfStack;
		topOfStack = newNode; 
	}

	public T pop() {
		if (topOfStack.link == null) {
			throw new StackUnderflowExcpetion("UNDERFLOW"); 
		}

		Node<T> returnNode = topOfStack;
		topOfStack = topOfStack.link;	
		return returnNode.contents;
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
}

interface BoundedStackInterface<T> extends StackInterface<T> {
	void push(T element) throws StackOverflowException;
	boolean isFull();	
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

@SuppressWarnings("serial")
class StackOverflowException extends RuntimeException {
	public StackOverflowException() {
		super();
	}

	public StackOverflowException(String message) {
		super(message);
	}
}
