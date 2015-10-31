#ifndef _LINKED_QUEUE_H
#define _LINKED_QUEUE_H

#include "QueueInterface.h"
#include "ListNode.h"
#include <iostream>
#include <utility> // std::swap
template <class ItemType>
class LinkedQueue : public QueueInterface<ItemType>
{
private:
	Node<ItemType>* headPtr;
	Node<ItemType>* tailPtr;
	int itemCount;
public:
	LinkedQueue(); // default constructor
	LinkedQueue(const LinkedQueue<ItemType>& rhs); // copy constructor
	LinkedQueue<ItemType>& operator=(LinkedQueue<ItemType> rhs); // assignment operator
	void swap(LinkedQueue<ItemType>& lhs, LinkedQueue<ItemType>& rhs); // no-throw swap function to assist assignment operator
	~LinkedQueue(); // destructor
	bool isEmpty() const;
	bool enqueue(const ItemType& newEntry);
	bool dequeue();
	ItemType peekFront() const;
	void clear();
};

#include "LinkedQueueImpl.h"


#endif
