//Driver for Dynamic Bag Array

using namespace std;
#include "BagWithReceipts.h"
#include "ExitScript.h"
#include <string>
#include <vector>
#include <iostream>

void displayBag(const BagWithReceipts<string>& aBag)
{
	cout << "The bag contains " << aBag.getCurrentSize()
		<< " items." << endl;
	vector<string> bagContents = aBag.toVector();
	int numberOfItems = aBag.getCurrentSize();
	for (int sizeCounter = 0; sizeCounter < numberOfItems; sizeCounter++)
	{
		cout << bagContents[sizeCounter] << " ";
	}
	cout << endl << endl;
}

void bagTester(BagWithReceipts<string>& aBag)
{
	cout << "isEmpty: returns " << aBag.isEmpty()
		<< "; should be 1 (true);" << endl;
	displayBag(aBag);
	
	string items1[] = { "One", "One", "One" };
	cout << "add 3 same items to the bag: " << endl;
	for (int i = 0; i < 3; i++)
	{
		aBag.add(items1[i]);
	} // end for
	cout << endl << "isEmpty: returns " << aBag.isEmpty()
		<< "; should be 0 (false)." << endl;
	displayBag(aBag);
	cout << endl << "getFrequencyOf(\"One\") returns: " << aBag.getFrequencyOf("One");
	cout << "; should be 3." << endl;

	/*cout << endl << "getFrequencyOf(\"One\") returns: " << aBag.getFrequencyOf("One")
		<< "; should be 3." << endl;*/ //test for getFrequencyOf
	int receiptOne = 1;
	int receiptTwo = 2;
	cout << endl << "Removing the second and last items &" << endl
		<< "adding \"Two\" and \"Three\" to the bag: " << endl << endl;
	aBag.remove(receiptOne);
	aBag.remove(receiptTwo);
	aBag.add("Two");
	aBag.add("Three");
	displayBag(aBag);
	
	string items2[] = { "Four", "Five", "Six" };
	cout << "adding next 3 consecutive numbers to the Bag: " << endl;
	for (int i = 0; i < 3; i++)
	{
		aBag.add(items2[i]);
	} // end for
	cout << endl << "isEmpty: returns " << aBag.isEmpty()
		<< "; should be 0 (false)." << endl; // tests dynamic capabilities of the Array
	displayBag(aBag);
	
	//remove exception testing
	cout << endl << "Attempting to remove a false receipt.  Should return error. " << endl;
	cout << aBag.remove(7) << endl << endl;
	//contains testing
	cout << "contains(\"Two\") returns: " << aBag.contains("Two")
		<< "; should be 1 (true)." << endl;
	
	cout << "Removing \"Two\" from Bag: ";
	aBag.remove(1);
	cout << endl << "contains(\"Two\") returns: " << aBag.contains("Two")
		<< "; should be 0 (false)." << endl;
	
	//clear testing
	cout << "Clearing the Bag:" << endl << endl;
	aBag.clear();
	displayBag(aBag);
	/*int items3[] = { 2, 3 };
	cout << endl << endl << "removing the second and third item from the bag: " << endl;
	for (int i = 0; i < 1; i++)
	{
		aBag.remove(items3[i]);
	} // end for
	displayBag(aBag);
	cout << "The bag should contain One One Two Four.";*/
} 

int main()
{
	BagWithReceipts<string> myBag;
	cout << "Testing the Array-Based Bag: \n";
	cout << "The Initial Bag is Empty. \n";
	bagTester(myBag);
	exitScript();
	return 0;
};
