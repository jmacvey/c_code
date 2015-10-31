#ifndef _ARRAY_LIST_IMPL_H
#define _ARRAY_LIST_IMPL_H
/* Implementation File for ArrayList.h */


/* Default Constructor */
template<class ItemType>
ArrayList<ItemType>::ArrayList() : listLength(0), maxItems(DEFAULT_CAPACITY){
	itemList = new ItemType[DEFAULT_CAPACITY]; // allocate memory
} // end default constructor

/* Copy Constructor */
template<class ItemType>
ArrayList<ItemType>::ArrayList(const ArrayList<ItemType>& listToCopy) : listLength(listToCopy.listLength), maxItems(listToCopy.maxItems)
{
	itemList = new ItemType[listToCopy.maxItems]; // allocate memory
	for (int loopVar = 0; loopVar < listToCopy.listLength; loopVar++)
	{
		itemList[loopVar] = listToCopy.itemList[loopVar]; // copy each item in array
	}
} // end copy constructor

/* Copy assignment operator */
template<class ItemType>
ArrayList<ItemType>& ArrayList<ItemType>::operator=(ArrayList<ItemType> listToCopy) // note pass by value for copy elision
{
	swap(*this, listToCopy);
	return *this;
} // end copy assignment operator

/* no-throw swap function to assist copy assignment operator */
template<class ItemType>
void ArrayList<ItemType>::swap(ArrayList<ItemType>& arrayToCopyTo, ArrayList<ItemType>& arrayToCopy){
	using std::swap;
	swap(arrayToCopyTo.listLength, arrayToCopy.listlength);
	swap(arrayToCopyTo.maxItems, arrayToCopy.maxItems);
	swap(arrayToCopyTo.itemList, arrayToCopy.itemList);
} // end swap

/* Destructor */
template<class ItemType>
ArrayList<ItemType>::~ArrayList() {
	delete[] itemList;
} // end destructor

/* Checks to see if array is empty */
template<class ItemType>
bool ArrayList<ItemType>::isEmpty() const {
	return listLength == 0;
} // end isEmpty

/* Returns the length of the list */
template<class ItemType>
int ArrayList<ItemType>::getLength() const {
	return listLength;
} // end getLength

/* inserts a new item in the i-th position of the list */
template<class ItemType>
bool ArrayList<ItemType>::insert(const int& newPosition, const ItemType& newEntry){
	if (listLength >= maxItems) // if listlength equal to or exceeds maximum size of array
	{
		ItemType* oldList = itemList;
		itemList = new ItemType[maxItems * 2]; // create new array with double capacity
		for (int pos = 0; pos < listLength; pos++)
		{
			itemList[pos] = oldList[pos]; // copy the array
		}
		delete[] oldList; // delete the oldList
		oldList = nullptr; // eliminate dangling pointer
		maxItems *= 2; // double maxItems
	}
	if (newPosition > listLength)
	{
		listLength++;
		itemList[listLength - 1] = newEntry; // put item to end of list if position is greater than length
		return true;
	}
	else
	{
		for (int toIndex = listLength; toIndex >= newPosition; toIndex--)
		{
			int fromIndex = toIndex - 1;
			itemList[toIndex] = itemList[fromIndex]; // shift all greater than newPosition to the right
		}
		itemList[newPosition - 1] = newEntry; // insert new item
		listLength++; // increment listLength
		return true;
	}
} // end insert

/* removes an item from the list */
template <class ItemType>
bool ArrayList<ItemType>::remove(const int& position)
{
	bool ableToRemove = (position <= listLength) && (position >= 1);
	if (ableToRemove)
	{
		for (int fromIndex = position; fromIndex < listLength; fromIndex++)
		{
			int toIndex = fromIndex - 1;
			itemList[toIndex] = itemList[fromIndex];
		}
		listLength--;
	}
	return ableToRemove;
} // end remove

/* clears all items from the list */
template<class ItemType>
void ArrayList<ItemType>::clear() {
	// deallocate memory
	delete[] itemList;
	// reallocate new memory
	itemList = new ItemType[DEFAULT_CAPACITY];
	maxItems = DEFAULT_CAPACITY;
	// empty the list
	listLength = 0;
} // end clear

/* gets item at a position in the list */
template<class ItemType>
ItemType ArrayList<ItemType>::getEntry(const int& position) const
throw(PrecondViolatedExcep) {
	bool ableToGetItem = position <= listLength && position >= 1;
	if (!ableToGetItem)
	{
		throw PrecondViolatedExcep("getEntry() called on emptyList or invalid position. \n");
	}
	return itemList[position - 1];
} // end getItem

template<class ItemType>
void ArrayList<ItemType>::setEntry(const int& position, const ItemType& newEntry)
throw(PrecondViolatedExcep) {
	bool ableToSetItem = position <= listLength && position >= 1;
	if (!ableToSetItem)
	{
		std::string myString = "setItem() called on invalid position. \n";
		throw PrecondViolatedExcep(myString);
	}
	else itemList[position - 1] = newEntry;
}

#endif