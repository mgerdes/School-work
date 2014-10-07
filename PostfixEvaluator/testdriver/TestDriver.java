package testdriver;
import expression.*;

import java.math.BigInteger;

public class TestDriver
{

	private static final int MAX_DEPTH = 3, MAX_NUMBER = 10;

	private TestCase testCases[];
	private int numOfTestCases;

	public TestDriver(int numOfTestCases)
	{
		this.numOfTestCases = numOfTestCases;
		testCases = new TestCase[numOfTestCases];
		this.createExpressions();
	}

	public void runTestCases()
	{
		boolean testCaseFailed = false;

		for (TestCase testcase : testCases)
		{
			InfixExpression infix = new InfixExpression(testcase.getExpression());
			PostfixExpression postfix = infix.convertToPostfix();
			//System.out.println(testcase.getExpression());
			//System.out.println(postfix);
			//System.out.println(testcase.getExpectedResult());

			int result = postfix.evaluate();

			if (result != testcase.getExpectedResult())
			{
				System.out.printf("%s evaluated to %d not the expected value of %d.\n",
				                  testcase.getExpression(), result, testcase.getExpectedResult());
				testCaseFailed = true;
			}
		}

		if (!testCaseFailed)
		{
			System.out.println("All test cases passed :).");
		}
		else
		{
			System.out.println("Some test cases failed :(.");
		}
	}

	private void createExpressions()
	{
		for (int i = 0; i < numOfTestCases; i++)
		{
			try
			{
				String[] expression = createExpression();

				InfixExpression infix = new InfixExpression(expression[0]);
				int result = Integer.valueOf(expression[1]);

				testCases[i] = new TestCase(infix, result);
			}
			catch (ArithmeticException e)
			{
				i--;
			}
		}
	}

	public static String[] createExpression() throws ArithmeticException
	{
		return createExpression(0);
	}

	private static String[] createExpression(int depth) throws ArithmeticException
	{
		if (depth >= MAX_DEPTH)
		{
			int randomNumber = (int)(Math.random() * MAX_NUMBER) + 1;
			return new String[] {("" + randomNumber), "" + randomNumber};
		}
		else
		{
			char operator = Operator.randomOperator();

			String[] expression1 = createExpression(depth + 1);
			int operand1 = Integer.valueOf(expression1[1]);

			if (Operator.isBinaryOperator(operator))
			{
				String[] expression2 = createExpression(depth + 1);
				int operand2 = Integer.valueOf(expression2[1]);

				while (operand2 == 0 && (operator == '/' || operator == '%'))
				{
					expression2 = createExpression(depth + 1);
					operand2 = Integer.valueOf(expression2[1]);
				}

				int result = evaluate(operand1, operand2, operator);

				return new String[] {"(" + expression1[0] + operator + expression2[0] + ")", "" + result};
			}
			else
			{
				while (operand1 < 0 && (operator == 'Q'))
				{
					expression1 = createExpression(depth + 1);
					operand1 = Integer.valueOf(expression1[1]);
				}

				int result = evaluate(operand1, 0, operator);

				return new String[] {operator + "(" + expression1[0] + ")", "" + result};
			}
		}
	}

	private static int evaluate(int operand1, int operand2, char operator) throws ArithmeticException
	{
		long result;

		switch(operator)
		{
		case('+'):
			result = (long)operand1 + (long)operand2;
			break;
		case('-'):
			result = (long)operand1 - (long)operand2;
			break;
		case('*'):
			result = (long)operand1 * (long)operand2;
			break;
		case('/'):
			result = (long)operand1 / (long)operand2;
			break;
		case('^'):
			result = (long)Math.pow((long)operand1, (long)operand2);
			break;
		case('<'):
			result = (long)operand1 << (long)operand2;
			break;
		case('>'):
			result = (long)operand1 >> (long)operand2;
			break;
		case('%'):
			result = (long)operand1 % (long)operand2;
			break;
		case('C'):
			result = (long)Math.pow((long)operand1, 1D/3);
			break;
		case('Q'):
			result = (long)Math.pow((long)operand1, 1D/2);
			break;
		default:
			result = 0;
			break;
		}


		if (result > Integer.MAX_VALUE)
		{
			throw new ArithmeticException("overflow");
		}
		if (result < Integer.MIN_VALUE)
		{
			throw new ArithmeticException("underflow");
		}

		return (int)result;
	}
}
