#ifndef _INFIX_TO_POSTFIX_IMPL_H
#define _INFIX_TO_POSTFIX_IMPL_H

#include "InfixToPostfix.h"
#include <iostream>
#include <stack>
#include <sstream>
#include <string>

InfixToPostfix::InfixToPostfix() : myExpression("NULL"), postFixExp(""){
	//default constructor
}

InfixToPostfix::InfixToPostfix(const std::string& aString) : myExpression(aString), postFixExp(""){
	//parameterized constructor
}

void InfixToPostfix::translateInToPost() {
	// asks user for input if none provided
	initializeExpression();
	std::cout << "Your Expression is: " << myExpression << std::endl;
	for (int loopVar = 0; loopVar < myExpression.size(); loopVar++)
	{
		std::cout << "next character considered: " << myExpression[loopVar] << std::endl;
		switch (myExpression[loopVar])
		{
		case('(') :// push it on the stack
			std::cout << "Encounter a \"(\".  Appending it to the postFixExp." << std::endl;
			myCalc.push(myExpression[loopVar]);
			break;
		case('+') :
		case('-') :
		case('*') :
		case('/') :
				  std::cout << "This character is an operator." << std::endl;
			while (!myCalc.isEmpty() && isOperator(myExpression[loopVar]) && myCalc.peek() != '(' && precedence(myExpression[loopVar], myCalc.peek()))
			{
				// convert char on top of stack to string and append to postFix
				postFixExp.append(charToString(myCalc.peek()));
				// pop the item from the stack
				myCalc.pop();
			}
			std::cout << "Pushing the operator on the stack." << std::endl;
			myCalc.push(myExpression[loopVar]); // push the operator on the stack
			break;
		case(')') : // pop stack until matching '('
			while (myCalc.peek() != '(')
			{
				std::cout << "Encountered a \")\". Appending the " << charToString(myCalc.peek()) << std::endl;
				postFixExp.append(charToString(myCalc.peek()));
				if (loopVar != myExpression.size() - 1)
				{
					appendSpace(); // append a space for every operator unless ')' is final character in string
				}
				std::cout << "Popping the " << charToString(myCalc.peek()) << std::endl;
				myCalc.pop();
				std::cout << "Pop successful.  Moving onto " << myCalc.peek() << std::endl;
			}
					std::cout << "Popping successful.  Popping once more." << std::endl;
					myCalc.pop(); // pop the '('
					break;
		default: // if none of the above cases are true, it's an operand
			// get the character length of the operand
			int charCounter = 0;
			int currentChar = loopVar;
			std::cout << "currentChar = " << loopVar << std::endl;
			// while the next character is not an operator or a parenthesis
			// it is part of the current integer (i.e. we can represent it as a substring)
			while (loopVar < myExpression.size() && !isOperator(myExpression[loopVar]) && !isParenthesis(myExpression[loopVar]))
			{
				std::cout << "Entering while loop: " << std::endl;
				charCounter++;
				loopVar++; // skip the next character eval
			}
			loopVar--; // adjust the loop variable for the for loop
			std::cout << "charCounter = " << charCounter << std::endl;
			std::cout << "the integer = " << myExpression.substr(currentChar, charCounter) << std::endl;
			// extract the integer from the string
			std::string mySub = myExpression.substr(currentChar, charCounter);
			std::cout << "Default case accepted!  Appending " << mySub
				<< " to the postfix." << std::endl;
			postFixExp.append(mySub);
			if (loopVar != myExpression.size() - 1)
			{
				appendSpace(); // append a space on every integer but the last
			}
		} // end switch
	} // end for
	while (!myCalc.isEmpty())
	{
		appendSpace();
		postFixExp.append(charToString(myCalc.peek()));
		myCalc.pop();
	}
	std::cout << "PostFix Equivalent is " << postFixExp << std::endl;
}

void InfixToPostfix::initializeExpression() {
	if (myExpression == "NULL")
	{
		std::cout << "Please input a syntactically correct infix expression to solve: ";
		std::getline(std::cin, myExpression);
		std::cout << std::endl << "Thank you.  Evaluating the expression." << std::endl << std::endl;
		std::cout << "Your input: " << myExpression << std::endl;
	}
}

bool InfixToPostfix::isOperator(const char& aChar) const {
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

bool InfixToPostfix::precedence(const char& operator1, const char& operator2) const
{
	bool hasPrecedence = false;
	if (myCalc.isEmpty())
	{
		hasPrecedence = false;
	}
	else if ((operator1 == '+' || operator1 == '-') && !myCalc.isEmpty())
		hasPrecedence = true;
	else if (operator1 == '*' || operator1 == '/')
	{
		if (operator2 == '*' || operator2 == '/')
		{
			hasPrecedence = true;
		}
		else hasPrecedence = false;
	}
	return hasPrecedence;
}

std::string InfixToPostfix::charToString(const char& aChar) const {
	std::stringstream ss;
	ss << aChar;
	std::string returnString;
	ss >> returnString;
	return returnString;
}

bool InfixToPostfix::isParenthesis(const char& aChar) const {
	bool isPar = ((aChar == '(') || (aChar == ')'));
	return isPar;
}

void InfixToPostfix::appendSpace() {
	std::string mySpace = " ";
	postFixExp.append(mySpace);
}

void InfixToPostfix::solveExpression() {
	int expressionLength = postFixExp.size();
	std::cout << "expressionLegnth: " << postFixExp.size() << std::endl;
	// Counts the beginning of the next piece of the string to evaluate
	int stringBegin = 0;
	// Counts the number of characters in the current integer
	int charCounter = 0;
	for (int loopVar = 0; loopVar < expressionLength; loopVar++)
	{
		std::cout << "loopVar: " << loopVar << std::endl;
		bool isOperator = false;
		for (int loopVarTwo = 0; loopVarTwo < myOperators.size(); loopVarTwo++)
		{
			if (postFixExp[loopVar] == myOperators[loopVarTwo])
			{
				isOperator = true;
			}
		}
		if (!isOperator) // if item is not an operator, it must be a character
			// if that character is a space, it signifies the end of the integer
		{
			if (postFixExp[loopVar] == ' ')
			{
				std::cout << "Pushing " << postFixExp.substr(stringBegin, charCounter) << " onto stack. \n";
				int Value = std::stoi(postFixExp.substr(stringBegin, charCounter));
				charCounter = 0; //reset the charCounter
				myCalc.push(Value);
				std::cout << "Push successful" << std::endl;
				stringBegin = loopVar + 1; // the next integer string begins after the space
			}
			else charCounter++;
		}
		else { // else is an operators
			int op2 = (myCalc.peek());
			myCalc.pop();
			int op1 = (myCalc.peek());
			myCalc.pop();
			int result = performOperation(op1, op2, postFixExp[loopVar]);
			std::cout << "\nOperator Reached: " << postFixExp[loopVar] << "\nResult = " << result << "\n";
			myCalc.push(result);
			std::cout << "peek of stack reads: " << myCalc.peek() << std::endl;
			stringBegin = loopVar + 2; // the next integer string begins after the space
			charCounter = 0; // reset the charCounter
			loopVar++; // skip the next space
		}
	}
	myAnswer = myCalc.peek(); // myAnswer is the peek of the stack
	std::cout << myExpression << " = " << myAnswer << ".";
	myCalc.pop(); // pop the answer
}

int InfixToPostfix::performOperation(const int& op1, const int& op2, const char& myOperation) const {
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

		break;
	case '*':
		result = op1 * op2;
		break;
	}
	return result;
}

std::string InfixToPostfix::getPostfix() const{
	return postFixExp;
}
#endif