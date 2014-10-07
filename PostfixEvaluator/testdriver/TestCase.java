package testdriver;

import expression.*;

public class TestCase
{
	private InfixExpression infix;
	private int expectedResult;

	public TestCase(InfixExpression infix, int expectedResult)
	{
		this.infix = infix;
		this.expectedResult = expectedResult;
	}

	public String getExpression()
	{
		return this.infix.toString();
	}

	public int getExpectedResult()
	{
		return this.expectedResult;
	}
}
