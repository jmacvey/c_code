#ifndef _LINKED_SORTED_LIST_H
#define _LINKED_SORTED_LIST_H

#include "ListNode.h"
#include "SortedListInterface.h"
#include "exceplib.h"
#include <cassert>

template <class ItemType>
class LinkedSortedList : public SortedListInterface<ItemType>
{
private:
	Node<ItemType>* headPtr;
	int itemCount;

	// Locates the node that is before the node that should or does
	// contain the given entry.
	// @param anEntry The entry to find.
	// @return Either a pointer to the node before the node that contains
	// or should contain the given entry, or nullptr if no prior node exists.
	Node<ItemType>* getNodeBefore(const ItemType& anEntry) const;
	// Locates the node at a given position within the chain.
	Node<ItemType>* getNodeAtPos(const int& position) const;
	// Returns a pointer to a copy of the chain to which origChainPtr points.
	Node<ItemType>* copyChain(Node<ItemType>* origChainPtr);
public:
	LinkedSortedList(); // default constructor
	LinkedSortedList(const LinkedSortedList<ItemType>& copyList); // copy constructor
	LinkedSortedList<ItemType>& operator=(LinkedSortedList<ItemType> copyList); // class assignment operator
	virtual ~LinkedSortedList(); // destructor
	/* no-throw swap function to assist copy assignment operator */
	void swap(LinkedSortedList<ItemType>& listToCopyTo, LinkedSortedList<ItemType>& listToCopy);
	void insertSorted(const ItemType& newEntry);
	bool removeSorted(const ItemType& anEntry);
	int getPosition(const ItemType& newEntry) const;
	// The following methods are the same as given in ListInterface:
	bool isEmpty() const;
	int getLength() const;
	bool insert(int newPosition, const ItemType& newEntry);
	bool remove(int position);
	void clear();
	ItemType getEntry(int position) const throw (PrecondViolatedExcep);
}; // end LinkedSortedList

#include "LinkedSortedListImpl.h"
#endif
