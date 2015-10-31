/** Implementation file for Statistics.h */

#include "Statistics.h"


Statistics::Statistics() : count(0), waitTime(0), bankLine() {
	// default constructor
}

void Statistics::addEvent(const Event& newEvent) {
	// if the event is an arrival
	if (newEvent.getEventType() == ARRIVAL)
	{
		// increment the count
		count++;
		// push the newEvent onto the bankLine
		bankLine.push(newEvent);
	}
	// else if the event is a departure
	else {
		// calculate the wait time for the customer and add to total waitTime
		waitTime += 
			newEvent.getTime() 
			- (bankLine.front().getTime() 
			+ bankLine.front().getLength());
		// pop the event from the bankline
		bankLine.pop();
	}
}

void Statistics::reportStats() {
	using std::cout; using std::endl;
	cout << "Final Statistics: " << endl << "\t";
	cout << "Total number of people processed: " << count << endl << "\t";
	cout << "Total wait time: " << waitTime << endl << "\t";
	cout << "Average amount of time spent waiting: " << static_cast<double>(waitTime)/count << endl;
}