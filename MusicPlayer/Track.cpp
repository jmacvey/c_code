/* TRACK IMPLEMENTATION FILE */

#include "Track.h"
#include <iostream>
#include "Disc.h"

/* Default constructor */
Track::Track(Disc* const discPtr) : relativeDiscPtr(discPtr){
	// read in values to assign to private data fields
	readTrack(discPtr);
	// read playTime in minutes:seconds format
	readPlayTime();
}

/* Default Destructor */
Track::~Track() {
	std::cout << "Invoking ~Track()..." << std::endl;
}

/*Prompts for and reads in from stdin: the Track name; artist (if a multi-artist Disc);
play time (in min:sec format); and path/filename (location) where Track is stored. */

void Track::readTrack(Disc* const discPtr) {
	using std::cout; using std::cin; using std::endl;
	cout << "Track Configuration Menu: " << endl;
	// prompt for title
	cout << "Enter Track Title: ";
	getline(cin, title);
	// prompt for artist if the disc is multiArtist
	if (discPtr->isMultiArtist())
	{
		cout << "Enter Artist: ";
		getline(cin, artist);
		char y;
		// prompt for another artist
		cout << "Enter another artist (for multi-artist tracks)? <y/Y/n/N>: ";
		cin.get(y);
		std::string temp;
		getline(cin, temp);
		// validate input
		while (y != 'y' && y != 'Y' && y != 'n' && y != 'N')
		{
			cout << "Invalid input.  Enter another artist? <y/Y/n/N>: ";
			cin.get(y);
			getline(cin, temp);
		}
		while (y == 'y' || y == 'Y')
		{
			cout << endl << "Enter Artist: ";
			artist.append(", ");
			getline(cin, temp);
			artist.append(temp);
			cout << endl << "Enter another artist? <y/Y/anyOtherForNo>: ";
			cin.get(y);
			getline(cin, temp);
		}
	} // end prompt artist input
	// prompt for playTime for track
	cout << "Enter track number: ";
	getline(cin, trackNumber);
	// validate the track number
	bool numValid = false;
	while (!numValid)
	{
		int j = 0;
		for (int i = 0; i < trackNumber.length(); i++)
		{
			if (isdigit(trackNumber[i]))
			{
				j++;
			}
		}
		if (j == trackNumber.length())
		{
			numValid = true;
		}
		if (!numValid)
		{
			cout << "Track number invalid. Please enter a track number: ";
			j = 0;
			trackNumber.clear();
			getline(cin, trackNumber);
		}
	}
	cout << "Enter pathname for track: ";
	getline(cin, pathName);
	cout << endl;
} // end readTrack

void Track::printTrack() const {
	using std::cout; using std::endl;
	cout << "\t" << trackNumber << ". ";
	cout << title << endl;
	if (relativeDiscPtr->isMultiArtist())
	{
		cout << "\t \t Artist(s): " << artist << endl;
	}
	cout << "\t \t PathName: " << pathName << endl;
	cout << "\t \t PlayTime: " << playTime << endl;
}

bool Track::isLessThan(const Track* const otherTrack) const {
	return trackNumber < otherTrack->getNumber();
}

std::string Track::getNumber() const {
	return trackNumber;
}

std::string Track::getPlayTime() const {
	return playTime;
}

void Track::readPlayTime() {
	using std::cout; using std::cin; using std::endl;
	cout << "Enter playTime for track (min:sec):";
	std::string temp;
	// get the string
	getline(cin, temp);
	// validateInputTime returns false if invalid, true if valid 
	while (!inputIsValid(temp))
	{
		cout << "Invalid input time. Enter playTime for track (min:sec):";
		temp.clear();
		getline(cin, temp);
	}
	// if valid, convert the strings to integers
	//find the colon index
	int colonIndex = temp.find(':');
	// append string version of minutes to the playTime
	std::string minuteString = temp.substr(0, colonIndex);
	// convert to integral version of minutes
	int minutes = stoi(minuteString);
	// get the seconds;
	std::string secondString = temp.substr(colonIndex + 1, temp.length());
	// convert to integral version of seconds
	int seconds = stoi(secondString);
	// convert seconds to minutes if necessary
	int secondsInMinutes = seconds / 60;
	// add this many minutes to total minutes
	minutes += secondsInMinutes;
	// find remaining seconds
	seconds = seconds % 60;
	// make that the playtime for the track
	playTime.append(std::to_string(minutes) + ':' + std::to_string(seconds));
	// add the track to the total play time
	relativeDiscPtr->addToTotalPlayTime(minutes, seconds);
}

/* validates input time from the string */
bool Track::inputIsValid(std::string inputString) const {
	// begin with assumption that the string is valid
	bool valid = true;
	int colonIndex = inputString.find(':');
	// if the colon is not in the string or is at the first character, the input is invalid
	if (colonIndex == inputString.npos || colonIndex == 0)
	{
		valid = false;
	}
	else {// else validate first part of the string
		int stringLength = inputString.length();
		int i = 0;
		while (i < colonIndex && valid)
		{
			// if the index value is not a digit, value is invalid 
			if (!isdigit(inputString[i]))
			{
				valid = false;
			}
			i++;
		}
		// if the first half of the string is valid, skip the colon digit
		i += 1;
		while (i < stringLength && valid)
		{
			if (!isdigit(inputString[i]))
			{
				valid = false;
			}
			i++;
		}
	}
	return valid;
}
