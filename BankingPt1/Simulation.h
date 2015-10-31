#ifndef _SIMULATION_H
#define _SIMULATION_H


#include "Event.h"
#include "Statistics.h"
#include "EventBuilder.h"
#include <queue>
#include <functional>
#include <vector>

/** forward declarations of class objects */
class Event;
class EventBuilder;
class Statistics;

class Simulation {
private:
	int customerNo;
	EventBuilder eventBuilder;
	Event currentEvent;
	Statistics stats;
	// priority queue of events; uses the greater definition as supplied by event
	std::priority_queue< Event, std::vector<Event>, std::greater<Event> > events;
	// standard queue for the bank line
	std::queue<Event> tellerLine;
	// utility methods
	void processArrival();
	void processDeparture();
public:
	Simulation(); // default constructor 
	void simulate();
};


#endif