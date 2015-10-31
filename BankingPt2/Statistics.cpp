/** Implementation file for Statistics.h */

#include "Statistics.h"


Statistics::Statistics() : countOne(0), countTwo(0), countThree(0),
	waitTimeOne(0), waitTimeTwo(0), waitTimeThree(0),
		bankLineOne(), bankLineTwo(), bankLineThree() {
	// default constructor
}

void Statistics::addEvent(const Event& newEvent) {
	using std::cout; using std::endl;
	// if the event is an arrival
	if (newEvent.getEventType() == ARRIVAL)
	{
		if (newEvent.getQueueNumber() == 1)
		{
			// increment the count
			countOne++;
			// push the newEvent onto the bankLine
			bankLineOne.push(newEvent);
		}
		else if (newEvent.getQueueNumber() == 2)
		{
			countTwo++;
			bankLineTwo.push(newEvent);
		}
		else
		{
			countThree++;
			bankLineThree.push(newEvent);
		}
	}
	// else if the event is a departure
	else {
		// calculate the wait time for the customer and add to total waitTime
		if (newEvent.getQueueNumber() == 1)
		{
			cout << "waited: " << newEvent.getTime()
				- (bankLineOne.front().getTime()
				+ bankLineOne.front().getLength()) << endl;
			waitTimeOne +=
				newEvent.getTime()
				- (bankLineOne.front().getTime()
				+ bankLineOne.front().getLength());
			// pop the event from the bankline
			bankLineOne.pop();
		}
		else if (newEvent.getQueueNumber() == 2)
		{
			cout << "waited: " << newEvent.getTime()
				- (bankLineTwo.front().getTime()
				+ bankLineTwo.front().getLength()) << endl;
			waitTimeTwo +=
				newEvent.getTime()
				- (bankLineTwo.front().getTime()
				+ bankLineTwo.front().getLength());
			bankLineTwo.pop();
		}
		else
		{
			cout << "waited: " << newEvent.getTime()
				- (bankLineThree.front().getTime()
				+ bankLineThree.front().getLength()) << endl;
			waitTimeThree +=
				newEvent.getTime()
				- (bankLineThree.front().getTime()
				+ bankLineThree.front().getLength());
			bankLineThree.pop();
		}
	}
}

void Statistics::reportStats() {
	using std::cout; using std::endl;
	// Output final cumulative stats
	cout << "Final Statistics: " << endl << "\t";
	cout << "Total number of people processed: " << countOne + countTwo + countThree << endl << "\t";
	cout << "Total wait time: " << waitTimeOne + waitTimeTwo + waitTimeThree << endl << "\t";
	cout << "Average amount of time spent waiting: " <<
		static_cast<double>(waitTimeOne + waitTimeTwo + waitTimeThree) / (countOne + countTwo + countThree) << endl << endl;
	// output Stats for teller 1
	cout << "Totals for Teller 1: " << endl << "\t";
	cout << "People Processed: " << countOne << endl << "\t";
	cout << "Wait time: " << waitTimeOne << endl << "\t";
	cout << "Average wait time: " << waitTimeOne / static_cast<double>(countOne) << endl << endl;
	// output Stats for teller 2
	cout << "Totals for Teller 2: " << endl << "\t";
	cout << "People Processed: " << countTwo << endl << "\t";
	cout << "Wait time: " << waitTimeTwo << endl << "\t";
	cout << "Average wait time: " << waitTimeTwo / static_cast<double>(countTwo) << endl << endl;
	// output stats for teller 3
	cout << "Totals for Teller 3: " << endl << "\t";
	cout << "People Processed: " << countThree << endl << "\t";
	cout << "Wait time: " << waitTimeThree << endl << "\t";
	cout << "Average wait time: " << waitTimeThree / static_cast<double>(countThree) << endl << endl;
}

int Statistics::getWaitTimeOne() const {
	return waitTimeOne;
}

int Statistics::getWaitTimeTwo() const {
	return waitTimeTwo;
}

int Statistics::getWaitTimeThree() const {
	return waitTimeThree;
}