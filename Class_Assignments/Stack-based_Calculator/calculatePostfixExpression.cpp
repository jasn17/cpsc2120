/* Jason Lin 
 * 02/11/2024
 * Stack-based Postfix Expression Calculator
 * CPSC 2120 - 003
 */
#include <string>
#include <stack>
#include <cstdlib>

using namespace std;

//Calculates a postfix expression with integer operands using a stack
//The expression is represented using an array of strings
//Each string is either an operand or operator symbol
//Operator symbols:
//"+" addition
//"-" subtraction
//"*" multiplication
//"/" divison
//"%" remainder
//Example expression: "8", "5", "-" evaluates to a result of 3:
//1: push 8, 2: push 5,
//3: "-"-> pop top two values, earlier value is the left-side operand: 8 - 5
//The result of the operation (8-5) is 3, push 3 onto stack
//After evaluation of the expression, the final result should be
//the only value on the stack, return 0 if the stack is
//non-empty after popping the result
//Return 0 if expression is zero-length or if there are insufficient operands
//for an operation
//The STL Stack class can be used
//To easily convert a numeric string to an int you may use the stoi() function
//which takes a string as a parameter and returns a string
int calculatePostfixExpression(string expression[], int length)
{
	// Checking if expression is zero length
	if (length == 0) {
		return 0;
	}

	// Checking for insufficient operands for an operation
	int operators = 0;
	int operands = 0;
   for (int i = 0; i < length; i++) {
	if (expression[i] == "+" || expression[i] == "-" || expression[i] == "*" || expression[i] == "/" || expression[i] == "%") {
		operators++;
	}
	else {
		operands++;
	}
   } 
   // Let number of operands be n, if the number of operators are not n - 1, then there is insufficient number of operators
   if (operands - 1 != operators) {
	return 0;
   }
 
   // Create stack data structure
   stack<int> stack;
   // Iterate through array
   	for (int i = 0; i < length; i++) {
		// If expression[i] is a operator, perform a operation by popping the previous two values from the stack
		if (expression[i] == "+" || expression[i] == "-" || expression[i] == "*" || expression[i] == "/" || expression[i] == "%") {
			int x = stack.top();
			stack.pop();
			int y = stack.top();
			stack.pop();
			
			// Perform the relevent calculation
			string temp = expression[i];
			if (temp == "+") {
				y += x;
				stack.push(y);
			}
			else if (temp ==  "-") {
				y -= x;
				stack.push(y);
			}
			else if (temp == "*") {
				y *= x;
				stack.push(y);
			}
			else if(temp == "/") {
				y /= x;
				stack.push(y);
			}
			else {
				y %= x;
				stack.push(y);
			}
		}
		// If expression[i] is not a operator, then convert it into a integer and push it to the stack
		else {
			stack.push(atoi(expression[i].c_str()));
		}
	}
	// Stores the final return value
	int z = stack.top(); stack.pop();
	
	// Checking for non-empty stack after popping the result
	if (!stack.empty()) {
		return 0;
	}
	else {
		return z;
	}
	
}
