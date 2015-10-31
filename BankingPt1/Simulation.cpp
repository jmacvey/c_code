/** Implementation file for Simulation */

#include "Simulation.h"

Simulation::Simulation() : customerNo(1) {};

void Simulation::simulate() {
	using std::cout; using std::endl;
	cout << "Simulation of 1 Queue Begins..." << endl;
	// build an initial arrival event &
	// push that event on the eventList
	events.push(eventBuilder.BuildArrivalEvent(customerNo));
	while (!events.empty())
	{
		// retrieve the next item in the events
		currentEvent = events.top();
		// check for the endEvent
		if (currentEvent.getNumber() == 0)
		{
			events.pop();
		}
		else
		{
			if (currentEvent.getEventType() == ARRIVAL)
			{
				// test to see if event is finalEvent.
				// for more info 
				// see EventBuilder.cpp EventBuilder::BuildArrivalEvent implementation.
				processArrival();
				// add the event to the stats list
			}
			else
			{
				processDeparture();

			}
			// add the event to the stats list
			stats.addEvent(currentEvent);
		}
	}
	// generate a statistics report
	stats.reportStats();
}

void Simulation::processArrival() {
	// teller is available if line is empty -> can create a departure event and add it to the list
	using std::cout; using std::endl;
	cout << "Processing an arrival event at time: " << currentEvent.getTime() << endl;
	// remove the event from the event list
	events.pop();
	if (tellerLine.empty())
	{
		// push the value onto the tellerLine
		tellerLine.push(currentEvent);
		// create the departure event for the customer
		// departure time is currentTime + the eventLength time
		//cout << "Building DepartureEvent with the following characteristics: " << endl;
		//cout << "Departure Time: " << currentEvent.getTime() + currentEvent.getLength() << endl;
		//cout << "customerNo: " << currentEvent.getNumber() << endl;
		Event departureEvent = eventBuilder.BuildDepartureEvent(currentEvent.getTime(),
			currentEvent.getLength(), currentEvent.getNumber());
		// add this departure event to the event list
		events.push(departureEvent);
	}
	else
	{
		//cout << "pushing customerNo " << customerNo << " onto the tellerLine." << endl;
		// push the customer onto the bank line
		tellerLine.push(currentEvent);
	}
	// create a new customer arrival and push it onto the event stack
	customerNo++;
	Event nextEvent = eventBuilder.BuildArrivalEvent(customerNo);
	//cout << "Testing event builder comparator: " << endl;
	//bool testop = nextEvent > events.top();
	//cout << "operator> returns: " << testop << "should be 1." << endl;
	events.push(nextEvent);
}

void Simulation::processDeparture() {
	// currentEvent = the head of the events list (the departure event).
	using std::cout; using std::endl;
	cout << "Processing a departure event at time: " << currentEvent.getTime() << endl;
	// remove the departure event from the event list
	events.pop();
	if (!tellerLine.empty())
	{
		// dequeue from the teller line
		//cout << "Popping from teller line." << endl;
		tellerLine.pop();
		//cout << "popped from teller line... " << endl;
		// create the new departure event
		// push a new departure event onto the events list with 
		// departure time = current departure time + newtransactionLength
		// and of course the new customer number
		if (!tellerLine.empty())
		{
			events.push(eventBuilder.BuildDepartureEvent(currentEvent.getTime(),
				tellerLine.front().getLength(), tellerLine.front().getNumber()));
		}
		//cout << "exiting processDeparture(); " << endl;
	}
}