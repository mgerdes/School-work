package expression;

import java.math.*;

public class Operator
{

	private static final char OPERATORS[] = {'>', '<', '-', '+', '%', '/', '*', '^', 'Q', 'C'};

	private char operator;

	public Operator(char operator)
	{
		this.operator = operator;
	}

	public static int precendence(char operator)
	{
		for (int i = 0; i < OPERATORS.length; i++)
		{
			if (operator == OPERATORS[i]) return i;
		}

		return -1;
	}

	public static boolean isOperator(char character)
	{
		for (char operator : OPERATORS)
		{
			if (character == operator) return true;
		}
		return false;
	}

	public static boolean isUnaryOperator(char operator)
	{
		if (operator == 'C' || operator == 'Q') return true;
		else return false;
	}

	public static boolean isBinaryOperator(char operator)
	{
		return !isUnaryOperator(operator);
	}

	public static char randomOperator()
	{
		return OPERATORS[(int)(Math.random() * OPERATORS.length)];
	}

	public static int evaluate(int operand1, int operand2, char operator) throws ArithmeticException
	{
		BigInteger resultBig;
		BigInteger operand1Big = new BigInteger("" + operand1);
		BigInteger operand2Big = new BigInteger("" + operand2); 

		switch(operator)
		{
			case('+'):
				resultBig = operand1Big.add(operand2Big);
				break;
			case('-'):
				resultBig = operand1Big.subtract(operand2Big);
				break;
			case('*'):
				resultBig = operand1Big.multiply(operand2Big);
				break;
			case('/'):
				resultBig = operand1Big.divide(operand2Big);
				break;
			case('^'):
				resultBig = operand1Big.pow(operand2);
				break;
			case('<'):
				resultBig = operand1Big.shiftLeft(operand2);
				break;
			case('>'):
				resultBig = operand1Big.shiftRight(operand2);
				break;
			case('%'):
				resultBig = operand1Big.mod(operand2Big);
				break;
			case('C'):
				resultBig = new BigInteger("" + (int)Math.pow(operand1, 1D/3));
				break;
			case('Q'):
				resultBig = new BigInteger("" + (int)Math.pow(operand1, 1D/2));
				break;
			default:
				resultBig = new BigInteger("" + 0);
				break;
		}

		if (resultBig.compareTo(new BigInteger("" + Integer.MAX_VALUE)) == 1) {
			throw new ArithmeticException("There was overflow in the previous calculation.");
		}
		if (resultBig.compareTo(new BigInteger("" + Integer.MIN_VALUE)) == -1) {
			throw new ArithmeticException("There was underflow in the previous calculation.");
		}

		return resultBig.intValue();
	}

}
