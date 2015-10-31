#ifndef _LIST_NODE_IMPL_H
#define _LIST_NODE_IMPL_H

template<class ItemType>
Node<ItemType>::Node() {
	//Default Constructor
} // end default constructor

template<class ItemType>
Node<ItemType>::Node(const ItemType& anItem) : item(anItem) {
	// parameterized constructor
}

template<class ItemType>
Node<ItemType>::Node(const ItemType& anItem, Node<ItemType>* nextPtr)
	: item(anItem), next(nextPtr) {
	//parameterized constructor
}

template<class ItemType>
void Node<ItemType>::setItem(const ItemType& theItem)
{
	item = theItem;
} //end setItem

template<class ItemType>
void Node<ItemType>::setNext(Node<ItemType>* thePtr)
{
	next = thePtr;
} // end setNext

template<class ItemType>
ItemType Node<ItemType>::getItem() const
{
	return item;
} // end getItem

template<class ItemType>
Node<ItemType>* Node<ItemType>::getNext() const
{
	return next;
} // end getNext

#endif
