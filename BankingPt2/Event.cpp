/* Implementation file for Event.h */

#include "Event.h"

Event::Event() : type(DEPARTURE), time(0), length(0), number(0), queueNumber(0) {
	// default constructor
}

Event::Event(EventType pType, Time pTime, Time pLength, int pNumber, int qNumber) :
type(pType), time(pTime), length(pLength), number(pNumber), queueNumber(qNumber)
{
	// end param constructor
}

/** ACCESSOR METHODS */
EventType Event::getEventType() const {
	return type;
}

Time Event::getTime() const {
	return time;
}

Time Event::getLength() const {
	return length;
}

int Event::getNumber() const {
	return number;
}

int Event::getQueueNumber() const {
	return queueNumber;
}

/** MUTATOR METHODS */

void Event::changeEventType(const EventType& newType) {
	type = newType;
}

void Event::changeLength(const Time& newLength) {
	length = newLength;
}

void Event::changeNumber(int newNumber) {
	number = newNumber;
}

void Event::changeTime(const Time& newTime) {
	time = newTime;
}

void Event::changeQueues(int newQNumber) {
	queueNumber = newQNumber;
}

/** OPERATOR METHODS */

bool Event::operator<(const Event& rhs) const {
	return time < rhs.time;
}

bool Event::operator<=(const Event& rhs) const {
	return time <= rhs.time;
}

bool Event::operator>(const Event& rhs) const {
	return time > rhs.time;
}

bool Event::operator>=(const Event& rhs) const {
	return time >= rhs.time;
}

bool Event::operator==(const Event& rhs) const {
	return time == rhs.time;
}

bool Event::operator!=(const Event& rhs) const {
	return time != rhs.time;
}