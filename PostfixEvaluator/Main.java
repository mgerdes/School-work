import stack.*;
import testdriver.*;
import expression.*;

import java.util.Scanner;

public class Main
{

	public static void main(String[] args)
	{
		try
		{
			TestDriver testing = new TestDriver(10000);
			testing.runTestCases();

			//runTestCases(10000);
			//getInputFromConsole();
			//String[] expression = createExpression(0, 10);
		}
		catch (ArithmeticException e)
		{
			System.out.println(e.getMessage());
		}
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
			System.out.println(postfix.evaluate());
		}
	}

}
