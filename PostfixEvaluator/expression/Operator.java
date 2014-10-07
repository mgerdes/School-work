package expression;

import java.math.*;

public class Operator
{
	private static OperatorInterface operators[] =
	{
		new OperatorInterface()
		{
			public char getCharacter()
			{
				return '+';
			}

			public int getPrecedence()
			{
				return 1;
			}

			public long evaluate(int operand1, int operand2)
			{
				long result = (long)operand1 + (long)operand2;
				return result;
			}

			public boolean isBinaryOperator()
			{
				return true;
			}
		},

		new OperatorInterface()
		{
			public char getCharacter()
			{
				return '-';
			}

			public int getPrecedence()
			{
				return 1;
			}

			public long evaluate(int operand1, int operand2)
			{
				long result = (long)operand1 - (long)operand2;
				return result;
			}

			public boolean isBinaryOperator()
			{
				return true;
			}
		},

		new OperatorInterface()
		{

			public char getCharacter()
			{
				return '/';
			}

			public int getPrecedence()
			{
				return 2;
			}

			public long evaluate(int operand1, int operand2)
			{
				long result = (long)operand1 / (long)operand2;
				return result;
			}

			public boolean isBinaryOperator()
			{
				return true;
			}

		},

		new OperatorInterface()
		{
			public char getCharacter()
			{
				return '*';
			}

			public int getPrecedence()
			{
				return 2;
			}

			public long evaluate(int operand1, int operand2)
			{
				long result = (long)operand1 * (long)operand2;
				return result;
			}

			public boolean isBinaryOperator()
			{
				return true;
			}
		},

		new OperatorInterface()
		{
			public char getCharacter()
			{
				return '%';
			}

			public int getPrecedence()
			{
				return 2;
			}

			public long evaluate(int operand1, int operand2)
			{
				long result = (long)operand1 % (long)operand2;
				return result;
			}

			public boolean isBinaryOperator()
			{
				return true;
			}
		},

		new OperatorInterface()
		{
			public char getCharacter()
			{
				return '>';
			}

			public int getPrecedence()
			{
				return 2;
			}

			public long evaluate(int operand1, int operand2)
			{
				long result = (long)operand1 >> (long)operand2;
				return result;
			}

			public boolean isBinaryOperator()
			{
				return true;
			}
		},

		new OperatorInterface()
		{
			public char getCharacter()
			{
				return '<';
			}

			public int getPrecedence()
			{
				return 2;
			}

			public long evaluate(int operand1, int operand2)
			{
				long result = (long)operand1 << (long)operand2;
				return result;
			}

			public boolean isBinaryOperator()
			{
				return true;
			}
		},

		new OperatorInterface()
		{
			public char getCharacter()
			{
				return '^';
			}

			public int getPrecedence()
			{
				return 2;
			}

			public long evaluate(int operand1, int operand2)
			{
				long result = (long)Math.pow((long)operand1, (long)operand2);
				return result;
			}

			public boolean isBinaryOperator()
			{
				return true;
			}

		},

		new OperatorInterface()
		{
			public char getCharacter()
			{
				return 'Q';
			}

			public int getPrecedence()
			{
				return 3;
			}

			public long evaluate(int operand1, int operand2)
			{
				long result = (long)Math.pow((long)operand1, 1D/2);
				return result;
			}

			public boolean isBinaryOperator()
			{
				return false;
			}
		},

		new OperatorInterface()
		{

			public char getCharacter()
			{
				return 'C';
			}

			public int getPrecedence()
			{
				return 3;
			}

			public long evaluate(int operand1, int operand2)
			{
				long result = (long)Math.pow((long)operand1, 1D/3);
				return result;
			}

			public boolean isBinaryOperator()
			{
				return false;
			}
		},
	};

	public static boolean isIntegerOverflow(long number)
	{
		if (number > Integer.MAX_VALUE)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	public static boolean isIntegerUnderflow(long number)
	{
		if (number < Integer.MIN_VALUE)
		{
			return true;
		}
		else
		{
			return false;
		}

	}

	public static int precendence(char operator)
	{
		for (OperatorInterface curOperator : operators)
		{
			if (curOperator.getCharacter() == operator)
			{
				return curOperator.getPrecedence();
			}
		}

		return -1;
	}

	public static boolean isOperator(char character)
	{
		for (OperatorInterface operator : operators)
		{
			if (operator.getCharacter() == character) return true;
		}
		return false;
	}

	public static boolean isUnaryOperator(char operator)
	{
		return !isBinaryOperator(operator);
	}

	public static boolean isBinaryOperator(char operator)
	{
		for (OperatorInterface curOperator: operators)
		{
			if (curOperator.getCharacter() == operator)
			{
				if (curOperator.isBinaryOperator()) return true;
				else return false;
			}
		}
		return false;
	}

	public static char randomOperator()
	{
		return operators[(int)(Math.random() * operators.length)].getCharacter();
	}

	public static int evaluate(int operand1, int operand2, char operator) throws ArithmeticException
	{
		for (OperatorInterface curOperator : operators)
		{
			if (curOperator.getCharacter() == operator)
			{
				long result = curOperator.evaluate(operand1, operand2);

				if (isIntegerOverflow(result))
					throw new ArithmeticException("Overflow");
				if (isIntegerUnderflow(result))
					throw new ArithmeticException("Underflow");

				return ((int)result);
			}
		}

		return 0;
	}
}
