#ifndef _ARRAY_LIST_H
#define _ARRAY_LIST_H


#include "ListInterface.h"
#include "exceplib.h"


template<class ItemType>
class ArrayList : public ListInterface < ItemType >
{
private:
	static const int DEFAULT_CAPACITY = 50;
	ItemType* itemList; // dynamically allocated list w/ pointer!
	int listLength; // length of the list
	int maxItems; // max items allowed in the array before new dynamic allocation takes place
public:
	/* Default constructor */
	ArrayList();
	/* Copy Constructor */
	ArrayList(const ArrayList<ItemType>& listToCopy);
	/* Copy assignment operator */
	ArrayList<ItemType>& operator=(ArrayList<ItemType> listToCopy); // note pass by value to utilize copy elision
	/* no-throw swap function to assist copy assignment operator */
	void swap(ArrayList<ItemType>& arrayToCopyTo, ArrayList<ItemType>& arrayToCopy);
	/* Destructor */
	~ArrayList();
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
};

#include "ArrayListImpl.h"

#endif
