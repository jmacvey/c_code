#ifndef _FLIGHT_MAP_H
#define _FLIGHT_MAP_H

#include <vector>
#include <string>
#include <stack>
#include "FlightNode.h"
#include "GetData.h"

/* Forward declaration of GetData Class */
// Provides methods to handle text files
class GetData; 

class FlightMap {
private:
	// vector of linked string nodes to represent the flight path
	/* Description of data structure: 
		- Each vector position represents an origin city
		- Each vector position is the head of a linked adjacency list
		- Any node attached to a link list represents
		  a city adjacent to the origin city. 
	 * Notes:
		- No city in the adjacency list besides its head can be marked as visited
	*/
	std::vector<Node<std::string>> flightList; 
	// number of cities in flight path
	int numCities;
	// flightPath vector
	std::vector<std::string> flightPath;
	// Path to file containing Cities served
	std::string cityFilePath;
	// Path to file containing Flight information
	std::string flightFilePath;
	// Path to file containing flight requests
	std::string requestFilePath;
	// constant string for when no adjacent city exists
	const std::string noCity = "_NO_CITY";
	// allocate vector of tryNext pointers of static size
	std::vector<Node<std::string>*> tryNext;
	/* Populates the vector with origin cities */
	void populateFlightList(const GetData& flightData);
	/* Populates an adjacency list given an origin city */
	void populateAdjacencyLists(const GetData& flightData);
	/* Adds a city to an adjacency list in the flightList vector (Helper function for populateAdj.) */
	void addAdjacentCity(const std::string& originCity, const std::string& adjCity);
	/* Destroys adjacency lists in the flightList vector */
	virtual void destroyAdjacencyLists();
	/* finds index in vector corresponding to an origin city */
	int findIndexOfCity(const std::string& originCity) const;
public:
	/* Default Constructor */
	FlightMap();
	/* Parameterized Constructor */
	FlightMap(std::string cFilePath, std::string fFilePath, std::string rFilePath);
	/* Destructor */
	virtual ~FlightMap();
	/* retrieves the vector containing cities */
	std::vector<Node<std::string>> getVector() const;
	/* retrieves number of cities */
	int getNumCities() const;
	/* gets the next adjacent city to a current city */
	//std::string getNextCity(const std::string& currentCity) const;
	std::string getNextCity(const std::string& currentCity);
	/* marks a city as visited */
	void markVisited(const std::string& cityVisited);
	/* checks via stack algorithm if there is a flightpath from origin to destination */
	bool isPath(const std::string& originCity, const std::string& destCity);
	/* unvisits all cities and resets nextPtr array */
	void unvisitAll();
	/* Processes requests from a request file */
	void processRequests(); 
	/* void Traverse Stack */
};


/* Modifications: 
	- Implement array of try-next pointers so the search can commence where it left off in the adjacency list
	- * Considerations:
		- If getNextCity returns no city, we need to go back to the previous adjacency list
		- we can save a pointer to the next city in the previous adjacency list using a stack
				// Call that stack nextPtrStack
		- when we return to that pointer, we set it to null and pop it from the stack
		- then get the next city
	* Location in program for modification:
		- getNextCity
*/


#endif