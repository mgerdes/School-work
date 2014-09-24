import java.util.*;

public class QueueTest {
	public static void main(String[] args) {
		UnboundedQueue<Integer> q = new UnboundedQueue<Integer>();

		q.push(123);
		q.push(12323);
		q.push(3222);
		q.push(52);

		System.out.println(q.pop());
		System.out.println(q.pop());
		System.out.println(q.pop());
	}
}

class UnboundedQueue<T> implements QueueInterface<T> {
	Node<T> topOfStack = new Node<T>(null), bottomOfStack = topOfStack;
	
	UnboundedQueue() {
			
	}

	public void push(T element) {
		Node<T> newNode = new Node<T>(element);
		topOfStack.link = newNode;
		topOfStack = newNode;

		if (bottomOfStack.contents == null) {
			bottomOfStack = newNode;
		}
	}

	public T pop() {
		Node<T> returnNode = bottomOfStack;
		bottomOfStack = bottomOfStack.link; 
		return returnNode.contents;
	}

	public boolean isEmpty() {
		return false;
	}
}

class BoundedQueue<T> implements BoundedQueueInterface<T> {
	T[] q;
	int head = 0, tail = 0;
	static final int DEFAULT_MAX_SIZE = 10;

	BoundedQueue() {
		this(DEFAULT_MAX_SIZE);
	}
	
	@SuppressWarnings("unchecked")
	BoundedQueue(int size) {
		q = (T[]) new Object[size];	
	}

	public void push(T element) {
		q[head++] = element;	
	}

	public T pop() {
		return q[tail++];
	}

	public boolean isEmpty() {
		return head == tail;
	}

	public boolean isFull() {
		return true;
	}
}

interface BoundedQueueInterface<T> extends QueueInterface<T> {
	void push(T element) throws QueueOverflowException;
	boolean isFull();
}

interface QueueInterface<T> {
	void push(T element); 
	T pop() throws QueueUnderflowException; 
	boolean isEmpty(); 
}

class Node<T> {
	T contents;
	Node<T> link;

	Node(T contents) {
		this.contents = contents;
		link = null;
	}
}

@SuppressWarnings("serial")
class QueueUnderflowException extends RuntimeException {
	QueueUnderflowException() {
		super();
	}

	QueueUnderflowException(String message) {
		super(message);
	}
}

@SuppressWarnings("serial")
class QueueOverflowException extends RuntimeException {
	QueueOverflowException() {
		super();
	}

	QueueOverflowException(String message) {
		super(message);
	}
}
