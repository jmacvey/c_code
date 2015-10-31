#ifndef _LINKED_LIST_IMPL_H
#define _LINKED_LIST_IMPL_H

/* Gets the listLength in a list */
template<class ItemType>
int LinkedList<ItemType>::getListLength() const {
	return listLength;
}
/* Default Constructor */
template<class ItemType>
LinkedList<ItemType>::LinkedList() : listLength(0), listHead(nullptr){
} // end default constructor

/* Copy Constructor */
template<class ItemType>
LinkedList<ItemType>::LinkedList(const LinkedList<ItemType>& listToCopy) : listLength(listToCopy.listLength)
{
	// if the head of listToCopy is nullptr, we're done.
	if (listToCopy.listHead == nullptr)
	{
		listHead = nullptr;
	}
	else {
		// copy the first node
		Node<ItemType>* newChainPtr = new Node<ItemType>(listToCopy.listHead->getItem());
		listHead = newChainPtr;
		// move to next part of chain
		Node<ItemType>* oldChainPtr = listToCopy.listHead->getNext();
		while (oldChainPtr != nullptr)
		{
			// create new node
			Node<ItemType>* newNode = new Node<ItemType>(oldChainPtr->getItem());
			// attach node to end of chain
			newChainPtr->setNext(newNode);
			// move down the link
			newChainPtr = newChainPtr->getNext();
			// move the oldChainPtr down its chain
			oldChainPtr = oldChainPtr->getNext();
			// eliminate dangling pointer
			newNode = nullptr;
		}
		// terminate the chain
		newChainPtr->setNext(nullptr);
		// eliminate dangling ptr
		newChainPtr = nullptr;
	} // end else
} // end copy constructor

/* Copy assignment operator */
template<class ItemType>
LinkedList<ItemType>& LinkedList<ItemType>::operator=(LinkedList<ItemType> listToCopy) // note pass by value for copy elision
{
	swap(*this, listToCopy);
	return *this;
} // end copy assignment operator

/* no-throw swap function to assist copy assignment operator */
template<class ItemType>
void LinkedList<ItemType>::swap(LinkedList<ItemType>& arrayToCopyTo, LinkedList<ItemType>& arrayToCopy){
	using std::swap;
	swap(arrayToCopyTo.listLength, arrayToCopy.listLength);
	swap(arrayToCopyTo.listHead, arrayToCopy.listHead);
} // end swap

/* Destructor */
template<class ItemType>
LinkedList<ItemType>::~LinkedList() {
	// if the headptr is nullptr, we're done
	while (listHead != nullptr)
	{
		Node<ItemType>* temp = listHead->getNext(); // save next link in chain
		listHead->setNext(nullptr); // eliminate dangling pointer
		delete listHead; // delete contents pointed to by listHead
		listHead = temp; // move to next link in chain
		temp = nullptr; // eliminate dangling pointer
	}
}

/* Checks to see if array is empty */
template<class ItemType>
bool LinkedList<ItemType>::isEmpty() const {
	return listHead == nullptr;
} // end isEmpty

/* Returns the length of the list */
template<class ItemType>
int LinkedList<ItemType>::getLength() const {
	return listLength;
} // end getLength

/*inserts a new item in the i-th position of the list */
template<class ItemType>
bool LinkedList<ItemType>::insert(const int& newPosition, const ItemType& newEntry){
	// check case for if inserting at beginning of chain:
	if (newPosition == 1)
	{	// create new node
		Node<ItemType>* newNode = new Node<ItemType>(newEntry, listHead);
		// make that Node the new head in the chain
		listHead = newNode;
	}
	else {
		// retrieves pointer pointing at position
		Node<ItemType>* ptrToPlaceToInsert = getNodeAtPos(newPosition - 1);
		// set the insertion node to point to where the previous node was pointing
		Node<ItemType>* nodeToInsert = new Node<ItemType>(newEntry, ptrToPlaceToInsert->getNext());
		// set the previous node to point to the node to insert
		ptrToPlaceToInsert->setNext(nodeToInsert);
		// eliminate dangling pointers
		ptrToPlaceToInsert = nodeToInsert = nullptr;
	}
	listLength++; // increment number of items
	return true; // return boolean value
} // end insert


/** Gets a node at the current position
	Note: Pointer is returned. All member functions using this
	private function are responsible for eliminating the ptr.
	*/
template <class ItemType>
Node<ItemType>* LinkedList<ItemType>::getNodeAtPos(const int& position) const {

	assert((position >= 1) && (position <= listLength));  // assert we can get a node at the current position
	Node<ItemType>* curPtr = listHead; // begin at beginning of list (pointing at 1st position)
	for (int ptrPosition = 1; ptrPosition < position; ptrPosition++)
	{
		curPtr = curPtr->getNext();
	}
	return curPtr; // returns the node at the current position 
}

/* gets item at a position in the list */
template<class ItemType>
ItemType LinkedList<ItemType>::getEntry(const int& position) const
throw(PrecondViolatedExcep) {
	if (!(position <= listLength && position >= 1))
	{
		throw PrecondViolatedExcep("getEntry() called on emptyList or invalid position. \n");
	}
	else {
		// get the node in the list
		Node<ItemType>* posPtr = getNodeAtPos(position);
		ItemType myItem = posPtr->getItem();
		posPtr = nullptr;
		return myItem;
	}
} // end getItem

template <class ItemType>
bool LinkedList<ItemType>::remove(const int& position)
{
	if (!(position >= 1 && position <= listLength))
	{
		return false;
	}
	else if (position == 1)
	{
		Node<ItemType>* temp = listHead->getNext();
		listHead->setNext(nullptr);
		delete listHead;
		listHead = temp;
	}
	else 
	{
		// get the node at the previous position
		Node<ItemType>* prevNode = getNodeAtPos(position - 1);
		Node<ItemType>* nodeToRemove = prevNode->getNext(); // get next ptr
		prevNode->setNext(nodeToRemove->getNext()); // point to item to node pointed to by the item to be deleted
		nodeToRemove->setNext(nullptr); // eliminate dangling pointer
		delete nodeToRemove; // deallocate memory of that node
		nodeToRemove = nullptr; // remove nullptr
	}
	listLength--;
	return true; 
} // end remove 

template<class ItemType>
void LinkedList<ItemType>::clear() {
	while (listHead != nullptr)
	{
		Node<ItemType>* temp = listHead->getNext(); // save next link in chain
		listHead->setNext(nullptr); // eliminate dangling pointer
		delete listHead; // delete contents pointed to by listHead
		listHead = temp; // move to next link in chain
	}
} // end clear

template<class ItemType>
void LinkedList<ItemType>::setEntry(const int& position, const ItemType& newEntry)
throw(PrecondViolatedExcep) {
	if (!(position >= 1 && position <= listLength))
	{
		throw PrecondViolatedExcep("attempted to remove from an empty list or invalid position.");
	}
	else 
	{
		Node<ItemType>* posPtr = getNodeAtPos(position);
		posPtr->setItem(newEntry);
	}
} // end setEntry

template <class ItemType>
void LinkedList<ItemType>::displayList() const {
	LinkedIterator<ItemType> currentIterator = this->begin();
	
	LinkedIterator<ItemType> endIterator = this->end();
	while (currentIterator != endIterator)
	{
		std::cout << *currentIterator << " ";
		++currentIterator;
	}
}

template <class ItemType>
LinkedIterator<ItemType> LinkedList<ItemType>::begin() const {
	LinkedIterator<ItemType> startIterator(this, listHead);
	return startIterator;
}

template <class ItemType>
LinkedIterator<ItemType> LinkedList<ItemType>::end() const
{
	LinkedIterator<ItemType> endIterator(this, nullptr);
	return endIterator;
}

#endif