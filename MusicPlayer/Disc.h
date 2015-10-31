/* DISC HEADER FILE */

#ifndef _DISC_H
#define _DISC_H

#include "LinkedSortedList.h"
#include <string>

class Track; // forward declaration of Track

class Disc
{
private:
	// pointer to list of track pointers 
	LinkedSortedList<Track*>* trackListPtr; 
	// title of disc
	std::string title;
	// artist of disc
	std::string artist;
	// TotalRunningTime
	std::string totalRunningTime;
	// Genre
	std::string genre;
	// year
	std::string year;
	// checks if the disc is multi artist
	bool multiArtist;
public:
	// default constructor
	Disc();
	// copy constructor 
	Disc(const Disc& copyDisc);
	// copy assignment operator (copy elision)
	Disc& operator=(Disc copyDisc);
	// swap function to assist with copy assignment operator
	void swap(Disc& discToCopyTo, Disc& discToCopy);
	// default destructor
	~Disc();
	// checks if track list is empty
	bool isEmpty() const;
	// checks number of tracks
	int getNumberTracks() const;
	// inserts a track 
	void insertTrack(Track* trackToInsert);
	// removes a track
	void removeTrack(Track* trackToRemove);
	// retrieves a track by its number
	Track* retrieveTrackByNumber(std::string number) const;
	// returns artist of disc
	std::string getArtist() const;
	// returns title of disc
	std::string getTitle() const;
	// checks to see if disc is multi-Artist
	bool isMultiArtist() const;
	// Prompts for and reads in numerous attributes about disc including:
	// Artists, Title, Genre, Year, total running time, all tracks information on the disc
	void readDisc();
	// print all disc characteristics
	void printDisc() const;
	// adds running time of a track to total played time
	void addToTotalPlayTime(int minutes, int seconds);
	// compares title of two discs for less than
	bool isLessThan(const Disc* const otherDisc);
	// compares title of two discs for less than or equal to
	bool isLessThanOrEqualTo(const Disc* const otherDisc);
};

#endif