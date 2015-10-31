#ifndef BOARD_H
#define BOARD_H
#include "Queen.h"
#include <vector>
#include <cassert>
#include <iostream>

using namespace std;
static const int BOARD_SIZE = 8;

class Board
{
private:
	vector<Queen*> queens; // Array of pointers to queens on the board
	/** Sees whether a queen exists in position (inRow, inCol). */
	bool isQueen(int inRow, int inCol) const;
	/** Attempts to place queens on board, starting with the designated queen. */
	bool placeQueens(Queen* queenPtr);
	/** Removes the last queen from the board, but does not deallocate it. */
	void removeQueen();
	/** Places a queen on the board. */
	void setQueen(Queen* queenPtr);
public:
	/** Supplies the Queen class with a pointer to the board. */
	Board();
	/** Clears the board and removes pointer from queens. */
	~Board();
	/** Clears board. */
	void clear();
	/** Displays board. */
	void display() const;
	/** Initiates the Eight Queens problem. */
	void doEightQueens();
	/** @return The number of queens on the board. */
	int getNumQueens() const;
	/** @return A pointer to the queen at the designated index. */
	Queen* getQueen(int index) const;
}; // end Board

#endif