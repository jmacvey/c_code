// Driver for sorting algorithms
#include "SortingAlgorithms.h"
#include "eslib.h"


template<typename ItemType>
void displayArray(ItemType anArray[], int size){
	std::cout << "Array Holds: " << std::endl;
	for (int i = 0; i < size; i++)
	{
		std::cout << anArray[i] << " ";
	}
	std::cout << std::endl;
}

void testSelectionSort(){
	std::cout << "Testing selectionSort: \n";
	int myArray[] = { 2, 37, 38, 1, 23 };
	displayArray(myArray, 5);
	RecursiveSorts::selectionSort(myArray, 5);
	displayArray(myArray, 5);
	std::cout << std::endl;
}

void testBubbleSort() {
	std::cout << "Testing bubbleSort: \n";
	int myArray[] = { 2, 37, 38, 1, 23 };
	displayArray(myArray, 5);
	RecursiveSorts::bubbleSort(myArray, 5);
	displayArray(myArray, 5);
	std::cout << std::endl;
}

void testInsertionSort() {
	std::cout << "Testing insertionSort: \n";
	int myArray[] = { 2, 37, 38, 1, 23 };
	displayArray(myArray, 5);
	IterativeSorts::insertionSort(myArray, 5);
	displayArray(myArray, 5);
	std::cout << std::endl;
}

void testMergeSort() {
	std::cout << "Testing mergeSort: \n";
	int myArray[] = { 2, 37, 38, 1, 23, 17, 38, 29, 1, 3, 5, 16, 29 };
	displayArray(myArray, 13);
	RecursiveSorts::mergeSort(myArray, 0, 12);
	displayArray(myArray, 13);
	std::cout << std::endl;
}

void testQuickSort() {
	std::cout << "Testing quickSort: \n";
	int myArray[] = { 2, 37, 38, 1, 23, 17, 38, 29, 1, 3, 5, 16, 29 };
	displayArray(myArray, 13);
	RecursiveSorts::quickSort(myArray, 0, 12);
	displayArray(myArray, 13);
	std::cout << std::endl;
}

int main() {
	testSelectionSort();
	testBubbleSort();
	testInsertionSort();
	testMergeSort();
	testQuickSort();
	exitScript();
	return 0;
}
