/* DRIVER FILE FOR hpAIR PROJECT */

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "GetData.h"
#include "FlightNode.h"
#include "FlightMap.h"
#include "eslib.h"

/* Tests the getData class using text files hpAirCityFile
 && hpAirFlightFile.  See file content to compare expected outcomes */
void testGetDataClass() {
	// Test for getName method
	std::cout << "Beginning test for getName method: " << std::endl;
	GetData myData;
	std::ifstream myCityFile("hpAirCityFile.txt");
	while (myCityFile.good())
	{
		std::cout << "City Name: " << myData.getName(myCityFile) << std::endl;
	}
	std::cout << std::endl;

	// Test for getNamePair method
	std::cout << "Beginning test for getNamePair method: " << std::endl;
	std::ifstream myFlightFile("hpAirFlightFile.txt");
	while (myFlightFile.good())
	{
		pairNames myCities = myData.getNamePair(myFlightFile, 'n');
		//std::string mytempString; 
		//std::getline(myFlightFile, mytempString);  // burn a line
		std::cout << "Origin City: " << myCities.origin << " ";
		std::cout << "Destination City: " << myCities.secondCity << std::endl;
	}
	// Test for Flight info
	std::string myFilePath = "hpAirFlightFileTwo.txt";
	std::cout << "Beginning test for getFlightInfo method: " << std::endl;
	flightInfo myFlightInfo = myData.getFlightInfo(myFilePath, "Chicago", "San Diego");
	std::cout << "Flight #" << myFlightInfo.flightNo << " from Chicago to San Diego. Cost: $" << myFlightInfo.flightCost <<
		std::endl;
	std::cout << std::endl;

	//Test for numCities
	std::cout << "Beginning test for numCities method: " << std::endl;
	std::cout << "Number of cities in city file: " <<
		myData.numLines("hpAirCityFile.txt") << std::endl
		<< std::endl;
}

/* Tests the flightMap class */
void flightMapTest()
{
	std::cout << "Beginning tests on FlightMap class: " << std::endl << std::endl;
	// initialize class
	std::cout << "Test line." << std::endl;
	FlightMap myMap("hpAirCityFile.txt",
		"hpAirFlightFile.txt", 
		"hpAirRequestFile.txt");
	std::cout << "FlightMap initialized." << std::endl;
	// test initialization
	std::cout << "Testing Initialization on FlightMap" << std::endl << std::endl;
	std::cout << "Flight map contains " << myMap.getNumCities() << " cities." << std::endl;
	std::cout << "City list currently in vector: " << std::endl;
	std::vector<Node<std::string>> myCityVector = myMap.getVector();
	// output the origin cities located in vector
	for (int loopVar = 0; loopVar < myMap.getNumCities(); loopVar++)
	{
		std::cout << myCityVector[loopVar].getItem() << std::endl;
	}
	// output the adjacent cities
	for (int loopVar = 0; loopVar < myMap.getNumCities(); loopVar++)
	{
		std::cout << "Flights from " << myCityVector[loopVar].getItem() << " to ";
		Node<std::string>* loopPtr = myCityVector[loopVar].getNext();
		if (loopPtr == nullptr)
		{
			std::cout << "nowhere." << std::endl;
		}
		while (loopPtr != nullptr)
		{
			std::cout << loopPtr->getItem() << ", ";
			loopPtr = loopPtr->getNext();
		}
		std::cout << std::endl << std::endl;
	}
	// test getNextCity && markCity
	std::cout << "Testing getNextCity(\"Chicago\"): \n";
	std::cout << "next unvisted city adjacent to Chicago is: " << myMap.getNextCity("Chicago") << std::endl;
	std::cout << "Marking San Diego as visited. " << std::endl;
	myMap.markVisited("San Diego");
	std::cout <<  "next unvisited city adjacent to Chicago is: " << myMap.getNextCity("Chicago") << std::endl;
	std::cout << "Marking Albuquerque as visited. " << std::endl;
	myMap.markVisited("Albuquerque");
	std::cout << "next unvisited city adjacent to Chicago is: " << myMap.getNextCity("Chicago") << std::endl;
	// test unvisit all cities
	std::cout << "Unvisiting all cities: " << std::endl;
	myMap.unvisitAll();
	std::cout << "next unvisited city adjacent to Chicago is: " << myMap.getNextCity("Chicago") << std::endl << std::endl;
	// test isPath
	myMap.unvisitAll();
	std::cout << "testing isPath method: " << std::endl;
	std::cout << "isPath(Albuquerque, San Diego) returns: " << myMap.isPath("Albuquerque", "San Diego") 
		<< "; should be 1 (true)." << std::endl;
	myMap.unvisitAll();
	std::cout << "isPath(Chicago, Albuquerque) returns: " << myMap.isPath("Chicago", "Albuquerque") 
		<< "; should be 1 (true)." << std::endl;
	myMap.unvisitAll();
	std::cout << "isPath(Chicago, Paris) returns: " << myMap.isPath("Chicago", "Paris")
		<< "; should be 0 (false)." << std::endl << std::endl;
	myMap.unvisitAll();
	// test processFlights
	std::cout << "testing processRequests method: " << std::endl;
	std::cout << "Processing Requests... " << std::endl << std::endl;
	myMap.processRequests();
}

int main() {
	std::cout << "Initializing tests of GetData class: " << std::endl;
	testGetDataClass();
	flightMapTest();
	exitScript();
	return 0;
}
