//@implementation file for Board.h
#include "Board.h"
#include "Queen.h"

bool Board::isQueen(int inRow, int inCol) const
{
	bool queenFound = false;
	int currentVectorSize = queens.size();
	int loopVar = 0;
	while (!queenFound && loopVar < currentVectorSize)
	{
		Queen* queenInspected = queens[loopVar];
		// if row and column match the row and column of a queen in the queens vector
		if ((queenInspected->getCol() == inCol) && (queenInspected->getRow() == inRow))
		{ // then queen is found
			queenFound = true;
		} // go to next queen if queen not yet found
		loopVar++;
	}
	return queenFound;
} // end isQueen

bool Board::placeQueens(Queen* queenPtr)
{
	// Base case: Try to place a queen in a nonexistent column.
	if (queenPtr->getCol() >= BOARD_SIZE)
	{
		delete queenPtr;
		return true;
	} // end if
	bool isQueenPlaced = false;
	while (!isQueenPlaced && queenPtr->getRow() < BOARD_SIZE)
	{
		// If the queen can be attacked, try moving it
		// to the next row in the current column
		if (queenPtr->isUnderAttack()){
			queenPtr->nextRow();
		}
		else
		{
			// Put this queen on the board and try putting a
			// new queen in the first row of the next column
			setQueen(queenPtr);
			Queen* newQueenPtr = new Queen(0, queenPtr->getCol() + 1);
			isQueenPlaced = placeQueens(newQueenPtr);
			// If it wasn't possible to put the new queen in the next column,
			// backtrack by deleting the new queen and moving the last
			// queen placed down one row
			if (!isQueenPlaced)
			{
				delete newQueenPtr;
				removeQueen();
				queenPtr->nextRow();
			} // end if
		} // end if
	} // end while
	return isQueenPlaced;
} // end placeQueens

void Board::removeQueen(){
	queens.pop_back();
	// USE WITH CARE: POSSIBLE MEMORY LEAK 
} // removes a queen from the board but does not deallocate the memory!

void Board::setQueen(Queen* queenPtr)
{
	queens.push_back(queenPtr);
} // end setQueend

/** Supplies the Queen class with a pointer to the board. */
Board::Board(){ //default constructor
	cout << "Building the board and setting the board pointer to " << this << endl;
	Queen::setBoard(this);
	cout << "Verifying that the board pointer for the Queen class is correctly set: " << endl;
	cout << "Queen class points to " << Queen::getBoard() << endl;
	cout << "Compare this with " << this << endl;
	cout << "If numbers match, then the class was initialized correctly." << endl << endl;
} //end default constructor

Board::~Board() { // destructor
	clear();// clear the members of the vector
	Queen::setBoard(nullptr);
	//board is a vector, so it will deallocate itself.
}

void Board::clear(){
	int currentBoardSize = queens.size();
	for (int loopVar = 0; loopVar < currentBoardSize; loopVar++)
	{
		delete queens[loopVar]; // deallocate the memory of the queen
		queens[loopVar] = nullptr; // set queen pointer to null
		// do this for all queens
	}
} //end clear

void Board::display() const {
	cout << "Displaying the queen locations in pairs (Row, Col): \n";
	int currentBoardSize = queens.size();
	for (int loopVar = 0; loopVar < currentBoardSize; loopVar++)
	{
		cout << "Queen #" << loopVar + 1 << ": (";
		cout << queens[loopVar]->getRow() << "," << queens[loopVar]->getCol() << ")" << endl;
	}
	cout << endl << endl;
	cout << "Displaying the Board.  A \"Q\" means a queen is placed at that location. \n \n";
	for (int j = 0; j < BOARD_SIZE; j++) // for the # of rows on the board
	{
		for (int i = 0; i < BOARD_SIZE; i++) // for the # of columns on the board
		{

			if (isQueen(j, i))
			{
				cout << "Q ";
			}
			else cout << "X ";
		}
		cout << endl; // begin new row
	}
	cout << endl << endl;
} //end display

int Board::getNumQueens() const
{
	return queens.size();
} // end getNumQueens

void Board::doEightQueens() // initializes eightQueens problem
{
	cout << "Attempting to Solve the Eight Queens Problem: " << endl;
	cout << "If solution was found, it will be displayed: " << endl << endl;
	Queen* myFirstQueen = new Queen();
	placeQueens(myFirstQueen);
}

Queen* Board::getQueen(int index) const {
	int numQueens = getNumQueens();
	if (index < numQueens)
	{
		return queens[index];
	}
	else
	{
		cout << "Error: No queen exists at index " << index << "." << endl;
		Queen* nullQueen = nullptr;
		return nullQueen;
	}
} // end getQueen
