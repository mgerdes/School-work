package stack;

public class Node<T>
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
