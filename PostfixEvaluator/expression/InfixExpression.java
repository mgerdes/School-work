package expression;

import stack.*;

public class InfixExpression
{

	private String expression;

	public InfixExpression(String expression)
	{
		this.expression = expression;
	}

	public PostfixExpression convertToPostfix()
	{
		Stack<Character> stack = new Stack<Character>();

		char infixCharArray[] = expression.replaceAll(" ", "").toCharArray();
		StringBuilder postfixExpression = new StringBuilder();

		for (int i = 0; i < infixCharArray.length; i++)
		{
			char curChar = infixCharArray[i];

			if (Operator.isOperator(curChar))
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
		}

		while (!stack.isEmpty())
		{
			postfixExpression.append(stack.pop() + " ");
		}

		return new PostfixExpression(postfixExpression);
	}


	public static void processOperator(char token, StringBuilder postfixExpression, Stack<Character> stack)
	{
		while (!stack.isEmpty() && !isLeftParan(stack.top())
		        && Operator.precendence(token) <= Operator.precendence(stack.top()))
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

	public static boolean isLeftParan(char character)
	{
		return (character == '(');
	}

	public static boolean isRightParan(char character)
	{
		return (character == ')');
	}

	public int evaluate() throws ArithmeticException
	{
		PostfixExpression postfix = this.convertToPostfix();
		return postfix.evaluate();
	}

	@Override
	public String toString()
	{
		return expression;
	}

}
