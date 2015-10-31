// Implementation file for BagWithReceipts
#ifndef BAGWITHRECEIPTSIMPL_H
#define BAGWITHRECEIPTSIMPL_H

template <class ItemType>
BagWithReceipts<ItemType>::BagWithReceipts() :itemCount(0), maxItems(DEFAULT_CAPACITY), totalItemsAddedEver(0)//Default Constructor 
{
	// initialize receipts array to false
	for (int i = 0; i < DEFAULT_CAPACITY; i++)
	{
		receipts[i] = false;
	} // end for
} //end default constructor

template <class ItemType>
BagWithReceipts<ItemType>::~BagWithReceipts() //default destructor
{
	delete[] items;
	items = nullptr;
	delete[] receipts;
	receipts = nullptr;
} //end destructor

template<class ItemType>
int BagWithReceipts<ItemType>::add(const ItemType& itemToAdd) {
	// check to see if array needs to be enlarged and do so
	enlargeArraySize(itemToAdd);
	int indexReceipt = 0;
	while (receipts[indexReceipt])
	{ //while receipt exists, do not add the bag to that spot in array
		indexReceipt++;
	} //end while
	items[indexReceipt] = itemToAdd; //add item to the Bag
	receipts[indexReceipt] = true; // declare receipt for item
	itemCount++; // increase number of items in bag by 1
	totalItemsAddedEver++;
	return indexReceipt; //return the receipt value of the item
} // end add

template<class ItemType>
ItemType BagWithReceipts<ItemType>::remove(const int& receiptOfItem)
{
	//check to see if receipt matches in parallel array
	if (receipts[receiptOfItem])
	{
		receipts[receiptOfItem] = false; // remove the item
		itemCount--; // decrement itemCounter
		return items[receiptOfItem]; // return the item
	}
	else
	{
		ItemType errorMsg = "Invalid Receipt: No Item Removed.";
		items[receiptOfItem] = errorMsg;
		return items[receiptOfItem];
	}
} //end remove

template <class ItemType>
int BagWithReceipts<ItemType>::getCurrentSize() const
{
	return itemCount; // returns current number of elements in the array
} //end getCurrentSize

template<class ItemType>
void BagWithReceipts<ItemType>::clear()
{ //reset all counters 
	itemCount = 0;
	totalItemsAddedEver = 0;
	//deallocate memory and eliminate dangling pointers of items and receipts arrays
	ItemType* oldItems = items; 
	//reset items
	items = new ItemType[DEFAULT_CAPACITY];
	delete[] oldItems;
	oldItems = nullptr;
	bool* oldReceipts = receipts;
	//re-initalize receipts
	receipts = new bool[DEFAULT_CAPACITY]; 
	for (int i = 0; i < DEFAULT_CAPACITY; i++)
	{
		receipts[i] = false;
	}//end for
	delete[] oldReceipts;
	oldReceipts = nullptr;
} //end clear

template<class ItemType>
bool BagWithReceipts<ItemType>::contains(const ItemType& anEntry) const
{
	return getIndexOfItem(anEntry) >= 0;
} //end contains

template<class ItemType>
bool BagWithReceipts<ItemType>::isEmpty() const
{
	return itemCount == 0;
} // end isEmpty

template<class ItemType>
vector<ItemType> BagWithReceipts<ItemType>::toVector() const
{ //copy individual items of bag to a vector
	vector<ItemType> vectorOfItems;
	for (int itemCounter = 0; itemCounter < totalItemsAddedEver; itemCounter++)
	{
		if (receipts[itemCounter]) //if an item has an associated receipt
		{
			vectorOfItems.push_back(items[itemCounter]);
		} //end if
	}
	return vectorOfItems;
} //end toVector;

template<class ItemType>
int BagWithReceipts<ItemType>::getFrequencyOf(const ItemType& anItem) const
{
	int frequency = 0;
	for (int itemCounter = 0; itemCounter < totalItemsAddedEver; itemCounter++)
	{
		if (receipts[itemCounter] && (items[itemCounter] == anItem))
		{ // if valid receipt with associated item
			frequency++;
		} //endif
	} //endfor
	return frequency;
} //end getFrequencyOf


template <class ItemType>
void BagWithReceipts<ItemType>::enlargeArraySize(const ItemType& anItem)
{
	bool hasRoomToAdd = (itemCount < maxItems);
	if (!hasRoomToAdd)
	{ // if no more room, create a new array with double the size
		ItemType* oldArray = items;
		items = new ItemType[maxItems * 2];
		for (int itemCounter = 0; itemCounter < itemCount; itemCounter++)
		{
			items[itemCounter] = oldArray[itemCounter];
		} //end for
		delete[] oldArray; // deallocate memory associated with the old array
		oldArray = nullptr; // eliminate dangling ptr
		bool* oldReceipts = receipts; // do the same for the parallel array
		receipts = new bool[maxItems * 2]; //Initialize this new boolean array
		for (int arraySizeCounter = 0; arraySizeCounter < (maxItems * 2); arraySizeCounter++)
		{
			receipts[arraySizeCounter] = 0;
		}  //end for
		for (int itemCounter = 0; itemCounter < itemCount; itemCounter++) //copy old array to new array
		{
			receipts[itemCounter] = oldReceipts[itemCounter];
		} // end for
		delete[] oldReceipts; // deallocate memory associated with old array;
		oldReceipts = nullptr; //eliminate dangling pointer
		maxItems *= 2;
	} // end if
} //end enlargeArraySize

template <class ItemType>
int BagWithReceipts<ItemType>::getIndexOfItem(const ItemType& anItem) const
{
	bool found = false;
	int indexOfItem = -1; // index to return
	int indexCounter = 0;
	while ((indexCounter < totalItemsAddedEver) && (!found))
	{
		//index is found if there is an item match and valid receipt
		found = ((items[indexCounter] == anItem) && receipts[indexCounter]);
		if (found)
		{
			indexOfItem = indexCounter;
		} //end if
		indexCounter++;
	} //end while
	return indexOfItem;
} //end getIndexOfItem

#endif

