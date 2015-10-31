/* IMPLEMENTATION FILE FOR DISC LIST */

#include "DiscList.h"
#include "Disc.h"
#include <iostream>

/* Default Constructor */
DiscList::DiscList() {
	// creates empty disc list and sets discListPtr to address
	discListPtr = new LinkedSortedList<Disc*>();
}

/* Copy Constructor */
DiscList::DiscList(const DiscList& copyList) : discListPtr(copyList.discListPtr) {
	// invoke linkedSortedLists's copy constructor operator
}

/* Copy Assignment operator */
DiscList& DiscList::operator=(DiscList copyList) {
	discListPtr = copyList.discListPtr;
	return *this;
}

/* Destructor */
DiscList::~DiscList()
{
	std::cout << "deallocating memory for disc objects... " << std::endl;
	// need to deallocate memory associated with individual discs
	int totalDiscs = discListPtr->getLength();
	for (int i = 1; i <= totalDiscs; i++)
	{
		// delete the memory allocated to the object in the node
		// *effectively calls disc destructors*
		// *which effectively calls track destructors
		delete discListPtr->getEntry(1);
	}
	// delete the discListPtr, which calls the LinkedSortedList destructor
	delete discListPtr;
	// dangling ptr is effectively destroyed as object's lifetime ends
}

/* checks to see if list is empty */
bool DiscList::isEmpty() const
{
	return discListPtr->isEmpty();
}

/* checks to see number of items in the list */
int DiscList::numberOfDiscs() const {
	return discListPtr->getLength();
}

/* inserts a disc in the discList */
void DiscList::insertDisc(Disc* discToInsert) {
	// if the list is empty, insert at position 1
	if (discListPtr->isEmpty())
	{
		discListPtr->insert(1, discToInsert);
	}
	else
	{
		int discPos = 1;
		while (discPos <= discListPtr->getLength() && discListPtr->getEntry(discPos)->isLessThanOrEqualTo(discToInsert))
		{
			discPos++;
		}
		discListPtr->insert(discPos, discToInsert);
	}
}

/* removes a disc from the discList*/
void DiscList::removeDisc(Disc* discToRemove) {
	// delete the disc
	// *note: because the disc contains track pointers, those pointers
	// must deallocate their memory.  Special care is taken to ensure
	// this is done in the disc destructor
	// remove the node associated with that disc
	// this effectively eliminates all pointers that had been pointing to deleted tracks
	// get the position
	int discPos = findDiscPosition(discToRemove->getTitle());
	delete discToRemove;
	discListPtr->remove(discPos);
}

/* finds disc position in the list */
int DiscList::findDiscPosition(std::string discTitle) const
{
	int discPos = 1;
	std::string currentTitle = discListPtr->getEntry(discPos)->getTitle();
	while (currentTitle != discTitle && discPos + 1 <= discListPtr->getLength())
	{
		discPos++;
		currentTitle = discListPtr->getEntry(discPos)->getTitle();
	}
	// if disc position is greater than discLength, we know the item is not in the list
	if (discPos + 1 > discListPtr->getLength() && currentTitle != discTitle)
	{
		return -1;
	}
	else return discPos;
}

Disc* DiscList::retrieveDisc(int position) const {
	// returns disc address in the list (non-static r-value)
	return discListPtr->getEntry(position);
}

void DiscList::printList() const {
	for (int i = 1; i <= discListPtr->getLength(); i++)
	{
		std::cout << "Disc No. " << i << ": ";
		std::cout << discListPtr->getEntry(i)->getTitle() << " " << std::endl;
	}
}