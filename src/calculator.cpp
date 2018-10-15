/*
  Infix to postfix conversion in C++
  Input Postfix expression must be in a desired format.
  Operands and operator, both must be single character.
*/
#include<iostream>
#include<stack>
#include<string>

// Function to convert Infix expression to postfix
std::string InfixToPostfix(std::string expression);

// Function to verify whether an operator has higher precedence over other
static int HasHigherPrecedence(char operator1, char operator2);

// Function to verify whether a character is operator symbol or not.
static bool IsOperatorBinary(char C);

static bool IsOperatorUnary(char C);

// Function to verify whether a character is alphanumeric chanaracter
//(letter or numeric digit) or not.
static bool IsOperand(char C);

// Function to check whether a char is an opening parenthesis i.e '(' or '{' or '['
static bool IsOpeningParentheses(char C);

// Function to check whether a char is an closing parenthesis i.e ')' or '}' or ']'
static bool IsClosingParentheses(char C);

#if 0
int main()
{
	std::string expression;
	std::cout<<"Enter Infix Expression \n";
	getline(std::cin,expression);
	std::string postfix = InfixToPostfix(expression);
	std::cout<<"Output = "<<postfix<<"\n";
}
#endif

// Function to evaluate Postfix expression and return output
std::string InfixToPostfix(std::string expression)
{
	// Declaring a Stack from Standard template library in C++.
	std::stack<char> S;
	std::string postfix = ""; // Initialize postfix as empty std::string.
	int unaryToBinary = 0;

    S.push('('); // Push a left parenthesis ‘(‘ onto the stack.

	for (int i = 0;i< expression.length(); i++) {

		// Scanning each character from left.
		// If character is a delimiter, move on.
		if (expression[i] == ' ' || expression[i] == ',')
			continue;

		// Else if character is an operand then just append it in res std::string
		else if (IsOperand(expression[i]))
		{
			postfix +=expression[i];
			if (unaryToBinary == 1) {
				postfix +=expression[i];
				unaryToBinary = 0;
			}
		}

		else if (IsOperatorUnary(expression[i]))
		{
			while (!S.empty() && !IsOpeningParentheses(S.top())
				  && HasHigherPrecedence(S.top(),expression[i]))
			{
				postfix+= S.top();
				S.pop();
			}
			S.push(expression[i]);
			unaryToBinary = 1;
		}

		//If character is operator, check for Higher precedence operator in Stack top
		//till first opening bracket and pop all such operators
		//Finally push the current operator on the Stack
		else if (IsOperatorBinary(expression[i]))
		{
			while (!S.empty() && !IsOpeningParentheses(S.top())
				   && HasHigherPrecedence(S.top(),expression[i]))
			{
				postfix+= S.top();
				S.pop();
			}
			S.push(expression[i]);
		}

		//If opening Parentheses simply push it on the Stack
		else if (IsOpeningParentheses(expression[i]))
		{
			S.push(expression[i]);
		}

        //If Closing Parentheses then pop all the operators and append to res std::string
        // until Stack top is opening Parentheses and finally one extra pop for Opening Parentheses
		else if (IsClosingParentheses(expression[i]))
		{
			while (!S.empty() && !IsOpeningParentheses(S.top())) {
				postfix += S.top();
				S.pop();
			}
			if (S.empty()) {
				throw std::runtime_error("missing left paren");
			}
			// Discard the left paren
			S.pop();
		}

		else {
			throw std::runtime_error("invalid input character");
		}
	}

	//Finally pop and append all operators till Stack is not empty

	// Started with a left paren, now close it:
	// While top of stack is not a left paren
	while (!S.empty() && '(' != S.top()) {
		postfix += S.top();
		S.pop();
	}

    if (S.empty()) {
        throw std::runtime_error("missing left paren");
    }
    // Discard the left paren
     S.pop();

     // all open parens should be closed now -> empty stack
     if (!S.empty()) {
         throw std::runtime_error("missing right paren");
     }

	return postfix;
}

// Function to verify whether a character is english letter or numeric digit.
// We are assuming in this solution that operand will be a single character
bool IsOperand (char C)
{
	if(C >= '0' && C <= '9') return true;
	if(C >= 'a' && C <= 'z') return true;
	if(C >= 'A' && C <= 'Z') return true;
	return false;
}

// Function to verify whether a character is operator symbol or not.
bool IsOperatorBinary(char C)
{
	if (C == '+' || C == '-' || C == '*' || C == '/' || C== '^')
		return true;

	return false;
}

// Function to verify whether a character is operator symbol or not.
bool IsOperatorUnary(char C)
{
	if (C == '!')
		return true;

	return false;
}

bool IsOpeningParentheses(char C)
{
	if(C == '(' || C == '{' || C=='[')
		return true ;
	return false;
}

bool IsClosingParentheses(char C)
{
    if(C == ')' || C == '}' || C==']')
        return true ;
    return false;
}
// Function to verify whether an operator is right associative or not.
int IsRightAssociative(char op)
{
	if(op == '^') return true;
	return false;
}

// Function to get weight of an operator. An operator with higher weight will have higher precedence.
#if 0
int GetOperatorWeight(char op)
{
	int weight = -1;
	switch(op)
	{
	case '+':
	case '-':
		weight = 1;
		break ;
	case '*':
	case '/':
		weight = 2;
		break ;
	case '^':
		weight = 3;
	}
	return weight;
}
#else /* 0 */
int GetOperatorWeight(char op)
{
	int weight = -1;
	switch(op)
	{
	case '^':
		weight = 1;
		break ;
	case '|':
		weight = 2;
		break ;
	case '+':
		weight = 3;
		break ;
	case '!':
		weight = 4;
		break ;
	}
	return weight;
}
#endif /* 0 */

// Function to perform an operation and return output.
int HasHigherPrecedence(char op1, char op2)
{
	int op1Weight = GetOperatorWeight(op1);
	int op2Weight = GetOperatorWeight(op2);

	// If operators have equal precedence, return true if they are left associative.
	// return false, if right associative.
	// if operator is left-associative, left one should be given priority.
	if(op1Weight == op2Weight)
	{
		if (IsRightAssociative(op1))
			return false;
		else
			return true;
	}
	return op1Weight > op2Weight ?  true: false;
}
