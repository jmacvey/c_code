// PROGRAMMING PROBLEM 6:  GOOD FOR VALUES < 12

#ifndef _INFIX_TO_POSTFIX_H
#define _INFIX_TO_POSTFIX_H

#include "OurStack.h"
#include <stack>
#include <string>
#include <iostream>

class InfixToPostfix
{
private:
	OurStack<char> myCalc; // Stack will be the ultimate calculator
	std::string myExpression; // String to hold the infix expression
	std::string postFixExp; // string to hold postfix expression
	const std::string myOperators = "+*/-"; // string of operators
	/* appends a space to the postfixExp */
	void appendSpace();
	int myAnswer; // answer to the infix expression
public:
	/** Default constructor */
	/* Default Constructor */
	InfixToPostfix();
	/* Parameterized Constructor
	*@param myString The string to be evaluated
	*/
	InfixToPostfix(const std::string& aString);
	/* Asks the user for an expression if default constructor used */
	/** Translates the infix expression to its postfix equivalent 
	@post : postFixExp contains translated expression */
	void translateInToPost();
	/* Initializes expression to evaluate if default constructor used */
	void initializeExpression();
	/* Checks if string is an operator */
	bool isOperator(const char& aChar) const;
	/* Checks if operator 1 is greater precedence than operator 2 */
	bool precedence(const char& operator1, const char& operator2) const;
	/* Converts a char to a string */
	std::string charToString(const char& aChar) const;
	/* checks if a character is a parenthesis */
	bool isParenthesis(const char& aChar) const;
	/* Solves a translated postfix expression using a postfix algorithm*/
	void solveExpression();
	/** performs and operation */
	int performOperation(const int& op1, const int& op2, const char& myOperation) const;
	/** gets postfix expression */
	std::string getPostfix() const;



};

#include "InfixtoPostfixImpl.h"

#endif