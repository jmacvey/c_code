// Driver for the Musics Player

#include "LinkedSortedList.h"
#include "Disc.h"
#include "DiscList.h"
#include "Track.h"
#include <iostream>
#include <string>
#include "ExitScript.h"

/* forward declarations of driver functions */
void mainMenu(DiscList* const myMusicLibrary);
void validateMenuInput(char menuChoice, DiscList* const myMusicLibrary);
void executeOption(char menuChoice, DiscList* const myMusicLibrary);

void mainMenu(DiscList* const myMusicLibrary) {
	using std::cout; using std::cin; using std::endl;
	cout << endl << "Main Menu" << endl;
	cout << "(A)dd a new disc." << endl;
	cout << "(R)emove a disc." << endl;
	cout << "(P)rint a disc." << endl;
	cout << "(L)ist discs." << endl;
	cout << "(Q)uit" << endl;
	char menuChoice;
	// take the first character of input
	cin.get(menuChoice);
	// throw away rest of line
	std::string temp;
	getline(cin, temp);
	// validate the input
	validateMenuInput(menuChoice, myMusicLibrary);
	// execute the option
	executeOption(menuChoice, myMusicLibrary);
}

void validateMenuInput(char menuChoice, DiscList* const myMusicLibrary) {
	using std::cout; using std::endl; using std::cin;
	while (menuChoice != 'Q' && menuChoice != 'q' && menuChoice != 'A' && menuChoice != 'a' && menuChoice != 'R' && menuChoice != 'r' && menuChoice != 'P' && menuChoice != 'p' && menuChoice != 'L' && menuChoice != 'L')
	{
		cout << "Invalid Input.  Returning to main menu." << endl << endl;
		mainMenu(myMusicLibrary);
	}
}

void executeOption(char menuChoice, DiscList* const myMusicLibrary) {
	using std::cout; using std::endl;
	switch (menuChoice)
	{
		// Add a disk
	case 'A':
	case 'a':
	{
		Disc* const newDisc = new Disc();
		myMusicLibrary->insertDisc(newDisc);
		mainMenu(myMusicLibrary);
	}
	break;
	// Remove a disk
	case 'R':
	case 'r':
	{
		if (myMusicLibrary->numberOfDiscs() == 0)
		{
			cout << "Error:  No disc exists.  Returning to main menu..." << endl;
		}
		else
		{
			// get title of disc
			cout << "Enter title of Disc: ";
			std::string searchTitle;
			getline(std::cin, searchTitle);
			// ensure the title exists
			int discPos = myMusicLibrary->findDiscPosition(searchTitle);
			while (discPos == -1)
			{
				cout << "Disc not found.  Enter title of Disc or (L) for a list of Disks: ";
				std::string searchTitle;
				getline(std::cin, searchTitle);
				discPos = myMusicLibrary->findDiscPosition(searchTitle);
			}
			// if the title exists, prompt the user for final validation and execute removal
			Disc* queryDisc = myMusicLibrary->retrieveDisc(discPos);
			cout << "Warning: This action cannot be undone." << endl;
			cout << "Are you sure you want to remove Disc : " << queryDisc->getTitle() << "? <y/Y/anyOtherForNo>:";
			char y;
			std::cin.get(y);
			getline(std::cin, searchTitle); // burn the rest of the line
			if (y == 'Y' || y == 'y')
			{
				cout << "Removing disc..." << endl;
				myMusicLibrary->removeDisc(queryDisc);
			}
			else
			{
				cout << "Disc not removed.  Returning to main menu." << endl;
			}
		}
		mainMenu(myMusicLibrary);
	}
	break;
	// Print a disk
	case 'P':
	case 'p':
	{
		if (myMusicLibrary->numberOfDiscs() == 0)
		{
			cout << "Error:  No disc exists.  Returning to main menu..." << endl;
		}
		else {
			// get title of disc
			cout << "Enter title of Disc: ";
			std::string searchTitle;
			getline(std::cin, searchTitle);
			// ensure the title exists
			int discPos = myMusicLibrary->findDiscPosition(searchTitle);
			while (discPos == -1)
			{
				cout << "Disc not found.  Enter title of Disc or (L) for a list of Disks: ";
				std::string searchTitle;
				getline(std::cin, searchTitle);
				discPos = myMusicLibrary->findDiscPosition(searchTitle);
			}
			// if the title exists, retrieve the title
			Disc* queryDisc = myMusicLibrary->retrieveDisc(discPos);
			queryDisc->printDisc();
		}
		mainMenu(myMusicLibrary);
	}
	break;
	// List the disks
	case 'L':
	case 'l':
	{
		cout << "Listing Discs..." << endl;
		myMusicLibrary->printList();
		cout << endl;
		mainMenu(myMusicLibrary);
	}
	break;
	// Default: Quit
	default:
		cout << "Exiting Program..." << endl;
	}
}

int main() {
	DiscList* myMusicLibrary = new DiscList();
	mainMenu(myMusicLibrary);
	exitScript();
	return 1;
}
