#ifndef _STATISTICS_H
#define _STATISTICS_H

#include "Event.h"
#include <queue>
#include <iostream>

class Statistics {
private:
	// customer count for three teller lines
	int countOne;
	int countTwo;
	int countThree;
	// Wait time for three teller lines
	int waitTimeOne;
	int waitTimeTwo;
	int waitTimeThree;
	// bank lines for the three tellers
	std::queue<Event> bankLineOne;
	std::queue<Event> bankLineTwo;
	std::queue<Event> bankLineThree;
public:
	Statistics(); // default constructor 
	void addEvent(const Event& newEvent);
	void reportStats();
	int getWaitTimeOne() const;
	int getWaitTimeTwo() const;
	int getWaitTimeThree() const;
};


#endif