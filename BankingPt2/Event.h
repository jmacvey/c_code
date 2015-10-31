#ifndef _EVENT_H
#define _EVENT_H

#include "EventType.h"
#include "Time.h"

class Event
{
private:
	EventType type;
	// arrival or departure time
	Time time; 
	// transaction time
	Time length;
	int number;
	// queue number
	int queueNumber;
public:
	Event(); // default constructor
	Event(EventType pType, Time pTime, Time pLength, int pNumber, int qNumber);
	// mutator and accessor methods
	EventType getEventType() const;
	Time getTime() const;
	Time getLength() const;
	int getNumber() const;
	int getQueueNumber() const;
	void changeEventType(const EventType& newType);
	void changeTime(const Time& newTime);
	void changeLength(const Time& newLength);
	void changeNumber(int newNumber);
	void changeQueues(int newQNumber);
	// all operators relate events based on time
	bool operator==(const Event& rhs) const;
	bool operator<(const Event& rhs) const;
	bool operator>(const Event& rhs) const;
	bool operator!=(const Event& rhs) const;
	bool operator>=(const Event& rhs) const;
	bool operator<=(const Event& rhs) const;
};

#endif
