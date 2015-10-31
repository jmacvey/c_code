/** IMPLEMENTATION FILE FOR LINKEDQUEUE TEMPLATE CLASS **/
#ifndef _LINKED_QUEUE_IMPL_H
#define _LINKED_QUEUE_IMPL_H

// Default constructor
template<class ItemType>
LinkedQueue<ItemType>::LinkedQueue(): headPtr(nullptr), tailPtr(nullptr), itemCount(0) {
}

// Copy Constructor
template<class ItemType>
LinkedQueue<ItemType>::LinkedQueue(const LinkedQueue<ItemType>& rhs) {
	// copy the itemCount
	itemCount = rhs.itemCount;
	// copy first Node
	headPtr = new Node<ItemType>(rhs.headPtr->getItem());
	Node<ItemType>* oldChainPtr = rhs.headPtr->getNext();
	Node<ItemType>* newChainPtr = new Node<ItemType>(oldChainPtr->getItem());
	headPtr->setNext(newChainPtr);
	oldChainPtr = oldChainPtr->getNext();
	// copy the rest of the nodes
	while (oldChainPtr != nullptr)
	{
		// copy the item in old node to the dynamically allocated new node
		Node<ItemType>* newNode = new Node<ItemType>(oldChainPtr->getItem());
		// point the newChainPtr at the new node
		newChainPtr->setNext(newNode);
		// move the old chain pointer down one node
		oldChainPtr = oldChainPtr->getNext();
		// set the newChainptr to the end of the chain
		newChainPtr = newNode;
		// loop until rest of chain copied
	}
	// set the last pointer in the chain to nullptr
	newChainPtr->setNext(nullptr);
	// set the tail pointer to the last node in chain
	tailPtr = newChainPtr;
}

// copy assignment operator
// HOW IT WORKS:
// Use compiler copy elision to get a working copy of the rhs (i.e. new dynamically allocated LinkedQueue)
// then swap function just swaps the pointers and size of that copy
template <class ItemType>
LinkedQueue<ItemType>& LinkedQueue<ItemType>::operator=(LinkedQueue<ItemType> rhs){
	// deallocate memory associated with lhs queue if needed!
	this->clear();
	// copy all from rhs to lhs
	LinkedQueue<ItemType>::swap(*this, rhs);
	// return the dereferenced object
	return *this;
}

// no-throw swap function
template <class ItemType>
void LinkedQueue<ItemType>::swap(LinkedQueue<ItemType>& lhs, LinkedQueue<ItemType>& rhs) {
	using std::swap;
	swap(lhs.itemCount, rhs.itemCount);
	swap(lhs.headPtr, rhs.headPtr);
	swap(lhs.tailPtr, rhs.tailPtr);
}

// default destructor
template <class ItemType>
LinkedQueue<ItemType>::~LinkedQueue() {
	// just call clear
	clear();
}

// Other functions

template<class ItemType>
bool LinkedQueue<ItemType>::isEmpty() const {
	return itemCount == 0;
}

template<class ItemType>
void LinkedQueue<ItemType>::clear() {
	Node<ItemType>* nextPtr = nullptr;
	Node<ItemType>* loopPtr = headPtr;
	while (loopPtr != nullptr)
	{
		// nextPtr points to next node in chain
		nextPtr = loopPtr->getNext();
		// eliminate the pointer originally pointing to next node
		loopPtr->setNext(nullptr);
		// deallocate memory
		delete loopPtr;
		// set loopPtr to the next node
		loopPtr = nextPtr;
		// loop until finished
	}
	// eliminate final dangling pts for good measure
	headPtr = loopPtr;
	tailPtr = loopPtr;
}

template<class ItemType>
ItemType LinkedQueue<ItemType>::peekFront() const {
	return headPtr->getItem(); 
}

template<class ItemType>
bool LinkedQueue<ItemType>::enqueue(const ItemType& newEntry) {
	// create the new node
	Node<ItemType>* newTail = new Node<ItemType>(newEntry, nullptr);
	// attach it to the tail if list is not empty. if list is empty, then the headPtr is also the tail
	if (tailPtr == nullptr)
	{
		tailPtr = newTail;
		headPtr = tailPtr;
	}
	// if list is not empty, attach the new tailNode to the end of the chain
	// and set the tailPtr to point at the newTail
	else 
	{
		tailPtr->setNext(newTail);
		tailPtr = newTail;
	}
	// add to itemCount
	itemCount++;
	return true;
}

template<class ItemType>
bool LinkedQueue<ItemType>::dequeue() {
	if (itemCount == 0)
	{
		std::cout << "Tried to dequeue from empty queue." << std::endl;
		return false;
	}
	if (headPtr == tailPtr)
	{
		tailPtr = nullptr;
	}
	// point the newHead to the next item in the queue
	Node<ItemType>* newHead = headPtr->getNext();
	// set the dangling pointer in first node to null
	headPtr->setNext(nullptr);
	// deallocate memory
	delete headPtr;
	// set headPtr to newHead
	headPtr = newHead;
	// decrement the itemCount
	itemCount--;
	return true;
}


#endif