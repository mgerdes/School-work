import stack.*;
import testdriver.*;
import expression.*;

import java.util.Scanner;

public class Main
{

	public static void main(String[] args)
	{
		//runTestCases(10000);
		getInputFromConsole();
		//String[] expression = createExpression(0, 10);
		//System.out.println(expression[0] + " = " + expression[1]);
	}

	public static void getInputFromConsole()
	{
		Scanner input = new Scanner(System.in);

		while (true)
		{
			String inputString = input.nextLine();

			if (inputString.equals("exit")) break;

			InfixExpression infix = new InfixExpression(inputString);
			PostfixExpression postfix = infix.convertToPostfix();

			System.out.println(postfix);

			try
			{
				System.out.println(postfix.evaluate());
			}
			catch (ArithmeticException e)
			{
				System.out.println(e.getMessage());
			}
		}
	}

}
