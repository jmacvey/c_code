/* TRACK CLASS HEADER FILE */

#ifndef _TRACK_H
#define _TRACK_H

class Disc; 
class DiscList;
#include <string>

class Track {
private:
	std::string title;
	std::string artist;
	std::string playTime;
	std::string pathName;
	Disc* const relativeDiscPtr; // pointer to the disc shouldn't change
	std::string trackNumber;
	Track(); // default constructor in private section
public:
	// constructor associating the track with a disc
	Track(Disc* const discPtr); // the disc pointer is constant
	// Destructor
	~Track(); 
	//Prompts for and reads in from stdin: the Track name; artist (if a multi-artist Disc); 
	//play time (in min:sec format); and path/filename (location) where Track is stored.
	void readTrack(Disc* const discPtr); // disc pointer is constant
	// reads play time in from the user in min:sec
	void readPlayTime();
	// Prints to stdout: the Track number; name; artist (if a multi-artist Disc); 
	// play time (in min:sec format); and path/filename (location) where Track is stored.
	void printTrack() const;
	// returns true if this track number is less than the arguments track number
	bool isLessThan(const Track* const otherTrack) const; // const pointer to constant data!
	// accessor for track's number field
	std::string getNumber() const;
	// gets total play time in min:sec for this track
	std::string getPlayTime() const;
	// validates the user-input for time on a track
	bool inputIsValid(std::string inputString) const;
};


#endif
