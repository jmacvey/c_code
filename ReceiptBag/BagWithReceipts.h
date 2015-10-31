#ifndef BAGWITHRECEIPTS_H
#define BAGWITHRECEIPTS_H

#include "BagInterface.h"

template <class ItemType>
class BagWithReceipts: public BagInterface<ItemType>
{
private:
	static const int DEFAULT_CAPACITY = 5; // default capacity of bag
	ItemType* items = new ItemType[DEFAULT_CAPACITY]; //Dynamic Array for items
	bool* receipts = new bool[DEFAULT_CAPACITY]; //Parallel Array for receipts
	int itemCount; // counts number of items currently in the bag
	int maxItems; // maxItems of Bag (allows for dynamic implementation)
	int totalItemsAddedEver;
	void enlargeArraySize(const ItemType& anItem); // enlarges array size if needed
	int getIndexOfItem(const ItemType& anItem) const; // returns index of a single item, if it exists
public:
	BagWithReceipts(); // Default Constructor
	virtual ~BagWithReceipts(); // Destructor
	int add(const ItemType& itemToAdd); // add item to bag & return corresponding integer receipt
	ItemType remove(const int& receiptOfItem); //remove item with specific receipt from bag and return item
	int getCurrentSize() const; // accessor for current size
	void clear(); //clears contents of the array
	bool contains(const ItemType& anEntry) const; //checks if bag contains an item
	bool isEmpty() const; //checks if bag is empty
	vector<ItemType> toVector() const; //copies elements of bag to a vector
	int getFrequencyOf(const ItemType& anItem) const; //checks frequency of bags in an item
}; 
//end class definition
#include "BagWithReceiptsImpl.h"

#endif
