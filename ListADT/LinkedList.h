#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

#include "ListInterface.h"
#include "ListNode.h"
#include "exceplib.h"
#include <iterator>
#include <cassert>
#include "LinkedIterator.h"

template<class ItemType>
class LinkedList : public ListInterface < ItemType >
{
private:
	Node<ItemType>* listHead; // headPtr to represent head ot list
	int listLength; // length of the list
	Node<ItemType>* getNodeAtPos(const int& position) const; // retrieves node at specific position
	LinkedIterator<ItemType> begin() const;
	LinkedIterator<ItemType> end() const;
public:
	/* Default constructor */
	LinkedList();
	/* Copy Constructor */
	LinkedList(const LinkedList<ItemType>& listToCopy);
	/* Copy assignment operator */
	LinkedList<ItemType>& operator=(LinkedList<ItemType> listToCopy); // note pass by value to utilize copy elision
	/* no-throw swap function to assist copy assignment operator */
	void swap(LinkedList<ItemType>& arrayToCopyTo, LinkedList<ItemType>& arrayToCopy);
	/* Destructor */
	~LinkedList();
	/* checks to see if list is empty */
	bool isEmpty() const;
	/* gets the current length of the list */
	int getLength() const;
	/* inserts a new item in the i-th position of the list */
	bool insert(const int& newPosition, const ItemType& newEntry);
	/* removes an item from the list */
	bool remove(const int& position);
	/* removes all items from the list */
	void clear();
	/* returns the i-th item in the list */
	ItemType getEntry(const int& position) const throw(PrecondViolatedExcep);
	/* sets an item in the list */
	void setEntry(const int& position, const ItemType& newEntry) throw(PrecondViolatedExcep);
	/* gets the number of entries in a list */
	int getListLength() const;
	/* display the list */
	void displayList() const;

};

#include "LinkedListImpl.h"

#endif
