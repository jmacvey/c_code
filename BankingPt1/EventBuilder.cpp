/* Implementation File for Event Builder */

#include "EventBuilder.h"

/* default constructor */
EventBuilder::EventBuilder() {
	using std::cout; using std::ifstream; using std::endl; using std::cin;
	std::string fileName;
	// get path to data file from user
	cout << "Provide path to file with event data: " << endl;
	getline(cin, fileName);
	// open an input file stream
	cout << "Opening a filestream on " << fileName << endl;
	std::ifstream myFile(fileName);
	// validate that the file is open and readable
	while (!myFile.good())
	{
		myFile.close();
		cout << "File cannot be found.  Provide path to file with event data: ";
		fileName.clear();
		getline(cin, fileName);
		myFile.open(fileName);
	}
	myFile.close();
	cout << "File stream opened..." << endl;
	myFileStream.open(fileName);
}

Event EventBuilder::BuildArrivalEvent(int number)
{
	using std::cout; using std::endl;
	// check if we're at the end of the file
	// if so build the dummy event and return it
	if (myFileStream.eof())
	{
		Event endEvent(ARRIVAL, END_OF_FILE_SIGNAL, END_OF_FILE_SIGNAL, END_OF_FILE_SIGNAL);
		return endEvent;
	}
	else {
		Time arrivalTime;
		myFileStream >> arrivalTime;
		Time tLength;
		myFileStream >> tLength;
	//cout << "Building ArrivalEvent with the following characteristics: " << endl;
	//cout << "ArrivaTime: " << arrivalTime << endl;
	//cout << "tLength: " << tLength << endl;
	//cout << "customerNo: " << number << endl;
		// burn the rest of the line
		std::string temp;
		getline(myFileStream, temp);
		Event arrivalEvent(ARRIVAL, arrivalTime, tLength, number);
		return arrivalEvent;
	}
}

Event EventBuilder::BuildDepartureEvent(Time currentEventTime, Time transactionLength, int number) {
	using std::cout; using std::endl;
	//cout << "Building DepartureEvent with the following characteristics: " << endl;
	//cout << "Departure Time: " << currentEventTime + transactionLength << endl;
	//cout << "customerNo: " << number << endl;
	Event departureEvent(DEPARTURE, currentEventTime + transactionLength, 0, number);
	return departureEvent;
}
