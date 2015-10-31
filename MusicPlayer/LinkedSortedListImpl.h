/* LINKED_SORTED_LIST_IMPLEMENTATION */

#ifndef _LINKED_SORTED_LIST_IMPL_H
#define _LINKED_SORTED_LIST_IMPL_H

/* Default Constructor */
template <class ItemType>
LinkedSortedList<ItemType>::LinkedSortedList() : itemCount(0), headPtr(nullptr) {
	///
} // end default constructor

/* Copy Constructor */
template<class ItemType>
LinkedSortedList<ItemType>::LinkedSortedList(const LinkedSortedList<ItemType>& copyList) : itemCount(copyList.itemCount)
{
	// if the head of copyList is nullptr, we're done.
	if (copyList.headPtr == nullptr)
	{
		headPtr = nullptr;
	}
	else {
		// copy the first node
		Node<ItemType>* newChainPtr = new Node<ItemType>(copyList.headPtr->getItem());
		headPtr = newChainPtr;
		// move to next part of chain
		Node<ItemType>* oldChainPtr = copyList.headPtr->getNext();
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
LinkedSortedList<ItemType>& LinkedSortedList<ItemType>::operator=(LinkedSortedList<ItemType> copyList) // note pass by value for copy elision
{
	swap(*this, copyList);
	return *this;
} // end copy assignment operator

/* no-throw swap function to assist copy assignment operator */
template<class ItemType>
void LinkedSortedList<ItemType>::swap(LinkedSortedList<ItemType>& listToCopyTo, LinkedSortedList<ItemType>& listToCopy){
	using std::swap;
	swap(listToCopyTo.itemCount, listToCopy.itemCount);
	swap(listToCopyTo.headPtr, listToCopy.headPtr);
} // end swap

/* destructor */
template <class ItemType>
LinkedSortedList<ItemType>::~LinkedSortedList() {
	while (headPtr != nullptr)
	{
		Node<ItemType>* temp = headPtr->getNext();
		headPtr->setNext(nullptr); // eliminate dangling pointer
		delete headPtr; // delete node 
		headPtr = temp; // remove temp
		temp = nullptr; // eliminate dangling pointer
	}
}
//// PRIVATE METHOD IMPLEMENTATIONS ////

/** Gets a node at the current position
Note: Pointer is returned. All member functions using this
private function are responsible for eliminating the ptr.
*/
template <class ItemType>
Node<ItemType>* LinkedSortedList<ItemType>::getNodeAtPos(const int& position) const {
	assert((position >= 1) && (position <= itemCount));  // assert we can get a node at the current position
	Node<ItemType>* curPtr = headPtr; // begin at beginning of list (pointing at 1st position)
	for (int ptrPosition = 1; ptrPosition < position; ptrPosition++)
	{
		curPtr = curPtr->getNext();
	}
	return curPtr; // returns the node at the current position 
}

/* returns a copy of the list remaining from the origChainPtr position
   function operates recursively */
template <class ItemType>
Node<ItemType>* LinkedSortedList<ItemType>::copyChain(Node<ItemType>* origChainPtr) {
	Node<ItemType>* copiedChainPtr;
	if (origChainPtr == nullptr)
	{
		copiedChainPtr = nullptr;
		itemCount = 0;
	}
	else
	{
		// copy the first element in the list
		copiedChainPtr = new Node<ItemType>(origChainPtr->getItem());
		// recursively copy the rest of the list
		copiedChainPtr->setNext(copyChain(origChainPtr->getNext()));
		// add 1 to the itemCount
		itemCount++;
	}
	return copiedChainPtr;
} // end copyChain

// Locates the node that is before the node that should or does
// contain the given entry.
// @param anEntry The entry to find.
// @return Either a pointer to the node before the node that contains
// or should contain the given entry, or nullptr if no prior node exists.
template <class ItemType>
Node<ItemType>* LinkedSortedList<ItemType>::getNodeBefore(const ItemType& anEntry) const {
	Node<ItemType>* curPointer = headPtr;
	Node<ItemType>* prevPointer = nullptr;
	while (curPointer != nullptr && anEntry > curPointer->getItem())
	{
		// if the item is of equal or greater value, then that's the node the item belongs to
		// messing up order of list
		prevPointer = curPointer;
		curPointer = curPointer->getNext();
	} // end while
	return prevPointer;
}

//// END PRIVATE METHODS ////

//// BEGIN SORT-SPECIFIC METHODS ////

/* inserts an item in its proper place in the list */
template<class ItemType>
void LinkedSortedList<ItemType>::insertSorted(const ItemType& newEntry) {
	// get the node before the new entry
	Node<ItemType>* prevNode = getNodeBefore(newEntry);
	// if the  list is empty or the previous node is nullptr, we can insert the node at the beginning.
	if (isEmpty() || prevNode == nullptr)
	{
		Node<ItemType>* newNode = new Node<ItemType>(newEntry, headPtr);
		headPtr = newNode;
	} // end if 
	else
	{
		// create the new node to point to where the previous node is pointing
		Node<ItemType>* newNode = new Node<ItemType>(newEntry, prevNode->getNext());
		// make the previous node point to the new node
		prevNode->setNext(newNode);
	} // end else
	itemCount++; // add one to the itemCount
}

template<class ItemType>
bool LinkedSortedList<ItemType>::removeSorted(const ItemType& anEntry) {
	// assumes the item is in the list
	// if entry is at the head of the list
	// remove the item and make headPtr point to next
	if (anEntry == headPtr->getItem())
	{
		Node<ItemType>* temp = headPtr->getNext();
		headPtr->setNext(nullptr); // eliminate dangling pointer
		delete headPtr; // deallocate memory
		headPtr = temp; // set headPtr to the remaining temp
	}
	else
	{
		// get pointer to node previous to node containing the item
		Node<ItemType>* prevPtr = getNodeBefore(anEntry);
		// get pointer to node containing the item
		Node<ItemType>* aftrPtr = prevPtr->getNext();
		if (aftrPtr->getNext() != nullptr)
		{
			Node<ItemType>* temp = aftrPtr->getNext();
			aftrPtr->setNext(nullptr); // eliminate dangling pointer
			delete aftrPtr; // deallocate memory and eliminate dangling pointer
			aftrPtr = nullptr;
			// make prevPtr point to the new node
			prevPtr->setNext(temp);
		}
		else
		{
			delete aftrPtr;
			aftrPtr = nullptr;
			prevPtr->setNext(nullptr);
		}
	}
	itemCount--; // decrement itemCount
	return true;
}

/* returns position of an entry in the list */
template<class ItemType>
int LinkedSortedList<ItemType>::getPosition(const ItemType& newEntry) const
{
	// if list is empty; it's trivial case; position would exist at position 1
	if (isEmpty())
	{
		return -1;
	}
	// initialize position
	int pos = 1;
	Node<ItemType>* loopPtr = headPtr;
	// if the item isn't equal or the list is not exhausted
	// increment potential position & traverse down the list
	while (loopPtr != nullptr && loopPtr->getItem() != newEntry)
	{
		pos++;
		loopPtr = loopPtr->getNext();
	}
	// if the list contains the entry
	// return its position
	if (loopPtr->getItem() == newEntry)
	{
		return pos;
	}
	// else the item does not exist in the list
	// find where it would exist if it did:
	// reinitialize loopVars
	loopPtr = headPtr;
	pos = 1;
	while (loopPtr != nullptr && newEntry > loopPtr->getItem())
	{
		pos++;
		loopPtr = loopPtr->getNext();
	}
	// return the negative of position
	return -pos;
}


//// BEGIN INTERFACE METHODS ////

/* checks to see if list is empty */
template <class ItemType>
bool LinkedSortedList<ItemType>::isEmpty() const {
	return itemCount == 0;
}

/* returns current list length */
template <class ItemType>
int LinkedSortedList<ItemType>::getLength() const {
	return itemCount;
}

/* returns item stored at specified position in list */
template <class ItemType>
ItemType LinkedSortedList<ItemType>::getEntry(int position) const throw(PrecondViolatedExcep){
	if (position < 1 || position > itemCount)
	{
		throw PrecondViolatedExcep("getEntry() called on emptyList or invalid position. \n");
	}
	else
	{
		Node<ItemType>* posPtr = getNodeAtPos(position);
		ItemType returnItem = posPtr->getItem();
		posPtr = nullptr;
		return returnItem;
	}
}

/* clears the list */
template <class ItemType>
void LinkedSortedList<ItemType>::clear() {
	while (headPtr != nullptr)
	{
		Node<ItemType>* temp = headPtr->getNext();
		headPtr->setNext(nullptr);
		delete headPtr;
		headPtr = temp;
	}
	itemCount = 0;
}

template <class ItemType>
bool LinkedSortedList<ItemType>::remove(int position) {
	if (!(position >= 1 && position <= itemCount))
	{
		return false;
	}
	else if (position == 1)
	{
		Node<ItemType>* temp = headPtr->getNext();
		headPtr->setNext(nullptr);
		delete headPtr;
		headPtr = temp;
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
	itemCount--;
	return true;
} // end remove 


template<class ItemType>
bool LinkedSortedList<ItemType>::insert(int newPosition, const ItemType& newEntry){
	// check case for if inserting at beginning of chain:
	if (newPosition == 1)
	{	// create new node
		Node<ItemType>* newNode = new Node<ItemType>(newEntry, headPtr);
		// make that Node the new head in the chain
		headPtr = newNode;
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
	itemCount++; // increment number of items
	return true; // return boolean value
} // end insert

#endif