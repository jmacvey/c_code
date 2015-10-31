/* DISC LIST HEADER FILE */

#ifndef _DISC_LIST_H
#define _DISC_LIST_H

#include "LinkedSortedList.h"

class Disc; // forward declaration of Disc
class Track; // forward declaration of track

class DiscList {
private:
	// pointer to a sorted linked list composed of disc pointers
	LinkedSortedList<Disc*>* discListPtr;
	
public:
	// default constructor
	DiscList(); 
	// copy constructor
	DiscList(const DiscList& copyList); 
	// copy assignment operator (uses copy elision)
	DiscList& operator=(DiscList copyList); 
	// Destructor
	~DiscList();
	// checks if list is empty
	bool isEmpty() const;
	// checks number of discs
	int numberOfDiscs() const;
	// inserts a disc
	void insertDisc(Disc* discToInsert);
	// removes a disc
	void removeDisc(Disc* discToRemove);
	// finds which position a disc is located in the list
	int findDiscPosition(std::string discTitle) const;
	// retrieves a pointer pointing to n-th disc in the list
	Disc* retrieveDisc(int position) const;
	// print list
	void printList() const;

};

#endif