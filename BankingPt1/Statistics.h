#ifndef _STATISTICS_H
#define _STATISTICS_H

#include "Event.h"
#include <queue>
#include <iostream>

class Statistics {
private:
	int count;
	int waitTime;
	std::queue<Event> bankLine;
public:
	Statistics(); // default constructor 
	void addEvent(const Event& newEvent);
	void reportStats();
};


#endif