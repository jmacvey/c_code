#ifndef _POST_FIX_IMPL_H
#define _POST_FIX_IMPL_H

#include "PostFixCalculator.h"
#include <string>
#include <iostream>
#include <fstream>

PostFixCalculator::PostFixCalculator() :myExpression("NULL"), myAnswer(0) {
	//default constructor
}

PostFixCalculator::PostFixCalculator(const std::string& aString) : myExpression(aString), myAnswer('0') {
	//parameterized constructor
}

void PostFixCalculator::solveExpression() {
	//prompt user for an expression if one not already provided
	initializeExpression();
	int expressionLength = myExpression.size();
	std::cout << "expressionLegnth: " << myExpression.size() << std::endl;
	// Counts the beginning of the next piece of the string to evaluate
	int stringBegin = 0;
	// Counts the number of characters in the current integer
	int charCounter = 0;
	for (int loopVar = 0; loopVar < expressionLength; loopVar++)
	{
		bool isOperator = false;
		for (int loopVarTwo = 0; loopVarTwo < myOperators.size(); loopVarTwo++)
		{
			if (myExpression[loopVar] == myOperators[loopVarTwo])
			{
				isOperator = true;
			}
		}
		if (!isOperator) // if item is not an operator, it must be a character
			// if that character is a space, it signifies the end of the integer
		{
			if (myExpression[loopVar] == ' ')
			{	
				int Value = std::stoi(myExpression.substr(stringBegin, charCounter));
				charCounter = 0; //reset the charCounter
				myCalc.push(Value);	
				stringBegin = loopVar + 1; // the next integer string begins after the space
			}
			else charCounter++;
		}
		else { // item is an operator
			int operand2 = (myCalc.peek());
			myCalc.pop();
			int operand1 = (myCalc.peek());
			myCalc.pop();
			int result = performOperation(operand1, operand2, myExpression[loopVar]);	
			myCalc.push(result);	
			stringBegin = loopVar + 2; // the next integer string begins after the space
			charCounter = 0; // reset the charCounter
			loopVar++; // skip the next space
		}
	}
	myAnswer = myCalc.peek(); // myAnswer is the peek of the stack
	std::cout << myExpression << " = " << myAnswer << ".";
	myCalc.pop(); // pop the answer
	getNewExpression(); // asks the user for a new expression
}

void PostFixCalculator::initializeExpression() {
	if (myExpression == "NULL")
	{
		std::cout << "Please input a syntactically correct Postfix expression to solve: ";
		std::getline(std::cin, myExpression);
		std::cout << "Thank you.  Evaluating the expression." << std::endl;
		std::cout << "Your input: " << myExpression << std::endl;
	}
}


char PostFixCalculator::getMyAnswer() const {
	return myAnswer;
}

int PostFixCalculator::performOperation(const int& op1, const int& op2, const char& myOperation) const {
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
	}
	return result;
}

void PostFixCalculator::getNewExpression() {
	std::cout << "\nSupply another postfix expression? <y/n>: ";
	std::string x;
	std::getline(std::cin, x);
	while ((x != "y") && (x != "n"))
	{
		std::cout << std::endl;
		std::cout << "Invalid input.  Supply another postfix expression? <y/n>: ";
		std::getline(std::cin, x);
	}
	if (x == "y")
	{
		std::cout << "\nEnter postfix expression: ";
		std::getline(std::cin, myExpression);
		solveExpression();
	}
}

std::string PostFixCalculator::getMyExpression() const {
	return myExpression;
}


#endif
