package testdriver;

public class TestCase
{
	private String infixExpression;
	private int expectedResult;

	public TestCase()
	{

	}

	public TestCase(String infixExpression, int expectedResult)
	{
		this.infixExpression = infixExpression;
		this.expectedResult = expectedResult;
	}

	public String getExpression()
	{
		return this.infixExpression;
	}

	public int getExpectedResult()
	{
		return this.expectedResult;
	}
}
