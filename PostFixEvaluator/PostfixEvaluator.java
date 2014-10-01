import stack.Stack;
import java.util.Scanner;

public class PostfixEvaluator {
	public static char operators[] = {'>', '<', '-', '+', '%', '/', '*', 'C', 'Q', '^'};

	public static char unaryOperators[] = {'C', 'Q'};
	public static char binaryOperators[] = {'>', '<', '-', '+', '%', '/', '*', '^'};

	public static void main(String[] args) {

		Scanner input = new Scanner(System.in);

		String infixExpression;
		while (!(infixExpression = input.nextLine()).equals("exit")) {
			String postfixExpression = convertToPostfix(infixExpression);
			int result = evaluatePostfixExpression(postfixExpression);

		//	System.out.printf("\nThe infix expression: \n\t %s\nwas converted to " +
		//	                  "the postfix expression: \n\t %s\nwhich evaluated to " +
		//	                  "%d.\n\n", infixExpression, postfixExpression, result);

			System.out.println(result);
		}

	}

	public static int evaluatePostfixExpression(String postfixExpression) {
		Stack<Integer> stack = new Stack<Integer>();

		String tokens[] = postfixExpression.split(" ");

		for (String token : tokens) {
			char firstCharacter = token.charAt(0);
			
			if (Character.isDigit(firstCharacter)) {
				stack.push(Integer.valueOf(token));
			} else {
				char operator = firstCharacter;
				doOperation(operator, stack);
			}
		}

		return stack.pop();
	}

	public static void doOperation(char operator, Stack<Integer> stack) {
		int operand1 = 0, operand2 = 0;

		operand1 = Integer.valueOf(stack.pop());
		if (isBinaryOperator(operator)) {
			operand2 = Integer.valueOf(stack.pop());
		}

		switch(operator) {
			case 'Q':
				stack.push((int)(Math.pow(operand1, 1D/2)));
				break;
			case 'C':
				stack.push((int)(Math.pow(operand1, 1D/3)));
				break;
			case '+':
				stack.push((operand1 + operand2));
				break;
			case '-':
				stack.push((operand2 - operand1));
				break;
			case '*':
				stack.push((operand1 * operand2));
				break;
			case '/':
				stack.push((operand2 / operand1));
				break;
			case '%':
				stack.push((operand2 % operand1));
				break;
			case '^':
				stack.push((int)(Math.pow(operand2, operand1)));
				break;
			case '<':
				stack.push((int)(operand2 / Math.pow(2, operand1)));
				break;
			case '>':
				stack.push((int)(operand2 * Math.pow(2, operand1)));
				break;
		}
	}

	public static String convertToPostfix(String infixString) {
		Stack<Character> stack = new Stack<Character>();

		char infixCharArray[] = infixString.replaceAll(" ", "").toCharArray();
		StringBuilder postfixExpression = new StringBuilder();

		for (int i = 0; i < infixCharArray.length; i++) {

			char curChar = infixCharArray[i];

			if (isOperator(curChar)) {
				processOperator(curChar, postfixExpression, stack);
			} else if (isLeftParan(curChar)) {
				stack.push(curChar);
			} else if (isRightParan(curChar)) {
				processRightParen(postfixExpression, stack);
			} else if (Character.isDigit(curChar)) {
				while (Character.isDigit(curChar)) {
					postfixExpression.append("" + curChar);
					if (i + 1 < infixCharArray.length) {
						curChar = infixCharArray[++i];
					} else {
						curChar = 'X';
						i += 2;
					}
				}
				postfixExpression.append(" ");
				i--;
			} else {
				// throws unknown input exception.
			}
		}

		while (!stack.isEmpty()) {
			postfixExpression.append(stack.pop() + " ");
		}

		return new String(postfixExpression);
	}

	public static void processOperator(char token, StringBuilder postfixExpression, Stack<Character> stack) {
		while (!stack.isEmpty() && !isLeftParan(stack.top())
		        && precendence(token) <= precendence(stack.top())) {
			postfixExpression.append(stack.pop() + " ");
		}

		stack.push(token);
	}

	public static void processRightParen(StringBuilder postfixExpression, Stack<Character> stack) {
		while(!isLeftParan(stack.top())) {
			postfixExpression.append(stack.pop() + " ");
		}

		stack.pop();
	}

	public static int precendence(char character) {
		for (int i = 0; i < operators.length; i++) {
			if (character == operators[i]) return i;
		}

		return -1;
	}

	public static boolean isUnaryOperator(char character) {
		for (char operator : unaryOperators) {
			if (operator == character) return true;
		}

		return false;
	}

	public static boolean isBinaryOperator(char character) {
		for (char operator : binaryOperators) {
			if (operator == character) return true;
		}

		return false;
	}

	public static boolean isOperator(char character) {
		for (char operator : operators) {
			if (operator == character) return true;
		}

		return false;
	}

	public static boolean isLeftParan(char character) {
		return (character == '(');
	}

	public static boolean isRightParan(char character) {
		return (character == ')');
	}
}
