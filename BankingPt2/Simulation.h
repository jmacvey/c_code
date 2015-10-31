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
	// current events in each of the queues
	Event currentEventOne;
	Event currentEventTwo;
	Event currentEventThree;
	Statistics stats;
	// priority queue of events; uses the greater definition as supplied by event
	std::priority_queue< Event, std::vector<Event>, std::greater<Event> > events;
	// standard queues for three bank lines
	std::queue<Event> tellerLineOne;
	std::queue<Event> tellerLineTwo;
	std::queue<Event> tellerLineThree;
	// utility methods
	void processArrivalQueueOne();
	void processDepartureQueueOne();
	void processArrivalQueueTwo();
	void processDepartureQueueTwo();
	void processArrivalQueueThree();
	void processDepartureQueueThree();
	int findMinimumQueue() const;
	void buildNextEvent();
	bool finalEventReached() const;
public:
	Simulation(); // default constructor 
	void simulate();
};


#endif