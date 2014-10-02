package stack;

public class Stack<T> implements StackInterface<T>
{
	Node<T> topOfStack;

	public Stack()
	{
		topOfStack = new Node<T>(null);
	}

	public void push(T element)
	{
		Node<T> newNode = new Node<T>(element);
		newNode.setLink(topOfStack);
		topOfStack = newNode;
	}

	public T pop()
	{
		if (this.isEmpty())
		{
			throw new StackUnderflowExcpetion("UNDERFLOW");
		}

		Node<T> returnNode = topOfStack;
		topOfStack = topOfStack.getLink();
		return returnNode.getContents();
	}

	public T top()
	{
		if (this.isEmpty())
		{
			throw new StackUnderflowExcpetion("UNDERFLOW");
		}

		return topOfStack.getContents();
	}

	public boolean isEmpty()
	{
		return topOfStack.getLink() == null;
	}
}

class Node<T>
{
	private T contents;
	private Node<T> link;

	Node(T contents)
	{
		this.contents = contents;
		link = null;
	}

	public T getContents()
	{
		return contents;
	}

	public void setContents(T contents)
	{
		this.contents = contents;
	}

	public Node<T> getLink()
	{
		return this.link;
	}

	public void setLink(Node<T> link)
	{
		this.link = link;
	}

	@Override
	public String toString()
	{
		return contents.toString();
	}
}

interface StackInterface<T>
{
	void push(T element);

	T pop() throws StackUnderflowExcpetion;

	boolean isEmpty();
}

@SuppressWarnings("serial")
class StackUnderflowExcpetion extends RuntimeException
{
	public StackUnderflowExcpetion()
	{
		super();
	}

	public StackUnderflowExcpetion(String message)
	{
		super(message);
	}
}
