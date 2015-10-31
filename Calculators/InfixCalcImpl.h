#ifndef _INFIX_CALC_IMPL_H
#define _INFIX_CALC_IMPL_H

#include "InfixCalc.h"
#include <limits>
#include <string>
#include <iostream>
#include <istream>
#include <fstream>

/* Default Constructor */
InfixCalc::InfixCalc() : myExpression("NULL"), myAnswer(0){
} // end default constructor

/* Parameterized Constructor*/
InfixCalc::InfixCalc(std::string& aString) : myExpression(aString), myAnswer(0) {
} // end Parameterized Constructor

/* Executes an operation */
void InfixCalc::Execute(){
	int operand2 = valStack.peek();
	valStack.pop();
	int operand1 = valStack.peek();
	valStack.pop();
	char op = opStack.peek();
	opStack.pop();
	int result = performOperation(operand1, operand2, op);
	valStack.push(result);
} // end Execture

int InfixCalc::performOperation(const int& op1, const int& op2, const char& myOperation) const{
	int result;
	switch (myOperation)
	{	
	case '+':
		result = op1 + op2;
		break;
	case '-':
		result = op1 - op2;
		break;
	case '/':	
		result = op1 / op2;
		break;
	case '*':
		result = op1 * op2;
		break;
	default:
		result = -1;
	}
	return result;
} // end perform operation

/* Initializes expression to evaluate if default constructor used */
void InfixCalc::initializeExpression() {
	if (myExpression == "NULL")
	{
		std::cout << "Please input a syntactically correct infix expression to solve: ";
		std::getline(std::cin, myExpression);
		std::cout << std::endl << "Thank you.  Evaluating the expression." << std::endl << std::endl;
		std::cout << "Your input: " << myExpression << std::endl;
	}
}

/* Checks if operator 1 is greater precedence than operator 2 */
bool InfixCalc::precedence(const char& operator1, const char& operator2) const
{
	bool hasPrecedence = false;
	if (opStack.isEmpty())
	{
		hasPrecedence = false;
	}
	else if (operator1 == '+' || operator1 == '-')
	{
		if (operator2 == '+' || operator2 == '-')
			{
				hasPrecedence = true;
			}
		else hasPrecedence = false;
	}
	else if (operator1 == '*' || operator1 == '/')
	{
		if (operator2 == '*' || operator2 == '/')
		{
			hasPrecedence = true;
		}
		else hasPrecedence = false;
	}
	return hasPrecedence;
} // end precedence

/* Solves a infix expression using an infix stack algorithm*/
void InfixCalc::solveExpression()
{
	initializeExpression(); // prompts user for expression if one not given
	for (int loopVar = 0; loopVar < myExpression.size(); loopVar++)
	{
		switch (myExpression[loopVar])
		{
		case ('(') :
			opStack.push(myExpression[loopVar]);
			break;
		case(')'):
			while (opStack.peek() != '(')
			{	
				Execute(); // execute what operations are inside the parenthesis
			}
				 opStack.pop(); // pop the open parenthesis
				 break;
		case('+') :
		case('-') :
		case('*') :
		case('/') :
				  if (opStack.isEmpty() || opStack.peek() == '(')
				  {
					  opStack.push(myExpression[loopVar]);
				  }
				  else if (precedence(opStack.peek(), myExpression[loopVar]))
				  {
					Execute();  // execute what's on the list
					opStack.push(myExpression[loopVar]); // push the operator
				  }
				  else // expression has precedence, so push it on the stack and continue
				  {
					opStack.push(myExpression[loopVar]);
				  }
				  break;
		default: // default case: value is a digit
			int value = charToStringToInt(myExpression[loopVar]);	
			valStack.push(value);
		} // end switch
	} // end for
	// do for rest of operators
	while (!opStack.isEmpty())
	{
		Execute();
	}
	myAnswer = valStack.peek();
	std::cout << myExpression << "=" << myAnswer << std::endl;
	getNewExpression();
}

int InfixCalc::charToStringToInt(const char& aChar) const {
	std::stringstream ss; // open up string string
	ss << aChar; // input char to stringstream
	std::string myString;
	ss >> myString; // output to myString
	int myValue = std::stoi(myString); // convert string to integer
	return myValue;
}

bool InfixCalc::isOperator(const char& aChar) const {
	bool isOperator = false;
	int loopVar = 0;
	while (loopVar < myOperators.size() && !isOperator)
	{
		if (aChar == myOperators[loopVar])
		{
			isOperator = true;
		}
		loopVar++;
	}
	return isOperator;
}


void InfixCalc::getNewExpression() {
	std::cout << "\nSupply another infix expression? <y/n>: ";
	std::string  x;
	std::getline(std::cin, x);
	while ((x != "y") && (x != "n"))
	{
		std::cout << std::endl;
		std::cout << "Invalid input.  Supply another infix expression? <y/n>: ";
		std::getline(std::cin, x);
	}
/*	if (x == "y")
	{
		std::cout << "\nEnter infix expression: ";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		myExpression.clear();
		std::getline(std::cin, myExpression);
		solveExpression();
	}*/
	if (x == "y")
	{
	// Reset expression
	myExpression = "NULL";
	solveExpression();
	}
}


#endif /* _INFIX_CALC_IMPL_H */
