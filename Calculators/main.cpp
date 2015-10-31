//-------------------------------------------------------------
// Calculators Stack Exercise Driver
//-------------------------------------------------------------


//-------------------------------------------------------------
// Include FIles
//-------------------------------------------------------------

#include <iostream>
#include <string>
#include <stack>
#include "OurStack.h"
#include "StackInterface.h"
#include "InfixCalc.h"
#include "PostFixCalculator.h"
#include "ExitScript.h"

//-------------------------------------------------------------
// Garbage - Basura - you know - unrelated stuff!
//-------------------------------------------------------------

//Implementation for isInL
/*bool isInL(const std::string& aString) {
	std::stack<char> aStack;
	bool isInLanguage = true;
	// if the string is empty or contains an odd number of characters
	// then the string is not in the language.
	int stringLength = aString.size();
	if (stringLength % 2 != 0 || stringLength == 0)
	{
		isInLanguage = false;
	}
	else {
		// find the midpoint
		int midPoint = stringLength / 2;
		// push all chharacters up to the midpoint on the stack
		for (int loopVar = 0; loopVar < midPoint; loopVar++)
		{
			aStack.push(aString[loopVar]); // push
		}
		//now check to see if each character matches the character on the stack
		int charRemaining = midPoint;
		// it's in the language until we prove it's not
		// we don't need to test if the stack will ever be empty
		// since the # items on the stack is exactly
		// the # items remaining in the string. 
		while (charRemaining < stringLength && isInLanguage)
		{
			// if the character does not match, it is not in the language
			if (aString[charRemaining] != aStack.top())
			{
				isInLanguage = false;
			} //end if
			charRemaining++;
			aStack.pop();
		} // end while
	}
	return isInLanguage;
}*/ 

/*
void stackTester(OurStack<char>& aStack){
	std::cout << "Initializing stackTester: \n" << "Initial Stack is empty." <<
		"aStack.isEmpty() returns: " << aStack.isEmpty() << "; should be 1 (true). \n";
	std::cout << "Pushing onto stack. \n";
	char myTestChar = 'T';
	aStack.push(myTestChar);
	std::cout << "Top of stack reads: " << aStack.peek() << "; should read: " << myTestChar << "\n" <<
		"aStack.isEmpty() returns: " << aStack.isEmpty() << "; should be 0 (false). \n" <<
		"popping from the stack." << std::endl;
	aStack.pop();
	std::cout << "aStack.isEmpty() returns: " << aStack.isEmpty() << "; should be 1 (true). \n";
}
*/


//-------------------------------------------------------------
// Entry Point
//-------------------------------------------------------------

int main() {
	/*std::string myString = "abc$cba";
	std::cout << "Testing isInLanguage(\"abc$cba\"): " << std::endl;
	std::cout << "Should return false.  It returns: " << isInL(myString) << std::endl;*/
	//OurStack<char> testStack;
	//stackTester(testStack);
	PostFixCalculator myCalc;
	myCalc.solveExpression();
	InfixCalc InfixCalcTest;
	InfixCalcTest.solveExpression();
	exitScript();
	return 0;
}
