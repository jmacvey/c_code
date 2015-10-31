/** IMPLEMENTATION FILE FOR CIRCULAR_ARRAY_QUEUE_H **/

#ifndef _CIRCULAR_ARRAY_QUEUE_IMPL_H
#define _CIRCULAR_ARRAY_QUEUE_IMPL_H
// queue works as follows:
// enqueing causes tailindex to move forward
// dequeing causes headIndex to move forward
// 

//utility method
template<class ItemType>
void CircularArrayQueue<ItemType>::resizeArray() {
	// allocate new array with double max items
	ItemType* newQueue = new ItemType[MAX_ITEMS * 2];
	// loopVar will keep track of how many items have been copied 
	int loopVar = 0;
	// use of oldIndexVar and newIndexVar ensures no gaps from headIndex to tailIndex clockwise
	// indexVar keeps track of the index and changes to 0 if we need to loop around
	int oldIndexVar = headIndex;
	// always copy from head to tail
	int newIndexVar = headIndex;
	while (loopVar < itemCount)
	{
		// if the newIndexVar is max items, we need to loop around to index 0 for new array
		if (newIndexVar == MAX_ITEMS * 2)
		{
			newIndexVar = 0;
		}
		// if the oldIndexVar is MAX_ITEMS, we need to loop around to index 0 for old array
		if (oldIndexVar == MAX_ITEMS)
		{
			oldIndexVar = 0;
		}
		newQueue[newIndexVar] = queue[oldIndexVar];
		// increment all variables
		loopVar++;
		newIndexVar++;
		oldIndexVar++;
	}
	// set tailIndex to newIndexVar - 1 (now the new index var minus the additional increment we do on the final loop)
	tailIndex = newIndexVar - 1;
	// deallocate the old queue
	delete[] queue;
	// point queue to the new array;
	queue = newQueue;
	// set newQueue to nullptr
	newQueue = nullptr;
	// maxItems is set to twice itself
	MAX_ITEMS *= 2;
	// head index retain its position
}

// default constructor
template<class ItemType>
CircularArrayQueue<ItemType>::CircularArrayQueue() :
headIndex(0), tailIndex(DEFAULT_CAPACITY - 1),
itemCount(0), MAX_ITEMS(DEFAULT_CAPACITY) // end initializer list
{
	// initialize the Queues
	queue = new ItemType[DEFAULT_CAPACITY];
}

// copy constructor
template <class ItemType>
CircularArrayQueue<ItemType>::CircularArrayQueue(const CircularArrayQueue<ItemType>& rhs) :
headIndex(rhs.headIndex), tailIndex(rhs.tailIndex),
itemCount(rhs.itemCount), MAX_ITEMS(rhs.MAX_ITEMS) // end initializer list
{
	// allocate queue
	queue = new ItemType[MAX_ITEMS];
	// there's only something to copy if the array is not empty
	if (!rhs.isEmpty())
	{
		// loopVar will keep track of how many items have been copied
		int loopVar = 0;
		// indexVar keeps track of the index and changes to 0 if we need to loop around
		int indexVar = headIndex;
		// always copy from head to tail
		while (loopVar < rhs.itemCount)
		{
			// if the indexVar is max items, we need to loop around to index 0
			if (indexVar == rhs.MAX_ITEMS)
			{
				indexVar = 0;
			}
			queue[indexVar] = rhs.queue[indexVar];
			loopVar++;
			indexVar++;
		}
	}
}

// copy assignment operator
template <class ItemType>
CircularArrayQueue<ItemType>& CircularArrayQueue<ItemType>::operator=(CircularArrayQueue<ItemType> rhs){
	CircularArrayQueue<ItemType>::swap(*this, rhs);
	return *this;
}

// no-throw swap function
template <class ItemType>
void CircularArrayQueue<ItemType>::swap(CircularArrayQueue<ItemType>& lhs, CircularArrayQueue<ItemType>& rhs){
	using std::swap;
	// swap all values
	swap(lhs.headIndex, rhs.headIndex);
	swap(lhs.tailIndex, rhs.tailIndex);
	swap(lhs.itemCount, rhs.itemCount);
	swap(lhs.MAX_ITEMS, rhs.MAX_ITEMS);
	swap(lhs.queue, rhs.queue);
}

// default destructor
template <class ItemType>
CircularArrayQueue<ItemType>::~CircularArrayQueue() {
	// deallocate memory associated with the queue
	delete[] queue;
	// eliminate dangling pointer
	queue = nullptr;
	// rest of the queue is set to expire with the class destruction
}

// other functions

template <class ItemType>
bool CircularArrayQueue<ItemType>::isEmpty() const {
	return itemCount == 0;
}

template <class ItemType>
void CircularArrayQueue<ItemType>::clear() {
	// reinitialize data members
	headIndex = 0;
	tailIndex = DEFAULT_CAPACITY - 1;
	itemCount = 0;
	MAX_ITEMS = DEFAULT_CAPACITY;
	// deallocate memory associated with the array
	delete[] queue;
	// allocate a new array
	queue = new ItemType[DEFAULT_CAPACITY];
}

template<class ItemType>
bool CircularArrayQueue<ItemType>::enqueue(const ItemType& newEntry) {
	// if the current array is full, resize it
	if (itemCount == MAX_ITEMS)
	{
		resizeArray();
	}
	tailIndex = (tailIndex + 1) % MAX_ITEMS;
	// insert the item
	queue[tailIndex] = newEntry;
	// add to the item count
	itemCount++;
	return true;
}

template<class ItemType>
bool CircularArrayQueue<ItemType>::dequeue() {
	if (isEmpty())
	{
		std::cout << "Error: Tried to dequeue from an empty queue." << std::endl;
		return false;
	}
	// increment head index using modulo arithmetic
	headIndex = (headIndex + 1) % MAX_ITEMS;
	// decrement the itemCount
	itemCount--;
	return true;
}

template<class ItemType>
ItemType CircularArrayQueue<ItemType>::peekFront() const {
	return queue[headIndex];
}

template<class ItemType>
void CircularArrayQueue<ItemType>::displayQueue() const {
	// loopVar keeps track of how many items have been copied
	std::cout << "Queue attributes: " << std::endl;
	std::cout << "itemCount: " << itemCount << std::endl;
	std::cout << "headIndex: " << headIndex << std::endl;
	std::cout << "tailIndex: " << tailIndex << std::endl;
	std::cout << "maxItems: " << MAX_ITEMS << std::endl;
	std::cout << "Queue from head to tail:" << std::endl;
	int loopVar = 0;
	// indexVar keeps track of index
	int indexVar = headIndex;
	while (loopVar < itemCount)
	{
		// if indexVar is equal to max_items, we need to set it to 0 to account for clockwise loop
		if (indexVar == MAX_ITEMS) 
		{
			indexVar = 0;
		}
		std::cout << queue[indexVar];
		if (loopVar < itemCount - 1)
		{
			std::cout << ", ";
		}
		indexVar++;
		loopVar++;
	}
	std::cout << std::endl;
}

#endif