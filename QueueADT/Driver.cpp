// DRIVER FOR LINKED_QUEUE_ADT

#include "LinkedQueue.h"
#include "CircularArrayQueue.h"
#include <iostream>
#include <string>
#include "ExitScript.h"

void LinkedQueueTest() {
	using std::cout; using std::endl; using std::string;
	// create queue
	LinkedQueue<string> myLinkedQueue;
	cout << "Beginning LinkedQueueTest(): ";
	// enqueue an array of string objects
	string myString[] = { "A", "B", "C", "D" };
	for (int i = 0; i < 4; i++)
	{
		cout << "Enqueuing \"" << myString[i] << "\"..." << endl;
		myLinkedQueue.enqueue(myString[i]);
	}
	cout << "Testing copy constructor... " << endl;
	LinkedQueue<string> copiedLinkedQueue(myLinkedQueue);
	cout << "First item in myLinkedQueue is " << myLinkedQueue.peekFront();
	cout << "; should be A." << endl;
	cout << "First item in copiedLinkedQueue is " << copiedLinkedQueue.peekFront();
	cout << "; should be A." << endl;
	cout << "Dequeing from myLinkedQueue and copiedLinkedQueue..." << endl;
	myLinkedQueue.dequeue(); copiedLinkedQueue.dequeue();
	cout << "First item in myLinkedQueue is " << myLinkedQueue.peekFront();
	cout << "; should be B." << endl;
	cout << "First item in copiedLinkedQueue is " << copiedLinkedQueue.peekFront();
	cout << "; should be B." << endl;
	cout << "Testing the copy assignment operator... " << endl;
	cout << "Dequeing from myLinkedQueue first..." << endl;
	myLinkedQueue.dequeue();
	cout << "First item in myLinkedQueue is " << myLinkedQueue.peekFront();
	cout << "; should be C." << endl;
	cout << "Now setting copiedLinkedQueue to myLinkedQueue..." << endl;
	copiedLinkedQueue = myLinkedQueue;
	cout << "First item in copiedLinkedQueue is " << copiedLinkedQueue.peekFront();
	cout << "; should be C." << endl;
	cout << "Deqeuing from copiedLinkedQueue... " << endl; 
	copiedLinkedQueue.dequeue();
	cout << "First item in copiedLinkedQueue is " << copiedLinkedQueue.peekFront();
	cout << "; should be D." << endl;
	cout << "Deqeuing from copiedLinkedQueue twice; should return error message " << endl;
	copiedLinkedQueue.dequeue(); copiedLinkedQueue.dequeue();
	cout << endl << endl;
}

void arrayQueueTest() {
	using std::cout; using std::endl; using std::string;
	CircularArrayQueue<string> circularQueue;
	cout << "Beginning CircularArrayQueueTest()..." << endl;
	string myString[] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K"};
	for (int i = 0; i < 11; i++)
	{
		cout << "Enqueuing \"" << myString[i] << "\"..." << endl;
		circularQueue.enqueue(myString[i]);
	}
	cout << "Displaying circularQueue:" << endl;
	circularQueue.displayQueue();
	cout << "Testing the copy constructor... " << endl;
	CircularArrayQueue<string> copiedArrayQueue(circularQueue);
	cout << "Displaying copiedArrayQueue:" << endl;
	copiedArrayQueue.displayQueue();
	cout << "Dequeing all items from circularQueue..." << endl;
	for (int i = 0; i < 11; i++)
	{
		circularQueue.dequeue();
	}
	circularQueue.displayQueue();
	string mySecondString[] = { "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };
	for (int i = 0; i < 15; i++)
	{
		cout << "Enqueuing \"" << mySecondString[i] << "\"..." << endl;
		circularQueue.enqueue(mySecondString[i]);
	}
	circularQueue.displayQueue();
	cout << "testing copy assignment operator with expression : \"copiedArrayQueue = circularQueue\"" << endl;
	copiedArrayQueue = circularQueue;
	cout << "Displaying copiedArrayQueue:" << endl;
	copiedArrayQueue.displayQueue();
	cout << "Rediplaying circularQueue:" << endl;
	circularQueue.displayQueue();
}

int main() {
	LinkedQueueTest();
	arrayQueueTest();
	exitScript();
	return 1;
}