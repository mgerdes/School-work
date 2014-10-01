import stack.Stack;
import java.util.Scanner;

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
	public static char operators[] = {'>', '<', '-', '+', '%', '/', '*', 'C', 'Q', '^'};

	public static char unaryOperators[] = {'C', 'Q'};
	public static char binaryOperators[] = {'>', '<', '-', '+', '%', '/', '*', '^'};

	public static void main(String[] args)
	{
		runTestCases();
	}

	public static void getInputFromConsole()
	{
		Scanner input = new Scanner(System.in);

		String infixExpression;
		while (!(infixExpression = input.nextLine()).equals("exit"))
		{
			String postfixExpression = convertToPostfix(infixExpression);
			int result = evaluatePostfixExpression(postfixExpression);

			//	System.out.printf("\nThe infix expression: \n\t %s\nwas converted to " +
			//	                  "the postfix expression: \n\t %s\nwhich evaluated to " +
			//	                  "%d.\n\n", infixExpression, postfixExpression, result);

			System.out.println(result);
		}
	}

	public static void runTestCases()
	{
		boolean testCaseFailed = false;
		generateTestCases();

		TestCase testcases[] =
		{
			new TestCase("( 2 + 5 ) * ( 4 % 2 )", 0),
			new TestCase("(2+3)*(4%2)", 0),
			new TestCase("Q((4*4))", 4),
			new TestCase("C(27)", 3),
			new TestCase("(0-1)*(2<10)", -2048),
			new TestCase("(0 - 1) * (2 < 10)", -2048),
			new TestCase("2<10", 2048),
			new TestCase("15>1", 7),
			new TestCase("7%2", 1),
			new TestCase("15 % 5", 0),
			new TestCase("17 % 5", 2),
			new TestCase("3 < 2", 12),
			new TestCase("3 ^ 4", 81),
			new TestCase("Q(11)", 3),
			new TestCase("Q(9)", 3),
			new TestCase("Q(9) * Q(11)", 9),
		};

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

	public static void generateTestCases()
	{

		int numberOfOperations = (int)(Math.random() * 20);
		numberOfOperations = 1;

		for (int i = 0; i < numberOfOperations; i++)
		{
			String expression;
			char operator = operators[(int)(Math.random() * operators.length)];
			int operand1 = 0, operand2 = 0;

			operand1 = (int)(Math.random() * 100);
			if (isBinaryOperator(operator))
			{
				operand2 = (int)(Math.random() * 100);
				expression = operand1 + " " + operator + " " + operand2;
			}
			else
			{
				expression = operator + "(" + operand1 + ")";
			}

			int result = 0;

			switch (operator)
			{
			case '<':
				result = operand1 << operand2;
				break;
			case '>':
				result = operand1 >> operand2;
				break;
			case '*':
				result = operand1 * operand2;
				break;
			case '/':
				result = operand1 / operand2;
				break;
			case '%':
				result = operand1 % operand2;
				break;
			case '+':
				result = operand1 + operand2;
				break;
			case '-':
				result = operand1 - operand2;
				break;
			case 'C':
				result = (int)Math.pow(operand1, 1D/3);
				break;
			case 'Q':
				result = (int)Math.pow(operand1, 1D/2);
				break;
			case '^':
				result = (int)Math.pow(operand1, operand2);
				break;
			}

			System.out.println(expression + " = " + result);
		}

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

	public static String convertToPostfix(String infixString)
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
				// throws unknown input exception.
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
