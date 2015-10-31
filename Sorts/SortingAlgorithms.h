#ifndef _SORTING_ALGORITHMS_H
#define _SORTING_ALGORITHMS_H

#include <algorithm> // for std::swap
#include <iostream> 

const int MAX_SIZE = 50;
/** Finds the largest item in an Array
 @pre the size of the array >= 1.
 @post the arguments are unchanged.
 @param theArray[] the array to be sorted.
 @param size the size of the array.
 @return the index of the largest item in the array. */
template<typename ItemType>
int findIndexOfLargest(const ItemType theArray[], const int& size);


/** Sorts an array in ascending order
 @pre the size of the array >= 1
 @post the array is sorted in ascending order.
 @param theArray[] the array to be sorted.
 @param size the size of the array
 @growth O(n^2). */
template<typename ItemType>
void selectionSort(ItemType theArray[], int size);

/** Sorts an array in ascending order
@pre the size of the array >= 1
@post the array is sorted in ascending order.
@param theArray[] the array to be sorted.
@param size the size of the array  */
template<typename ItemType>
void bubbleSort(ItemType theArray[], int size);

/** Sorts an array in ascending order
@pre the size of the array >= 1
@post the array is sorted in ascending order.
@param theArray[] the array to be sorted.
@param size the size of the array  */
template<typename ItemType>
void insertionSort(ItemType theArray[], int size);

/** Sorts an array in ascending order
@pre the size of the array is >= 1
@post the array is sorted in ascending order.
@param theArray[] the array to be sorted
@param first lower bound for sorting algorithm, generally the lowest index in array.
@param last the last index in the array, or the last index in the subarray to be sorted. */
template<typename ItemType>
void mergeSort(ItemType theArray[], int first, int last);

template<typename ItemType>
void merge(ItemType theArray[], int first, int mid, int last);


/** Sorts an array in ascending order
@pre the size of the array is >= 1
@post the array is sorted in ascending order.
@param theArray[] the array to be sorted
@param first lower bound for sorting algorithm, generally the lowest index in array.
@param last the last index in the array, or the last index in the subarray to be sorted. */
template<typename ItemType>
void quickSort(ItemType theArray[], int first, int last);

template<typename ItemType>
void sortFirstMiddleLast(ItemType theArray[], int first, int mid, int last);

template<typename ItemType>
int partition(ItemType theArray[], int first, int last);



// Implementation of findIndexLargestOf
template<typename ItemType>
int findIndexOfLargest(const ItemType theArray[], const int& size) {
	int indexOfLargest = 0;
	for (int searchIndex = 0; searchIndex < size; searchIndex++)
	{
		if (theArray[searchIndex] >= theArray[indexOfLargest])
		{
			indexOfLargest = searchIndex;
		}
	}
	return indexOfLargest;
}


namespace IterativeSorts {

	// Iterative Implementation of selectionSort
	template<typename ItemType>
	void selectionSort(ItemType theArray[], int size)
	{
		for (int currentSize = size - 1; currentSize > 0; currentSize--) // runs n-1 times
		{
			int largestValueIndex = findIndexOfLargest(theArray, currentSize + 1);
			std::swap(theArray[currentSize], theArray[largestValueIndex]); // 3 exchanges
		}
	}
	/* Analysis of Iterative selectionSort:
		largestValueIndex runs (n-1) + (n-2) + ... + 1 + n -n = n(n+1)/2 - n = n(n-1)/2 times
		sort runs n-1 times for a total of 3*(n-1) exchanges.
		so the entire operation costs 3*(n-1) + n(n-1)/2 = (n+6)(n-1)/2 = n^2 + 5n/2 - 3
		-> O(n^2) = INEFFICIENT FOR LARGE ARRAYS */

	// Iterative Implementation of bubbleSort
	template<typename ItemType>
	void bubbleSort(ItemType theArray[], int size)
	{
		int valOne, valTwo;
		for (int currentSize = size - 1; currentSize > 0; currentSize--) // bubble to the top
		{
			for (int nextVal = 0; nextVal < currentSize; nextVal++) // 
			{
				// compare values for member & adjacent member
				if (theArray[nextVal] >= theArray[nextVal + 1]) // 1 comparison each round
				{
					std::swap(theArray[nextVal], theArray[nextVal + 1]); // exchange places if out of order
					// cost of 3 exchanges if comparison is true
				}
				// else do nothing
			} // end inner for
		} // end outer for
	} // end bubbleSort
	/* Analysis of iterative bubbleSort:
		outer loop executes n - 1 times.
		inner loop executes (n-1) + (n-2) + ... + 2 + 1 + n - n = n(n+1)/2 - n = n(n-1)/2
		worst case scenario on exchanges: we get (n-1) + (n-2) + ... + 2 + 1 confirmations -> 3*n(n-1)/2 exchanges
		total cost: n(n-1)/2 + 3*n*(n-1)/2 = 2*n*(n-1) cycles -> O(n^2) */

	// Iterative Implementation of insertionSort
	/*template<typename ItemType>
	void insertionSort(ItemType theArray[], int size){
	int lastIndexInSorted = 0;
	// the first data item is sorted
	// mental note: first index in unsorted is lastIndexInSorted + 1
	// want to insert items into the sorted side until the lastIndexInSorted = size -1
	while (lastIndexInSorted != size - 1)
	{
	for (int sortIndex = 0; sortIndex <= lastIndexInSorted; sortIndex++) // for the sorted partition
	{
	if (theArray[sortIndex] >= theArray[lastIndexInSorted + 1])
	{
	// if an item in the sorted partition is greater than or equal to first item unsorted
	// shift all the greater value items in sorted to the right
	for (int greaterItemIndex = sortIndex; greaterItemIndex <= lastIndexInSorted; greaterItemIndex++)
	{
	std::swap(theArray[greaterItemIndex], theArray[lastIndexInSorted + 1]);
	} // end for
	} // end if
	} // end for
	lastIndexInSorted++; // increment the last index in sorted for each item added
	} // end while
	} // end insertionSort */

	//iterative implementation of insertionSort
	template<typename ItemType>
	void insertionSort(ItemType theArray[], int size){
		for (int unsorted = 1; unsorted < size; unsorted++)
		{
			// At this point, theArray[0..unsorted-1] is sorted.
			// Find the right position (loc) in theArray[0..unsorted]
			// for theArray[unsorted], which is the first entry in the
			// unsorted region; shift, if necessary, to make room
			ItemType nextItem = theArray[unsorted];
			int loc = unsorted;
			while ((loc > 0) && (theArray[loc - 1] > nextItem))
			{
				// Shift theArray[loc - 1] to the right
				theArray[loc] = theArray[loc - 1];
				loc--;
			} // end while
			// At this point, theArray[loc] is where nextItem belongs
			theArray[loc] = nextItem; // Insert nextItem into sorted region
		} // end while
	} // end insertionSort
	/** Analysis of iterative insertionSort:
	 // outer loop runs n-1 times at two assignments
	 // the while loop runs n(n-1)/2 times at least.
	 // total : 2*(n-1) + n(n-1)/2 = (n+4)(n-1)/2 times -> O(n^2) */

} // end iterativeSorts namespace

namespace RecursiveSorts {

	// Recursive Implementation of selectionSort
	template<typename ItemType>
	void selectionSort(ItemType theArray[], int size){
		// place largest value at the end of the array
		if (size > 0)
		{
			// find the index of the largest value
			int largestValueIndex = findIndexOfLargest(theArray, size);
			// store the value at that index
			ItemType temp = theArray[largestValueIndex];
			// swap the values of the largest with size
			theArray[largestValueIndex] = theArray[size - 1];
			theArray[size - 1] = temp;
			// sort the rest of the array
			selectionSort(theArray, size - 1);
		}
	}

	// recursive implementation of bubbleSort
	template<typename ItemType>
	void bubbleSort(ItemType theArray[], int size) {
		if (size > 0)
		{
			for (int curVal = 0; curVal < size - 1; curVal++) // bubble the largest value
			{
				if (theArray[curVal] >= theArray[curVal + 1])
				{
					std::swap(theArray[curVal], theArray[curVal + 1]);
				}
			} // end for
			bubbleSort(theArray, size - 1); // bubble the rest of the Array
		}
	} // end bubbleSort


	template<typename ItemType>
	void merge(ItemType theArray[], int first, int mid, int last){
		ItemType tempArray[MAX_SIZE];
		int first1 = first;
		int first2 = mid + 1;
		int last1 = mid;
		int last2 = last;
		// while the arrays are not empty
		int index = first1; // next available index in temporary array
		// the two halves of the array are already sorted, so just sort the next two halves
		while ((first1 <= last1) && (first2 <= last2))
		{
			if (theArray[first1] <= theArray[first2])
			{
				// copy the lowest value into the temp array
				tempArray[index] = theArray[first1];
				first1++;
			}
			else // the value in the second half is smaller
			{
				tempArray[index] = theArray[first2];
				first2++;
			}
			index++;
		} // this may leave items in one or the other (but never both) of the arrays we need to take care of
		// do so with these while loops
		while (first1 <= last1)
		{
			tempArray[index] = theArray[first1];
			first1++;
			index++;
		}
		while (first2 <= last2)
		{
			tempArray[index] = theArray[first2];
			first2++;
			index++;
		}
		//copy the items into the the array
		for (int tempIndex = first; tempIndex <= last; tempIndex++)
		{
			theArray[tempIndex] = tempArray[tempIndex];
		}
	} // end mergeSort
	// recursive implementation of mergeSort
	template<typename ItemType>
	void mergeSort(ItemType theArray[], int first, int last) {
		// find midpoint of array
		int mid;
		if (first < last)
		{
			mid = first + (last - first) / 2;
			// mergeSort the first half
			mergeSort(theArray, first, mid);
			// mergeSort the second half
			mergeSort(theArray, mid + 1, last);
			// merge the two halves 
			RecursiveSorts::merge(theArray, first, mid, last);
		}
	} // end mergeSort

	// implementation of merge helper function to mergeSort
	/** mergeSort Analysis:
		we start with an array of n items.  divide by 2 until n = 1;.
		so we have n/2^k where k is the # of recursive calls.
		Assuming at worst n = 2^k -> k = log_2(n) recursive calls.
		for each call we have to execute.  We work both sides of the array so we end up with
		2*log_2(n) recursive calls.
		Now each recursive call calls for n copies, at the most.
		So in total we have 2*n*log_2(n) calls -> O(nlogn)
		*/

	template<typename ItemType>
	void sortFirstMiddleLast(ItemType theArray[], int first, int mid, int last)
	{
		if (theArray[first] > theArray[mid])
		{
			std::swap(theArray[first], theArray[mid]);
		}
		if (theArray[mid] > theArray[last])
		{
			std::swap(theArray[mid], theArray[last]);
		}
		if (theArray[first] > theArray[mid])
		{
			std::swap(theArray[mid], theArray[last]);
		}
	}

	template<typename ItemType>
	int partition(ItemType theArray[], int first, int last) {
		int mid = first + (last - first) / 2; // obtain midpoint of array
		sortFirstMiddleLast(theArray, first, mid, last); // sort original three integers
		std::swap(theArray[last - 1], theArray[mid]); // swap 2nd to last item with mid-value (pivot)
		int pivotIndex = last - 1;
		ItemType pivot = theArray[pivotIndex];
		// initialize partition regions
		int indexFromRight = last - 2;
		int indexFromLeft = first + 1; // get the second item
		bool done = false; // boolean value suggesting completion of partitioning
		while (!done)
		{ // find first value greater than pivot
			while (theArray[indexFromLeft] < pivot)
			{
				indexFromLeft++;
			}
			// find first value greater then pivot from right
			while (theArray[indexFromRight] > pivot)
			{
				indexFromRight--;
			}
			if (indexFromLeft < indexFromRight)
			{   // swap the values
				std::swap(theArray[indexFromLeft], theArray[indexFromRight]);
				indexFromLeft++;
				indexFromRight--;
			}
			else {
				done = true;
			}
		}
		// place pivot in proper location
		std::swap(theArray[indexFromLeft], theArray[last - 1]);
		pivotIndex = indexFromLeft;
		std::cout << "Returning pivotIndex: " << pivotIndex << std::endl;
		return pivotIndex;
	} // end partition

	template<typename ItemType>
	void quickSort(ItemType theArray[], int first, int last)
	{
		if (last - first + 1 < 10)
		{
			IterativeSorts::insertionSort(theArray, last + 1);
		}

		else {// partition the array and obtain the pivot index
			int pivotIndex = partition(theArray, first, last);
			// quicksort the left side of the array
			quickSort(theArray, first, pivotIndex - 1);
			// quicksort the right side of the array
			quickSort(theArray, pivotIndex + 1, last);
		} // end quickSort
	}


} /* END ITERATIVE NAMESPACE */







#endif
