package testdriver;

import expression.*;

public class TestDriver
{

	public static void runTestCases(int numberOfTestCases)
	{
		boolean testCaseFailed = false;
		TestCase testcases[] = new TestCase[numberOfTestCases];

		for (int i = 0; i < numberOfTestCases; i++)
		{
			String[] expression = createExpression(0, 5);
			testcases[i] = new TestCase(expression[0], Integer.valueOf(expression[1]));
		}

		for (TestCase testcase : testcases)
		{
			InfixExpression infix = new InfixExpression(testcase.getExpression());
			PostfixExpression postfix = infix.convertToPostfix();

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

	public static String[] createExpression(int depth, int maxDepth)
	{
		if (depth >= maxDepth)
		{
			int randomNumber = (int)(Math.random() * 10) + 1;
			return new String[] {("" + randomNumber), "" + randomNumber};
		}
		else
		{
			char operator = Operator.randomOperator();

			String[] expression1 = createExpression(depth + 1, maxDepth);
			int operand1 = Integer.valueOf(expression1[1]);

			if (Operator.isBinaryOperator(operator))
			{
				String[] expression2 = createExpression(depth + 1, maxDepth);
				int operand2 = Integer.valueOf(expression2[1]);

				while (operand2 == 0 && (operator == '/' || operator == '%'))
				{
					expression2 = createExpression(depth + 1, maxDepth);
					operand2 = Integer.valueOf(expression2[1]);
				}

				int result = Operator.evaluate(operand1, operand2, operator);

				return new String[] {"(" + expression1[0] + operator + expression2[0] + ")", "" + result};
			}
			else
			{
				while (operand1 < 0 && (operator == 'Q'))
				{
					expression1 = createExpression(depth + 1, maxDepth);
					operand1 = Integer.valueOf(expression1[1]);
				}

				int result = Operator.evaluate(operand1, 0, operator);

				return new String[] {operator + "(" + expression1[0] + ")", "" + result};
			}
		}
	}
}
