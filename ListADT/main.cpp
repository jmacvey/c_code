/* Driver for list ADT */
#include <iostream>
#include "ArrayList.h"
#include "LinkedList.h"
#include "exceplib.h"
#include <string>


void arrayListTest()
{
	using std::cout; using std::endl; using std::string;
	cout << "Initializing listTest for ArrayList: " << endl;
	ArrayList<std::string> myArrayList;
	cout << "isEmpty() returns: " << myArrayList.isEmpty() << "; should be 1 (true)." << endl;
	cout << "Inserting an item into position 1..." << endl;
	string myString = "Eggs";
	myArrayList.insert(1, myString);
	cout << "isEmpty() returns: " << myArrayList.isEmpty() << "; should be 0 (false)." << endl;
	cout << "getEntry(1) returns: " << myArrayList.getEntry(1) << "; should be \"Eggs\"." << endl;
	cout << "getEntry(2) should throw an exception: " << endl;
	try {
		myArrayList.getEntry(2);
	}
	catch (std::logic_error logErr)
	{
		std::cout << logErr.what();
	}
}


void linkedListTest()
{
	using std::cout; using std::endl; using std::string;
	cout << "Initializing listTest for LinkedList: " << endl;
	LinkedList<std::string> myLinkedList;
	cout << "isEmpty() returns: " << myLinkedList.isEmpty() << "; should be 1 (true)." << endl;
	cout << "Inserting an item into position 1..." << endl;
	string myString = "Eggs";
	myLinkedList.insert(1, myString);
	cout << "isEmpty() returns: " << myLinkedList.isEmpty() << "; should be 0 (false)." << endl;
	cout << "getEntry(1) returns: " << myLinkedList.getEntry(1) << "; should be \"Eggs\"." << endl;
	cout << "getEntry(2) should throw an exception: " << endl;
	try {
		myLinkedList.getEntry(2);
	}
	catch (std::logic_error logErr)
	{
		std::cout << logErr.what();
	}
	cout << "setEntry(1,Potatoes)..." << endl;
	myLinkedList.setEntry(1, "Potatoes");
	cout << "getEntry(1) returns: " << myLinkedList.getEntry(1) << "; should be \"Potatoes\"." << endl;
	cout << "removing first item from list: " << endl;
	myLinkedList.remove(1);
	cout << "isEmpty() returns: " << myLinkedList.isEmpty() << "; should be 1 (true)." << endl;
	cout << "getEntry(1) should throw an exception: " << endl;
	try {
		myLinkedList.getEntry(1);
	}
	catch (std::logic_error logErr)
	{
		std::cout << logErr.what();
	}
	cout << endl;
	cout << "adding multiple items to the list... " << endl;
	std::string myStringTwo[] = { "Eggs", "Potatoes", "Milk", "Carrots" };
	for (int i = 1; i <= 4; i++)
	{
		myLinkedList.insert(i, myStringTwo[i-1]);
	}
	cout << "isEmpty() returns: " << myLinkedList.isEmpty() << "; should be 0 (false)." << endl;
	cout << "getEntry(1) returns: " << myLinkedList.getEntry(1) << "; should be \"Eggs\"." << endl;
	cout << "displaying the list: " << endl;
	myLinkedList.displayList();
	cout << "should read: \"Eggs\", \"Potatoes\", \"Milk\", \"Carrots\"" << endl;
	/*
	cout << "Testing copy constructor " << endl;
	LinkedList<std::string>  myCopy(myLinkedList);
	cout << "myCopy.getEntry(1) returns: " << myCopy.getEntry(1) << "; should be \"Potatoes\"." << endl;
	cout << "Testing copy assignment operator: " << endl;
	LinkedList<std::string> myCopyTwo = myCopy;
	cout << "myCopyTwo.getEntry(1) returns: " << myCopyTwo.getEntry(1) << "; should be \"Potatoes\"." << endl; */

}

void exitScript(){
	using std::cout; using std::cin; using std::endl;
	cout << "Testing Complete! Exit? <y>:";
	std::string y;
	std::getline(std::cin, y);
	while (y != "y")
	{
		cout << endl << "Invalid input.  Exit? <y>:";
		std::getline(cin, y);	
	}
}

int main()
{
	arrayListTest();
	linkedListTest();
	exitScript();
	return 1;
}
