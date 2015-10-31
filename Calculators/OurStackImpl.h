#ifndef _OUR_STACK_IMPL_H
#define _OUR_STACK_IMPL_H

#include <vector>

template<class ItemType>
OurStack<ItemType>::OurStack(){
// default constructor
}

template<class ItemType>
bool OurStack<ItemType>::isEmpty() const {
	return myStack.empty();
}

template<class ItemType>
ItemType OurStack<ItemType>::peek() const {
	return myStack.top();
}

template<class ItemType>
bool OurStack<ItemType>::push(const ItemType& newEntry) {
	myStack.push(newEntry);
	return true;
}

template<class ItemType>
bool OurStack<ItemType>::pop() {
	myStack.pop();
	return true;
}
#endif