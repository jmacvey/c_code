
#ifndef NODE_H
#define	NODE_H

template <class ItemType>
class Node {
private:
	ItemType item; // data item
	Node<ItemType>* next; // pointer to next node
	char visitMark; // tells whether a city has been visited before
public:
	Node(); // Default Constructor
	Node(const ItemType& anItem);
	Node(const ItemType& anItem, Node<ItemType>* nextPtr);
	void setItem(const ItemType& theItem);
	void setNext(Node<ItemType>* thePtr);
	ItemType getItem() const;
	Node<ItemType>* getNext() const;
}; // end Node Class

// Inline declaration of Nodes

template<class ItemType>
Node<ItemType>::Node() {
	//Default Constructor
} // end default constructor

template<class ItemType>
Node<ItemType>::Node(const ItemType& anItem) : item(anItem), visitMark('n') {
	// parameterized constructor
}

template<class ItemType>
Node<ItemType>::Node(const ItemType& anItem, Node<ItemType>* nextPtr)
	: item(anItem), next(nextPtr), visitMark('n') {
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

#endif	/* NODE_H */

