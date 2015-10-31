/* IMPLEMENTATION FILE FOR DISC */

#include "Disc.h"
#include "Track.h"
#include <iostream>

/* Default constructor */
Disc::Disc() {
	// initializes track list pointer
	trackListPtr = new LinkedSortedList<Track*>();
	// initialize running time
	totalRunningTime = "0:0";
	// read all elements of the disc
	readDisc();
}

/* copy constructor */
Disc::Disc(const Disc& copyDisc) :
trackListPtr(copyDisc.trackListPtr), title(copyDisc.title),
artist(copyDisc.artist), totalRunningTime(copyDisc.totalRunningTime),
genre(copyDisc.genre), year(copyDisc.year), multiArtist(copyDisc.multiArtist)
{
	// end copy constructor
}

/* Copy assignment operator*/
Disc& Disc::operator=(Disc copyDisc) {
	swap(*this, copyDisc);
	return *this;
}

/* no-throw swap function to assist assignment operator */
void Disc::swap(Disc& discToCopyTo, Disc& discToCopy)
{
	using std::swap;
	swap(discToCopyTo.trackListPtr, discToCopy.trackListPtr);
	swap(discToCopyTo.title, discToCopy.title);
	swap(discToCopyTo.artist, discToCopy.artist);
	swap(discToCopyTo.totalRunningTime, discToCopy.totalRunningTime);
	swap(discToCopyTo.genre, discToCopy.genre);
	swap(discToCopyTo.year, discToCopy.year);
	swap(discToCopyTo.multiArtist, discToCopyTo.multiArtist);
}

/* Destructor */
Disc::~Disc() {// when a disc ends, the lives of all it's tracks must also end
	// set the track loopPtr to the initial pointer in the linked list
	// delete all track objects and eliminate dangling pointers
	int totalTracks = trackListPtr->getLength();
	std::cout << "Invoking ~Disc()... " << std::endl;
	for (int i = 1; i <= totalTracks; i++)
	{
		// deallocate the memory for the track object
		// remove the node
		removeTrack(trackListPtr->getEntry(1));
	}
	// delete the track list pointer associated with the object
	// this calls the LinkedSortedList destructor
	// the dangling pointer is destroyed as the object's lifetime ends

	delete trackListPtr;
	/*Track* trackLoopPtr = trackListPtr->getEntry(1);
	int loopCounter = 1;
	while (trackLoopPtr != nullptr && loopCounter <= trackListPtr->getLength())
	{
		// get the pointer to the object at every position in the list 
		trackLoopPtr = trackListPtr->getEntry(loopCounter);
		// delete those pointer objects
		delete trackLoopPtr;
		// the pointer to the object will be deleted when the Disc is deleted, so do not need to worry
		// about eliminating it
		loopCounter++;
	} // end while
	// the list can now destroy itself without harm assuming the LinkedSortedList is implemented without memory leaks
	*/
}

/* checks if track listing is empty*/
bool Disc::isEmpty() const {
	return trackListPtr->isEmpty();
}

/* checks number of tracks */
int Disc::getNumberTracks() const {
	return trackListPtr->getLength();
}

/* inserts a track based on the track number*/
void Disc::insertTrack(Track* trackToInsert) {
	std::string trackNo = trackToInsert->getNumber();
	// if it's the first track insert at first position
	if (trackNo == "1")
	{
		trackListPtr->insert(1, trackToInsert);
	}
	else // else find where the item belongs and insert it
	{
		int posCounter = 1;
		// if the trackNo is greater than the current track number, move its prospective position up one
		// do this until we reach the end of the list
		while (posCounter <= trackListPtr->getLength() && trackListPtr->getEntry(posCounter)->isLessThan(trackToInsert))
		{
			posCounter++;
		}
		trackListPtr->insert(posCounter, trackToInsert);
	}
}

/* removes a track */
void Disc::removeTrack(Track* trackToRemove) {
	// deallocate memory associated with the track object
	delete trackToRemove;
	// remove the node, effectively eliminating its pointer
	trackListPtr->removeSorted(trackToRemove);
}

/* retrieves a track by its number */
Track* Disc::retrieveTrackByNumber(std::string number) const
{
	Track* currentTrack = trackListPtr->getEntry(1);
	int numero = 1;
	while (numero <= trackListPtr->getLength() && currentTrack->getNumber() != number)
	{
		currentTrack = trackListPtr->getEntry(numero);
		numero++;
	}
	return currentTrack;
}

std::string Disc::getArtist() const {
	return artist;
}

std::string Disc::getTitle() const {
	return title;
}

bool Disc::isMultiArtist() const {
	return multiArtist;
}

void Disc::readDisc() {
	using std::cout; using std::cin; using std::endl;
	std::string temp;
	// get disc constants
	cout << "Entering disc configuration..." << endl;
	cout << "Enter Disc Title: ";
	getline(cin, title);
	// check to see if this is a multi-artist disk
	cout << "Is this a multi-artist disk? <y/Y/N/n>:";
	char y;
	cin.get(y);
	getline(cin, temp);
	while (y != 'y' && y != 'n' && y != 'Y' && y != 'N')
	{

		cout << "Invalid input.  Is this a multi-artist disk? <y/Y/n/N>:";
		cin.get(y);
		getline(cin, temp);
	}
	if (y == 'n' || y == 'N')
	{
		cout << "Enter Disc Artist: ";
		getline(cin, artist);
		multiArtist = false;
	}
	else {
		multiArtist = true;
	}
	cout << "Enter Genre: ";
	getline(cin, genre);
	cout << "Enter release year: ";
	getline(cin, year);
	// prompt to enter a track
	char trackPrompt;
	cout << "Enter a track? <y/Y/n/N>:";
	// take first character of input
	cin.get(trackPrompt);
	// throw away the rest of the input
	getline(cin, temp);
	// validate the input
	while (trackPrompt != 'y' && trackPrompt != 'n' && trackPrompt != 'Y' && trackPrompt != 'N')
	{

		cout << endl << "Invalid input.  Enter a track? <y/Y/n/N>:";
		cin.get(trackPrompt);
		getline(cin, temp);
	}
	while (trackPrompt == 'y' || trackPrompt == 'Y')
	{
		// create a new track affiliated with this disc
		// the construction will take care of the Track properties
		Track* newTrack = new Track(this);
		insertTrack(newTrack);
		// prompt user for another track
		cout << endl << "Enter another track? <y/Y/n/N>";
		cin.get(trackPrompt);
		getline(cin, temp);
		// ensure valid input 
		while (y != 'y' && y != 'n' && y != 'Y' && y != 'N')
		{

			cout << endl << "Invalid input.  Enter another track? <y/Y/n/N>:";
			cin.get(y);
			getline(cin, temp);
		}
	}
}

void Disc::printDisc() const {
	using std::cout; using std::endl;
	cout << "Title: " << title << endl;
	if (multiArtist == false)
	{
		cout << "Artist: " << artist << endl;
	}
	cout << "PlayTime: " << totalRunningTime << endl;
	cout << "Genre: " << genre << endl;
	cout << "Release Year: " << year << endl;
	cout << "\t Track Attributes:" << endl;
	cout << "\t Total Tracks: " << getNumberTracks() << endl;
	for (int pos = 1; pos <= trackListPtr->getLength(); pos++)
	{
		trackListPtr->getEntry(pos)->printTrack();
	}
}

void Disc::addToTotalPlayTime(int minutes, int seconds) {
	using std::cout; using std::cin; using std::endl;
	// get the minutes
	std::string temp = totalRunningTime;
	// get index of ':'
	int colonIndex = temp.find(":");
	// convert current minutes of string into an int
	int currentMinutes = stoi(temp.substr(0, colonIndex));
	// get a value for new minutes
	int totalMinutes = currentMinutes + minutes;
	// convert current seconds of string to an int
	int currentSeconds = stoi(temp.substr(colonIndex + 1, temp.length()));
	// add values for new seconds
	int totalSeconds = currentSeconds + seconds;
	// convert integers to strings
	std::string minStr = std::to_string(totalMinutes);
	std::string secStr = std::to_string(totalSeconds);
	// concatenate the new strings and make that the new total running time
	totalRunningTime = minStr + ":" + secStr;
}

bool Disc::isLessThan(const Disc* const otherDisc) {
	return title < otherDisc->getTitle();
}

bool Disc::isLessThanOrEqualTo(const Disc* const otherDisc){
	return title <= otherDisc->getTitle();
}