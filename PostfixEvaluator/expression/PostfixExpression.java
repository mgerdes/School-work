package expression;

import stack.*;

public class PostfixExpression
{

	private String expression;

	public PostfixExpression(String expression)
	{
		this.expression = expression;
	}

	public PostfixExpression(StringBuilder expression)
	{
		this.expression = new String(expression);
	}

	public int evaluate() throws ArithmeticException
	{
		Stack<Integer> stack = new Stack<Integer>();

		String tokens[] = expression.split(" ");

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
				int operand1, operand2;

				if (Operator.isBinaryOperator(firstCharacter))
				{
					operand1 = stack.pop();
					operand2 = stack.pop();
				}
				else
				{
					operand1 = stack.pop();
					operand2 = 0;
				}

				int result = Operator.evaluate(operand2, operand1, operator);

				stack.push(result);
			}
		}

		return stack.pop();
	}

	@Override
	public String toString()
	{
		return expression;
	}

}
