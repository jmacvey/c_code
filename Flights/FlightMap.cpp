/* IMPLEMENTATION FILE FOR _FLIGHT_MAP_H */
#include "FlightMap.h"

/* Default Constructor */
FlightMap::FlightMap() {
} // End default Constructor

/* Parameterized Constructor */
FlightMap::FlightMap(std::string cFilePath, std::string fFilePath, std::string rFilePath) :
cityFilePath(cFilePath), flightFilePath(fFilePath), requestFilePath(rFilePath) {
	/** get number of cities served
	  * each city corresponds to:
	  (1) an index in flightList vector
	  (2) the head of an adjacency list
	  */
	GetData myFlightData;
	numCities = myFlightData.numLines(cityFilePath);

	// initialize served citiies
	populateFlightList(myFlightData);

	// initialize adjacency lists
	populateAdjacencyLists(myFlightData);
	std::cout << "Adjacency Lists populated..." << std::endl;
	// initialize the tryNext vector
	// i-th index of vector represents the current position in the i-th adjacency list
	for (int loopVar = 0; loopVar < flightList.size(); loopVar++)
	{
		tryNext.push_back(flightList[loopVar].getNext());
	}
} // end parameterized constructor

/* Destructor */
FlightMap::~FlightMap() {
	// eliminate dangling pointers on vector tryNext
	for (int loopVar = 0; loopVar < tryNext.size(); loopVar++)
	{
		tryNext[loopVar] = nullptr;
	} 
	// vector tryNext safe to deallocate itself now
	// destroy the adjacency lists corresponding to vector flightPath
	destroyAdjacencyLists();
	// vector flightPath safe to deallocate itself now
} // end destructor

void FlightMap::destroyAdjacencyLists() {
	for (int loopVar = 0; loopVar < flightList.size(); loopVar++)
	{
		Node<std::string>* loopPtr = flightList[loopVar].getNext();
		if (loopPtr != nullptr) // if loopPtr = nullptr, then no adjacency list exists
		{
			Node<std::string>* loopPtrTwo = loopPtr->getNext();
			while (loopPtrTwo != nullptr)
			{
				loopPtr->setNext(nullptr); // eliminate dangling pointer in node
				delete loopPtr; // delete object pointed to by loopPtr
				loopPtr = loopPtrTwo; // set loopPtr to next node
				loopPtrTwo = loopPtrTwo->getNext(); // move down the chain
			} // loopPtrTwo ends at nullptr
			delete loopPtr; // deletes final object in chain
			loopPtr = nullptr; //eliminate dangling pointer
		}
		flightList[loopVar].setNext(nullptr); // sets the pointer in the original vector object to null
	} // do for all vector objects
}

void FlightMap::populateFlightList(const GetData& flightData) {
	/** populate the vector */
	// open inputFile stream for city data
	std::ifstream myCFile(cityFilePath);
	for (int loopVar = 0; loopVar < numCities; loopVar++)
	{
		// initialize a new node storing name of city
		Node<std::string> myNewNode(flightData.getName(myCFile), nullptr);
		// push the node onto the vector ;
		flightList.push_back(myNewNode);
	}
}

void FlightMap::populateAdjacencyLists(const GetData& flightData) {
	// open an ifstream on the flightFile
	std::ifstream flightLinks(flightFilePath);
	while (flightLinks.good())
	{
		pairNames twoCities = flightData.getNamePair(flightLinks,'n');	
		std::cout << "Origin city: " << twoCities.origin << "; AdjCity: " << twoCities.secondCity << std::endl;
		addAdjacentCity(twoCities.origin, twoCities.secondCity);
	}
}

void FlightMap::addAdjacentCity(const std::string& originCity, const std::string& adjCity)
{
	// get the node for originCity
	int originIndex = findIndexOfCity(originCity);
	Node<std::string>* adjCityNode = new Node<std::string>(adjCity);
	adjCityNode->setNext(nullptr);
	//std::cout << "flightList[originIndex].getNext(): " << flightList[originIndex].getNext()->getItem() << std::endl;
	if (flightList[originIndex].getNext() == nullptr)
	{
		// if the adjacent list has only origin city
		// then point it at the adjacent city
		std::cout << "Setting " << adjCityNode->getItem() << " adjacent to " << flightList[originIndex].getItem() << std::endl;
		flightList[originIndex].setNext(adjCityNode);
	}
	else {
		// else find the end of the list

		Node<std::string>* nodeTestPtr = flightList[originIndex].getNext();
		while (nodeTestPtr->getNext() != nullptr)
		{
			nodeTestPtr = nodeTestPtr->getNext();
		} // end while.  nodeTestPtr points at final node in list
		// set that node to the adjacent city
		
		std::cout << "Setting " << adjCityNode->getItem() << " adjacent to " << flightList[originIndex].getItem() << std::endl;
		nodeTestPtr->setNext(adjCityNode);
		nodeTestPtr = nullptr; // eliminate dangling pointer
	}
} // end addAdjacentCity

int FlightMap::findIndexOfCity(const std::string& originCity) const {
	int returnIndex = -1;
	int indexMatch = 0;
	bool cityFound = false;
	while (indexMatch < numCities && !cityFound)
	{
		if (flightList[indexMatch].getItem() == originCity)
		{
			cityFound = true;
			returnIndex = indexMatch;
		}
		indexMatch++;
	}
	return returnIndex;
}

/* retrieves the vector containing cities */
std::vector<Node<std::string>> FlightMap::getVector() const {
	return flightList;
}

/* retrieves number of cities */
int FlightMap::getNumCities() const {
	return numCities;
}


/* gets the next adjacent city to a current city
 std::string FlightMap::getNextCity(const std::string& currentCity) const  {
 // get the index of the currentCity
 int currentCityIndex = findIndexOfCity(currentCity);
 // if there are no adjacent cities, return default string
 if (flightList[currentCityIndex].getNext() == nullptr)
 {
 return noCity;
 }
 else
 {
 // loop ptr points to next item in list
 Node<std::string>* loopPtr = flightList[currentCityIndex].getNext();
 int nextCityIndex;
 bool cityVisited = true;
 // city visited and need to avoid assert error on pointer
 while (cityVisited && loopPtr != nullptr)
 {
 // find the index in the vector for the next city in the adjacency list
 nextCityIndex = findIndexOfCity(loopPtr->getItem());
 // if the object in that vector position is marked visited
 if (flightList[nextCityIndex].isVisited())
 {
 // move the loopPtr forward
 loopPtr = loopPtr->getNext();
 }
 else { // else the city is unvisited
 cityVisited = false;
 }
 } // end while
 if (!flightList[nextCityIndex].isVisited())

 // final check in case this city corresponds to
 // the last node in adjacency list
 {
 std::string adjCity = flightList[nextCityIndex].getItem();
 loopPtr = nullptr; // eliminate dangling pointer
 return adjCity; } // end if

 } // end else
 return noCity;
 } */

void FlightMap::markVisited(const std::string& cityVisited) {
	// find index of the city in the vector
	int cityIndex = findIndexOfCity(cityVisited);
	// mark the city as visited
	flightList[cityIndex].setVisitMark();
}

bool FlightMap::isPath(const std::string& originCity, const std::string& destCity) {
	// create a stack for cities
	std::stack<std::string> cityStack;
	// push the origin onto the stack
	cityStack.push(originCity);
	std::string topCity = cityStack.top();
	// while the top city is not the dest city & the stack is not empty
	while (topCity != destCity && !cityStack.empty())
	{
		// find the next unvisited city adjacent to the top city
		std::string nextCity = getNextCity(topCity);
		// if no city is available, pop top city from the stack
		// which is equivalent to backtracking the last city
		if (nextCity == noCity)
		{
			cityStack.pop();
		}
		// else mark the city as visited
		// push the next city onto the stack
		// and make that the new topCity
		else {
			cityStack.push(nextCity);
		}
		if (!cityStack.empty())
		{
			topCity = cityStack.top();
		}
	}
	// if stack is empty at the end of the loop, there exists no path
	return !cityStack.empty();
} // end isPth

void FlightMap::unvisitAll() {
	for (int loopVar = 0; loopVar < numCities; loopVar++)
	{
		flightList[loopVar].clearVisitMark();
	}
	// reinitialize the nextPtr array
	for (int loopVar = 0; loopVar < numCities; loopVar++)
	{
		tryNext[loopVar] = flightList[loopVar].getNext();
	}
}

void FlightMap::processRequests() {
	GetData FlightRequests;
	// open an input file stream on the request file
	std::ifstream rFile(requestFilePath);
	// for the entire file
	while (rFile.good())
	{
		// get an individual request
		pairNames myFlightRequest = FlightRequests.getNamePair(rFile, 'n');
		std::cout << "Request is to fly from " << myFlightRequest.origin << " to "
			<< myFlightRequest.secondCity << "." << std::endl;
		// unvisit all cities and initialize loop variables
		unvisitAll();
		bool originCityServed = false;
		bool destCityServed = false;
		int loopVar = 0;
		// get boolean values if the cities are served
		while (loopVar < numCities && (!originCityServed || !destCityServed))
		{
			if (flightList[loopVar].getItem() == myFlightRequest.origin)
			{
				originCityServed = true;
			}
			if (flightList[loopVar].getItem() == myFlightRequest.secondCity)
			{
				destCityServed = true;
			}
			loopVar++;
		}
		// if both cities served, check if path exists
		if (originCityServed && destCityServed)
		{  // if path exists
			if (isPath(myFlightRequest.origin, myFlightRequest.secondCity))
			{
				std::cout << "HPAir flies from " << myFlightRequest.origin << " to " << myFlightRequest.secondCity
					<< "." << std::endl << std::endl;
			}
			else
			{ // otherwise return that no path exists
				std::cout << "Sorry. No flight from " << myFlightRequest.origin << " to " << myFlightRequest.secondCity <<
					" is available." << std::endl << std::endl;
			}
		}
		// if neither flight is served
		else if (!originCityServed && !destCityServed)
		{
			std::cout << "Sorry. HPAir serves neither " << myFlightRequest.origin << " nor "
				<< myFlightRequest.secondCity << "." << std::endl << std::endl;
		}
		// if origin flight unserved
		else if (!originCityServed)
		{
			std::cout << "Sorry. HPAir does not serve " << myFlightRequest.origin << "." << std::endl << std::endl;
		}
		// else if destination flight unserved
		else {
			std::cout << "Sorry. HPAir does not serve " << myFlightRequest.secondCity << "." << std::endl << std::endl;
		}
		// clear all the cities for the next request
	} // end while
}

// getNextCity version 2 (incorporates nextPtr vector for tracking position in adja
std::string FlightMap::getNextCity(const std::string& currentCity) {
	//get the current city index
	int currentCityIndex = findIndexOfCity(currentCity);
	// if the pointer corresponding to that city is nullptr:
	if (tryNext[currentCityIndex] == nullptr)
	{
		return noCity;
	}
	// else 
	else
	{
		// set the loopPtr to the current pointer in that city's adjacency list
		Node<std::string>* loopPtr = tryNext[currentCityIndex];
		// update the tryNext ptr for that list
		tryNext[currentCityIndex] = loopPtr->getNext();
		// return that city
		return loopPtr->getItem();
	}
}
