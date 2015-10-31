/* IMPLEMENTATION FILE FOR GETDATA */

#include "GetData.h"
#include <iostream>
#include <string>
#include <fstream>
#include <istream>
#include<sstream>
#include <cctype>
#include <vector>

/* Default Constructor */
GetData::GetData()
{
} // end default constructor 

/* Returns a name from the next line on the file */
std::string GetData::getName(std::ifstream& myFile) const {
	std::string nameOfCity;
	std::getline(myFile, nameOfCity);
	return nameOfCity;
}

/* Returns a pair of two names from the next line in a text file */
// excepts city names to be comma delimited with spaces after each comma
pairNames GetData::getNamePair(std::ifstream& myFile, const char& moreInfoNeeded) const {
	pairNames myCities;
	// get the first city
	std::getline(myFile, myCities.origin, ',');
	// eliminate whitespace
	std::ws(myFile);
	std::string tempString;
	myFile >> tempString;
	myCities.secondCity.append(tempString);
	if (!isdigit(myFile.peek()) && myFile.peek() != '\n' && myFile.peek() != EOF)
	{
		myFile >> tempString;
		myCities.secondCity.append(" ");
		myCities.secondCity.append(tempString);
	} // burn the rest of the line
	if (moreInfoNeeded == 'n')
	{   // if no more info needed burn the line
		getline(myFile, tempString);
	}// remove the whitespace from the second city
	std::cout << "Returning cities \n";
	return myCities;
}

flightInfo GetData::getFlightInfo(std::string& myFilePath, const std::string& origin, const std::string& destination) const
{
	// opens an ifstream on a file path
	std::ifstream myFlightFile(myFilePath);
	bool flightFound = false;
	flightInfo myFlightInfo;
	std::string temp;
	while (!flightFound)
	{
		pairNames myFlight = getNamePair(myFlightFile, 'y');
		std::cout << "origin City: " << myFlight.origin << "to destination " << myFlight.secondCity << std::endl;
			if (myFlight.origin == origin && myFlight.secondCity == destination)
		{
			myFlightFile >> myFlightInfo.flightNo >> myFlightInfo.flightCost;
			flightFound = true;
		}
		std::getline(myFlightFile, temp); // burn rest of line
	}
	return myFlightInfo;
}

/* Returns the total number of cities in a text file */
int GetData::numLines(std::string myFilePath) const {
	std::ifstream myFile(myFilePath);
	int numberOfLines = 0;
	while (myFile.good())
	{
		std::string temp;
		getline(myFile, temp);
		numberOfLines++;
	}
	return numberOfLines;
}
