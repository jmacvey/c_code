#ifndef _INFIX_CALC_H
#define _INFIX_CALC_H

// PROGRAMMING PROBLEM 8

#include "OurStack.h"
#include <iostream>
#include <string>
#include <sstream>


class InfixCalc {
private:
	OurStack<int> valStack; // value stack to contain characters
	OurStack<char> opStack; // opStack to contain operators
	std::string myExpression; // expression to evaluate
	int myAnswer; // answer to expression 
	const std::string myOperators = "+*/-"; // string of operators for calculator
public:
	/* Default Constructor */
	InfixCalc();
	/* Parameterized Constructor */
	InfixCalc(std::string& aString);
	/* Executes an operation */
	void Execute();
	/** performs an operation */
	int performOperation(const int& op1, const int& op2, const char& myOperation) const;
	/* Initializes expression to evaluate if default constructor used */
	void initializeExpression();
	/* Checks if operator 1 is greater precedence than operator 2 */
	bool precedence(const char& operator1, const char& operator2) const;
	/* Solves a infix expression using an infix stack algorithm*/
	void solveExpression();
	/* prompts user for a new expression after solving the first one */
	void getNewExpression();
	/* Checks if char is an operator */
	bool isOperator(const char& aChar) const;
	/* Converts a char to a string to an int */
	int charToStringToInt(const char& aChar) const;
};

#include "InfixCalcImpl.h"

#endif
