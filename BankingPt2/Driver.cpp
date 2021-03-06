/** Driver file for the bank project */

#include "Event.h"
#include "EventBuilder.h"
#include "EventType.h"
#include "Time.h"
#include "Statistics.h"
#include <iostream>
#include <string>
#include "Simulation.h"


void exitScript(){
	using std::cout; using std::cin; using std::endl;
	cout << "Testing Complete! Exit? <y>:";
	std::string temp;
	getline(cin, temp);
	while (temp != "y")
	{
		cout << endl << "Invalid input.  Exit? <y>:";
		getline(cin, temp);
	}
};


int main() {
	Simulation mySim;
	mySim.simulate();
	exitScript();
}
