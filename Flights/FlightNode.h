#ifndef _FLIGHT_NODE_H
#define _FLIGHT_NODE_H

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
	char getVisitMark() const;
	void setVisitMark();
	bool isVisited() const;
	void clearVisitMark();
}; // end Node Class

// Inline declaration of Nodes

template<class ItemType>
void Node<ItemType>::clearVisitMark() {
	visitMark = 'n';
}

template<class ItemType>
bool Node<ItemType>::isVisited() const {
	return visitMark == 'V';
}

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

template <class ItemType>
char Node<ItemType>::getVisitMark() const {
	return visitMark;
} // end getVisitMark

template <class ItemType>
void Node<ItemType>::setVisitMark() {
	visitMark = 'V';
}

#endif /* _FLIGHT_NODE_H */