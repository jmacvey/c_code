#ifndef _GET_DATA_H
#define _GET_DATA_H

#include <fstream>
#include <iostream>

struct pairNames
{
	std::string origin;
	std::string secondCity;
};

struct flightInfo
{
	std::string flightNo;
	std::string flightCost;
};

class GetData {
public:
	/* Default Constructor */
	GetData();
	/* Returns a name from the next line on the file */
	std::string getName(std::ifstream& myFile) const;
	/* Returns a pair of two names from the next line in a text file. */
	pairNames getNamePair(std::ifstream& myFile, const char& moreInfoNeeded) const;
	/* returns flight no and cost of a specific flight */
	flightInfo getFlightInfo(std::string& myFilePath, const std::string& origin, const std::string& destination) const;
	/* Returns the total number of cities in a text file */
	int numLines(std::string myFilePath) const;
};


#endif