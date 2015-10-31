#ifndef _LIST_NODE_H
#define	_LIST_NODE_H

template <class ItemType>
class Node {
private:
	ItemType item; // data item
	Node<ItemType>* next; // pointer to next node
public:
	Node(); // Default Constructor
	Node(const ItemType& anItem);
	Node(const ItemType& anItem, Node<ItemType>* nextPtr);
	void setItem(const ItemType& theItem);
	void setNext(Node<ItemType>* thePtr);
	ItemType getItem() const;
	Node<ItemType>* getNext() const;
}; // end Node Class

#include "ListNodeImpl.h"
#endif	/* NODE_H */
