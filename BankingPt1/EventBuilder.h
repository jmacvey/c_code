#ifndef _EVENT_BUILDER_H
#define _EVENT_BUILDER_H

#include "Event.h"
#include <iostream>
#include <fstream>
#include <string>

class EventBuilder{
private:
	// filestream associated with the simulation
	const int END_OF_FILE_SIGNAL = 0;
	std::ifstream myFileStream;
public:
	EventBuilder(); // Default constructor
	Event BuildArrivalEvent(int number); 
	Event BuildDepartureEvent(Time currentEventTime, Time transactionLength, int number);
};


#endif