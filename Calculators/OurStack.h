#ifndef _OUR_STACK_H
#define _OUR_STACK_H

#include "StackInterface.h"

template<class ItemType>
class OurStack : public StackInterface < ItemType > {
private:
	std::stack<ItemType> myStack; // private stack for the class ^.^ how pointless.
public:
	OurStack(); // default constructor
	bool isEmpty() const;
	bool push(const ItemType& newEntry);
	bool pop();
	ItemType peek() const;
};

#include "OurStackImpl.h"

#endif
