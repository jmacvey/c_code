#ifndef _LINKED_ITERATOR_H
#define _LINKED_ITERATOR_H

#include <iterator>
#include "ListNode.h"
#include "LinkedList.h"

template <class ItemType>
class LinkedList;

template <class ItemType>
class LinkedIterator : public std::iterator<std::input_iterator_tag, int>
{
private:
	// ADT associated with iterator
	const LinkedList<ItemType>* containerPtr;
	// Current location in collection
	Node<ItemType>* currentItemPtr;
public:
	LinkedIterator(const LinkedList<ItemType>* someList, Node<ItemType>* nodePtr);
	// dereferencing operator
	const ItemType operator*();
	// prefix incrememnt operator
	LinkedIterator<ItemType> operator++();
	// equality overload operator
	bool operator==(const LinkedIterator<ItemType>& rhs) const;
	//inequality overload operator
	bool operator!=(const LinkedIterator<ItemType>& rhs) const;
};

#include "LinkedIteratorImpl.h"

#endif