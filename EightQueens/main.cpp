#include "Board.h"
#include "Queen.h"
#include <string>

int main()
{
	Board myNewBoard;
	myNewBoard.display();
	myNewBoard.doEightQueens();
	myNewBoard.display();
	std::string x;
	std::cout << "Testing Complete! Exit? <y>: ";
	std::getline(std::cin, x);
	while (x != "y")
	{
		std::cout << "Invalid Response.  Exit? <y>:";
		std::getline(std::cin, x);
		std::cout << endl;
	}
	return 0;
}
