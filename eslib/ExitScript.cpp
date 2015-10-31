#include <iostream>
#include <string>
#include "ExitScript.h"

void exitScript(){
	using std::cout; using std::cin; using std::endl;
	cout << "Testing Complete! Exit? <y>:";
	std::string y;
	std::getline(cin, y);
	while (y != "y")
	{
		cout << endl << "Invalid input.  Exit? <y>:";
		std::getline(cin, y);
	}
};
