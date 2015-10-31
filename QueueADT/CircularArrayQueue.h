#ifndef _CIRCULAR_ARRAY_QUEUE_H
#define _CIRCULAR_ARRAY_QUEUE_H

#include "QueueInterface.h"

template<class ItemType>
class CircularArrayQueue : public QueueInterface<ItemType> {
private:
	// head of queue
	int headIndex;
	// tail of queue
	int tailIndex;
	// # of items in queue
	int itemCount;
	// initial default capacity of array
	const int DEFAULT_CAPACITY = 10;
	// max_items subject to change
	int MAX_ITEMS;
	// Queue of items
	ItemType* queue;
	// utility function to resize the array
	void resizeArray();
public:
	CircularArrayQueue(); // default constructor
	CircularArrayQueue(const CircularArrayQueue<ItemType>& rhs); // copy constructor
	CircularArrayQueue<ItemType>& operator=(CircularArrayQueue<ItemType> rhs); // assignment operator
	void swap(CircularArrayQueue<ItemType>& lhs, CircularArrayQueue<ItemType>& rhs); // no throw swap function
	~CircularArrayQueue(); // default destructor
	bool isEmpty() const;
	void clear();
	bool enqueue(const ItemType& newEntry);
	bool dequeue(); 
	ItemType peekFront() const;
	void displayQueue() const;
};

#include "CircularArrayQueueImpl.h"

#endif