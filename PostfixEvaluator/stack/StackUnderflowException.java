package stack;

@SuppressWarnings("serial")
public class StackUnderflowException extends RuntimeException
{
	public StackUnderflowException()
	{
		super();
	}

	public StackUnderflowException(String message)
	{
		super(message);
	}
}
