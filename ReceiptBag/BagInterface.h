#ifndef BAGINTERFACE_H
#define BAGINTERFACE_H
using namespace std;
#include <vector>

template <class ItemType>
class BagInterface {
public:
	/**Adds an item to the bag
	@param itemToAdd is the item to be added to the bag
	@post item is added and receipt is returned; itemCount increased by 1.*/
	virtual int add(const ItemType& itemToAdd) = 0;
	/*Removes an item from the bag
	@post item is removed and returned, itemCount reduced by 1.*/
	virtual ItemType remove(const int& receiptOfItem) = 0;
	/**Tests whether this bag contains a given entry.
	@param anEntry The entry to locate.
	@return True if object is in bag.  False if not.*/
	virtual bool contains(const ItemType& anEntry) const = 0;
	/*Clears all items from the
	@post all items removed from the bag*/
	virtual void clear() = 0;
	/*Accessor: gets current size of bag
	@post returns current size from the bag*/
	virtual int getCurrentSize() const = 0;
	/*Checks to see if bag is empty
	@post returns 1 if yes, 0 if not.*/
	virtual bool isEmpty() const = 0;
	/**Counts number of times a given entry occurs in the bag
	@param the item to be counted
	@post no change to object, returns integer value for times*/
	virtual int getFrequencyOf(const ItemType&) const = 0;
	/**Returns a vector containing all items in a given bag
	@post no change to object*/
	virtual vector<ItemType> toVector() const = 0;
}; // end abstract base class

#endif
