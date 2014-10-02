import stack.*;
import java.util.Scanner;

@SuppressWarnings("serial")
class UnknownOperatorException extends Exception
{
	public UnknownOperatorException()
	{
		super();
	}

	public UnknownOperatorException(String message)
	{
		super(message);
	}
}

class TestCase
{
	String infixExpression;
	int expectedResult;

	TestCase(String infixExpression, int expectedResult)
	{
		this.infixExpression = infixExpression;
		this.expectedResult = expectedResult;
	}
}

public class PostfixEvaluator
{
	public static char operators[] = {'>', '<', '-', '+', '%', '/', '*', '^', 'Q', 'C'};

	public static char unaryOperators[] = {'C', 'Q'};
	public static char binaryOperators[] = {'>', '<', '-', '+', '%', '/', '*', '^'};

	public static void main(String[] args)
	{
		runTestCases(10000);
		//	getInputFromConsole();
		String[] expression = createExpression(0, 10);
		System.out.println(expression[0] + " = " + expression[1]);
	}

	public static void getInputFromConsole()
	{
		Scanner input = new Scanner(System.in);

		String infixExpression;
		while (!(infixExpression = input.nextLine()).equals("exit"))
		{
			try
			{
				String postfixExpression = convertToPostfix(infixExpression);
				int result = evaluatePostfixExpression(postfixExpression);

				//	System.out.printf("\nThe infix expression: \n\t %s\nwas converted to " +
				//	                  "the postfix expression: \n\t %s\nwhich evaluated to " +
				//	                  "%d.\n\n", infixExpression, postfixExpression, result);

				System.out.println(result);
			}
			catch (UnknownOperatorException e)
			{
				System.out.println(e.getMessage());
			}
		}
	}

	public static void runTestCases(int numberOfTestCases)
	{
		try
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
				int result = evaluatePostfixExpression(convertToPostfix(testcase.infixExpression));
				if (result != testcase.expectedResult)
				{
					System.out.printf("%s evaluated to %d not the expected value of %d.\n",
					                  testcase.infixExpression, result, testcase.expectedResult);
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
		catch (UnknownOperatorException e)
		{
			e.printStackTrace();
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
			char operator = randomOperator();

			String[] expression1 = createExpression(depth + 1, maxDepth);
			int operand1 = Integer.valueOf(expression1[1]);

			if (isBinaryOperator(operator))
			{
				String[] expression2 = createExpression(depth + 1, maxDepth);
				int operand2 = Integer.valueOf(expression2[1]);

				while (operand2 == 0 && (operator == '/' || operator == '%'))
				{
					expression2 = createExpression(depth + 1, maxDepth);
					operand2 = Integer.valueOf(expression2[1]);
				}

				int result = evaluate(operand1, operand2, operator);

				return new String[] {"(" + expression1[0] + operator + expression2[0] + ")", "" + result};
			}
			else
			{
				while (operand1 < 0 && (operator == 'Q'))
				{
					expression1 = createExpression(depth + 1, maxDepth);
					operand1 = Integer.valueOf(expression1[1]);
				}

				int result = evaluate(operand1, 0, operator);

				return new String[] {operator + "(" + expression1[0] + ")", "" + result};
			}
		}
	}

	public static int evaluate(int operand1, int operand2, char operator)
	{
		int result = 0;

		switch(operator)
		{
		case('+'):
			result = operand1 + operand2;
			break;
		case('-'):
			result = operand1 - operand2;
			break;
		case('*'):
			result = operand1 * operand2;
			break;
		case('/'):
			result = operand1 / operand2;
			break;
		case('^'):
			result = (int)Math.pow(operand1, operand2);
			break;
		case('<'):
			result = operand1 << operand2;
			break;
		case('>'):
			result = operand1 >> operand2;
			break;
		case('%'):
			result = operand1 % operand2;
			break;
		case('C'):
			result = (int)Math.pow(operand1, 1D/3);
			break;
		case('Q'):
			result = (int)Math.pow(operand1, 1D/2);
			break;
		}

		return result;
	}

	public static char randomOperator()
	{
		return operators[(int)(Math.random() * operators.length)];
	}

	public static int evaluatePostfixExpression(String postfixExpression)
	{
		Stack<Integer> stack = new Stack<Integer>();

		String tokens[] = postfixExpression.split(" ");

		for (String token : tokens)
		{
			char firstCharacter = token.charAt(0);

			if (Character.isDigit(firstCharacter))
			{
				stack.push(Integer.valueOf(token));
			}
			else
			{
				char operator = firstCharacter;
				doOperation(operator, stack);
			}
		}

		return stack.pop();
	}

	public static int doOperation(char operator, Stack<Integer> stack)
	{
		int operand1 = 0, operand2 = 0, result = 0;

		operand1 = Integer.valueOf(stack.pop());
		if (isBinaryOperator(operator))
		{
			operand2 = Integer.valueOf(stack.pop());
		}

		switch(operator)
		{
		case 'Q':
			result = (int)(Math.pow(operand1, 1D/2));
			break;
		case 'C':
			result = (int)(Math.pow(operand1, 1D/3));
			break;
		case '+':
			result = operand1 + operand2;
			break;
		case '-':
			result = operand2 - operand1;
			break;
		case '*':
			result = operand1 * operand2;
			break;
		case '/':
			result = operand2 / operand1;
			break;
		case '%':
			result = operand2 % operand1;
			break;
		case '^':
			result = (int)(Math.pow(operand2, operand1));
			break;
		case '<':
			result = operand2 << operand1;
			break;
		case '>':
			result = operand2 >> operand1;
			break;
		}

		stack.push(result);
		return result;
	}

	public static String convertToPostfix(String infixString) throws UnknownOperatorException
	{
		Stack<Character> stack = new Stack<Character>();

		char infixCharArray[] = infixString.replaceAll(" ", "").toCharArray();
		StringBuilder postfixExpression = new StringBuilder();

		for (int i = 0; i < infixCharArray.length; i++)
		{
			char curChar = infixCharArray[i];

			if (isOperator(curChar))
			{
				processOperator(curChar, postfixExpression, stack);
			}
			else if (isLeftParan(curChar))
			{
				stack.push(curChar);
			}
			else if (isRightParan(curChar))
			{
				processRightParen(postfixExpression, stack);
			}
			else if (Character.isDigit(curChar))
			{
				while (Character.isDigit(curChar))
				{
					postfixExpression.append("" + curChar);
					if (i + 1 < infixCharArray.length)
					{
						curChar = infixCharArray[++i];
					}
					else
					{
						curChar = 'X';
						i += 2;
					}
				}
				postfixExpression.append(" ");
				i--;
			}
			else
			{
				throw new UnknownOperatorException("The character " + curChar + " is not known.");
			}
		}

		while (!stack.isEmpty())
		{
			postfixExpression.append(stack.pop() + " ");
		}

		return new String(postfixExpression);
	}

	public static void processOperator(char token, StringBuilder postfixExpression, Stack<Character> stack)
	{
		while (!stack.isEmpty() && !isLeftParan(stack.top())
		        && precendence(token) <= precendence(stack.top()))
		{
			postfixExpression.append(stack.pop() + " ");
		}

		stack.push(token);
	}

	public static void processRightParen(StringBuilder postfixExpression, Stack<Character> stack)
	{
		while(!isLeftParan(stack.top()))
		{
			postfixExpression.append(stack.pop() + " ");
		}

		stack.pop();
	}

	public static int precendence(char character)
	{
		for (int i = 0; i < operators.length; i++)
		{
			if (character == operators[i]) return i;
		}

		return -1;
	}

	public static boolean isUnaryOperator(char character)
	{
		for (char operator : unaryOperators)
		{
			if (operator == character) return true;
		}

		return false;
	}

	public static boolean isBinaryOperator(char character)
	{
		for (char operator : binaryOperators)
		{
			if (operator == character) return true;
		}

		return false;
	}

	public static boolean isOperator(char character)
	{
		for (char operator : operators)
		{
			if (operator == character) return true;
		}

		return false;
	}

	public static boolean isLeftParan(char character)
	{
		return (character == '(');
	}

	public static boolean isRightParan(char character)
	{
		return (character == ')');
	}
}
