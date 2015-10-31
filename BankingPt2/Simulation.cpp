/** Implementation file for Simulation */

#include "Simulation.h"

Simulation::Simulation() : customerNo(1) {};

void Simulation::simulate() {
	using std::cout; using std::endl;
	cout << "Simulation of 3 Queues Begins..." << endl;
	// build an initial arrival event for Queue 1 and push it on the eventList
	// push that event on the eventList
	events.push(eventBuilder.BuildArrivalEvent(customerNo, 1));
	while (!events.empty())
	{
		int currentQNumber = events.top().getQueueNumber();
		switch (currentQNumber)
		{
		case 1:
		{
			if (finalEventReached())
			{
				events.pop();
			}
			else
			{
				if (events.top().getEventType() == ARRIVAL)
				{
					processArrivalQueueOne();
				}
				else
				{
					processDepartureQueueOne();
				}
			}
		} // end case 1
		break;
		case 2:
		{
			if (finalEventReached())
			{
				events.pop();
			}
			else
			{
				if (events.top().getEventType() == ARRIVAL)
				{
					processArrivalQueueTwo();
				}
				else
				{
					processDepartureQueueTwo();
				}
			}
		} // end case 2
		break;
		case 3:
		{
			if (finalEventReached())
			{
				events.pop();
			}
			else
			{
				if (events.top().getEventType() == ARRIVAL)
				{
					processArrivalQueueThree();
				}
				else
				{
					processDepartureQueueThree();
				}
			} // end default Case
		}
		break;
		}// end switch
		buildNextEvent();
	} // end while
	// generate a statistics report
	stats.reportStats();
}

/* ARRIVAL PROCESSES */
void Simulation::processArrivalQueueOne() {
	// teller is available if line is empty -> can create a departure event and add it to the list
	using std::cout; using std::endl;
	currentEventOne = events.top();
	cout << "Processing an arrival event " << currentEventOne.getNumber() << " in queue 1 at time: " << currentEventOne.getTime() << endl;
	// remove the event from the event list
	int qNumber = 1;
	events.pop();
	if (tellerLineOne.empty())
	{
		// push the value onto the tellerLineOne 
		tellerLineOne.push(currentEventOne);
		// create the departure event for the customer
		// departure time is currentTime + the eventLength time
		//cout << "Building DepartureEvent with the following characteristics: " << endl;
		//cout << "Departure Time: " << currentEvent.getTime() + currentEvent.getLength() << endl;
		//cout << "customerNo: " << currentEvent.getNumber() << endl;
		// build the departure event and push that onto the events list
		Event departureEvent = eventBuilder.BuildDepartureEvent(currentEventOne.getTime(),
			currentEventOne.getLength(), currentEventOne.getNumber(), qNumber);
		// add this departure event to the event list
		events.push(departureEvent);
	}
	else
	{
		//cout << "pushing customerNo " << customerNo << " onto the tellerLine." << endl;
		// push the customer onto the bank line
		tellerLineOne.push(currentEventOne);
	}
	// process the stats to the stat list
	stats.addEvent(currentEventOne);
}

void Simulation::processArrivalQueueTwo()
{
	using std::cout; using std::endl;
	currentEventTwo = events.top();
	cout << "Processing an arrival event " << currentEventTwo.getNumber() << " in queue 2 at time: " << currentEventTwo.getTime() << endl;
	// remove the events from the event list
	int qNumber = 2;
	events.pop();
	if (tellerLineTwo.empty())
	{
		// push the value onto the tellerLineOne 
		tellerLineTwo.push(currentEventTwo);
		// create the departure event for the customer
		// departure time is currentTime + the eventLength time
		//cout << "Building DepartureEvent with the following characteristics: " << endl;
		//cout << "Departure Time: " << currentEvent.getTime() + currentEvent.getLength() << endl;
		//cout << "customerNo: " << currentEvent.getNumber() << endl;
		// build the departure event and push that onto the events list
		Event departureEvent = eventBuilder.BuildDepartureEvent(currentEventTwo.getTime(),
			currentEventTwo.getLength(), currentEventTwo.getNumber(), qNumber);
		// add this departure event to the event list
		events.push(departureEvent);
	}
	else
	{
		// cout << "pushing customerNo " << customerNo << " onto the tellerLine." << endl;
		// push the customer onto the bank line
		tellerLineTwo.push(currentEventTwo);
	}
	stats.addEvent(currentEventTwo);
}

void Simulation::processArrivalQueueThree() {
	using std::cout; using std::endl;
	currentEventThree = events.top();
	cout << "Processing an arrival event " << currentEventThree.getNumber() << " in queue 3 at time: " << currentEventThree.getTime() << endl;
	// remove the events from the event list
	int qNumber = 3;
	events.pop();
	if (tellerLineThree.empty())
	{
		// push the value onto the tellerLineOne 
		tellerLineThree.push(currentEventThree);
		// create the departure event for the customer
		// departure time is currentTime + the eventLength time
		//cout << "Building DepartureEvent with the following characteristics: " << endl;
		//cout << "Departure Time: " << currentEvent.getTime() + currentEvent.getLength() << endl;
		//cout << "customerNo: " << currentEvent.getNumber() << endl;
		// build the departure event and push that onto the events list
		Event departureEvent = eventBuilder.BuildDepartureEvent(currentEventThree.getTime(),
			currentEventThree.getLength(), currentEventThree.getNumber(), qNumber);
		// add this departure event to the event list
		events.push(departureEvent);
	}
	else
	{
		//cout << "pushing customerNo " << customerNo << " onto the tellerLine." << endl;
		// push the customer onto the bank line
		tellerLineThree.push(currentEventThree);
	}
	stats.addEvent(currentEventThree);
}

int Simulation::findMinimumQueue() const {
	using std::cout; using std::endl;
	int nextQNumber = 0;
	int qSizeOne = tellerLineOne.size();
	int qSizeTwo = tellerLineTwo.size();
	int qSizeThree = tellerLineThree.size();
	/*cout << "Current queue sizes: " << endl << "\t";
	cout << "qSizeOne: " << tellerLineOne.size() << endl << "\t";
	cout << "qSizeTwo: " << tellerLineTwo.size() << endl << "\t";
	cout << "qSizeThree: " << tellerLineThree.size() << endl << "\t";*/
	// find the next QNumber corresponding to shortest queue
	if (qSizeOne <= qSizeTwo && qSizeOne <= qSizeThree)
	{
		nextQNumber = 1;
	}
	else if (qSizeTwo <= qSizeOne && qSizeTwo <= qSizeThree)
	{
		nextQNumber = 2;
	}
	else
	{
		nextQNumber = 3;
	}
	//cout << "nextQNumber: " << nextQNumber << endl;
	return nextQNumber;
}

/* DEPARTURE PROCESSES */
void Simulation::processDepartureQueueOne() {
	// currentEvent = the head of the events list (the departure event).
	using std::cout; using std::endl;
	int qNumber = 1;
	currentEventOne = events.top();
	cout << "Processing a departure event " << currentEventOne.getNumber() << " at time: " << currentEventOne.getTime() << " in line #" << qNumber <<
		"; event: " << currentEventOne.getNumber() << "; " << endl;
	// remove the departure event from the event list
	events.pop();
	if (!tellerLineOne.empty())
	{
		// dequeue from the teller line
		//cout << "Popping from teller line." << endl;
		tellerLineOne.pop();
		//cout << "popped from teller line... " << endl;
		// create the new departure event
		// push a new departure event onto the events list with 
		// departure time = current departure time + newtransactionLength
		// and of course the new customer number
		if (!tellerLineOne.empty())
		{
			events.push(eventBuilder.BuildDepartureEvent(currentEventOne.getTime(),
				tellerLineOne.front().getLength(), tellerLineOne.front().getNumber(), qNumber));
		}
	}
	stats.addEvent(currentEventOne);
}

void Simulation::processDepartureQueueTwo() {
	using std::endl; using std::cout;
	int qNumber = 2;
	currentEventTwo = events.top();
	cout << "Processing a departure event " << currentEventTwo.getNumber() << " at time: " << currentEventTwo.getTime() << " in line #" << qNumber <<
		"; event: " << currentEventTwo.getNumber() << "; ";
	// remove the departure event from the event list
	events.pop();
	if (!tellerLineTwo.empty())
	{
		// dequeue from the teller line
		//cout << "Popping from teller line." << endl;
		tellerLineTwo.pop();
		//cout << "popped from teller line... " << endl;
		// create the new departure event
		// push a new departure event onto the events list with 
		// departure time = current departure time + newtransactionLength
		// and of course the new customer number
		if (!tellerLineTwo.empty())
		{
			events.push(eventBuilder.BuildDepartureEvent(currentEventTwo.getTime(),
				tellerLineTwo.front().getLength(), tellerLineTwo.front().getNumber(), qNumber));
		}
	}
	stats.addEvent(currentEventTwo);
}

void Simulation::processDepartureQueueThree() {
	using std::cout; using std::endl;
	int qNumber = 3;
	currentEventThree = events.top();
	cout << "Processing a departure event " << currentEventThree.getNumber() << " at time: " << currentEventThree.getTime() << " in line #" << qNumber <<
		"; event: " << currentEventThree.getNumber() << "; ";
	// remove the departure event from the event list
	events.pop();
	if (!tellerLineThree.empty())
	{
		// dequeue from the teller line
		//cout << "Popping from teller line." << endl;
		tellerLineThree.pop();
		//cout << "popped from teller line... " << endl;
		// create the new departure event
		// push a new departure event onto the events list with 
		// departure time = current departure time + newtransactionLength
		// and of course the new customer number
		if (!tellerLineThree.empty())
		{
			events.push(eventBuilder.BuildDepartureEvent(currentEventThree.getTime(),
				tellerLineThree.front().getLength(), tellerLineThree.front().getNumber(), qNumber));
		}
	}
	stats.addEvent(currentEventThree);
}

void Simulation::buildNextEvent() {
	// find minimumQueueSize
	int qForNextArrival = findMinimumQueue();
	// build the next arrival event and add it to events list
	customerNo++;
	// need to build the next event based on the state of the queues at the time the event happens
	Event prospectiveEvent = eventBuilder.BuildArrivalEvent(customerNo, qForNextArrival);
	// check that the event is not the end event
	if (prospectiveEvent.getNumber() != 0)
	{
		while (!events.empty() && events.top() < prospectiveEvent)
		{
			int nextQ = events.top().getQueueNumber();
			if (events.top().getEventType() == ARRIVAL)
			{
				switch (nextQ)
				{
				case 1:
					processArrivalQueueOne();
					break;
				case 2:
					processArrivalQueueTwo();
					break;
				case 3:
					processArrivalQueueThree();
					break;
				} // end switch
			}
			else
			{
				switch (nextQ)
				{
				case 1:
					processDepartureQueueOne();
					break;
				case 2:
					processDepartureQueueTwo();
					break;
				case 3:
					processDepartureQueueThree();
					break;
				} // end switch
			} // end else
		} // end while
		// when event is ready to be added, add it.
		int stateOfQueues = findMinimumQueue();
		prospectiveEvent.changeQueues(stateOfQueues);
		events.push(prospectiveEvent);
	}
}

bool Simulation::finalEventReached() const {
	return events.top().getNumber() == 0;
}