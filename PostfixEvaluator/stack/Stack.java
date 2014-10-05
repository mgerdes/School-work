package stack;

public class Stack<T>
{
	private Node<T> topOfStack;

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
			throw new StackUnderflowException("Underflow");
		}

		Node<T> returnNode = topOfStack;
		topOfStack = topOfStack.getLink();
		return returnNode.getContents();
	}

	public T top()
	{
		if (this.isEmpty())
		{
			throw new StackUnderflowException("Underflow");
		}

		return topOfStack.getContents();
	}

	public boolean isEmpty()
	{
		return topOfStack.getLink() == null;
	}
}
