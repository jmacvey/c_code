#ifndef _POST_FIX_CALCULATOR_H
#define _POST_FIX_CALCULATOR_H

#include "OurStack.h"
#include <string>
#include <stack>


class PostFixCalculator {
private:
	OurStack<int> myCalc; // Stack will be the ultimate calculator
	std::string myExpression; // String to hold the expression
	int myAnswer; // String to hold the latest expression
	const std::string myOperators = "+*/-"; // string of operators
public:
	/* Default Constructor */
	PostFixCalculator();
	/* Parameterized Constructor
	 *@param myString The string to be evaluated
	 @return evaluation of the expression as a character
	 */
	PostFixCalculator(const std::string& aString);
	/* Asks the user for an expression if default constructor used */
	void initializeExpression();
	/* Solves the expression of the current string
	 *@param aString the expression to solve
	 @pre aString is a syntactically correct postFix expression
	 @post myAnswer stores the answer to the expression
	 outputs expression to string
	 prompts user for another expression to solve*/
	void solveExpression();
	/** Accepts newString as the new expression to solve */
	void newString() const;
	/** Accessor for latest expression */
	char getMyAnswer() const;
	/** Accessor for current string */
	std::string getMyExpression() const;
	/** Gets another expression to solve if user wants */
	void getNewExpression();
	/** 
	* @param op1 first operand
		     op2 second operand
	* @pre expects operator to be at top of stack 
	* @post pops operator from the stack
	* @return returns result of operation */
	int performOperation(const int& op1, const int& op2, const char& myOperation) const;
};

#include "PostFixImpl.h"
#endif
