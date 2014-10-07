package expression;

public interface OperatorInterface
{

	public int getPrecedence();	
	public long evaluate(int operand1, int operand2) throws ArithmeticException;
	public char getCharacter(); 
	public boolean isBinaryOperator();

}
