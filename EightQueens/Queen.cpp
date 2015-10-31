//@implementation file for Queen header

#include "Queen.h"
#include "Board.h"

const Board* Queen::boardPtr = nullptr;

// Private methods
Queen::Queen() : row(0), col(0)
{
	//default constructor for queen
} // end default constructor

Queen::Queen(int inRow, int inCol)
{
	row = inRow;
	col = inCol;
} // end parameterized constructor

int Queen::getCol() const {
	return col;
} // end accessor for column

int Queen::getRow() const {
	return row;
} // end accessor for row

void Queen::nextRow() {
	row = row + 1;
} // end mutator for row

bool Queen::belowAndToRight() const
{
	bool isAttacked = false;
	int numQueens = boardPtr->getNumQueens();
	Queen* queenConsidered = nullptr; //need to check for all the queens
	for (int queenIndex = 0; queenIndex < numQueens; queenIndex++)
	{
		queenConsidered = boardPtr->getQueen(queenIndex);
		int rowOfQueenConsidered = queenConsidered->getRow(); // get row of queen in question
		int colOfQueenConsidered = queenConsidered->getCol(); // get column of queen in question
		//initialize row/col to check
		int colOfQueen = col;
		int rowOfQueen = row;
		//check the diagonal below and to the right
		while (!isAttacked && rowOfQueen <= BOARD_SIZE && rowOfQueen <= BOARD_SIZE)
		{
			rowOfQueen++;
			colOfQueen++;
			if (rowOfQueen == rowOfQueenConsidered && colOfQueen == colOfQueenConsidered)
			{
				isAttacked = true;
				queenConsidered = nullptr; //eliminate dangling pointer
				return isAttacked; // exit loop if queen is attacked
			}
		}
	}
	return isAttacked;
}


bool Queen::belowAndToLeft() const
{
	bool isAttacked = false;
	int numQueens = boardPtr->getNumQueens();
	Queen* queenConsidered = nullptr; //need to check for all the queens
	for (int queenIndex = 0; queenIndex < numQueens; queenIndex++)
	{
		queenConsidered = boardPtr->getQueen(queenIndex);
		int rowOfQueenConsidered = queenConsidered->getRow(); // get row of queen in question
		int colOfQueenConsidered = queenConsidered->getCol(); // get column of queen in question
		//initialize row/col to check
		int colOfQueen = col;
		int rowOfQueen = row;
		//check the diagonal below and to the right
		bool withinBounds = (rowOfQueen >= 0 && rowOfQueen <= BOARD_SIZE && colOfQueen >= 0 && colOfQueen <= BOARD_SIZE);
		while (!isAttacked && withinBounds)
		{
			rowOfQueen++;
			colOfQueen--;
			withinBounds = (rowOfQueen >= 0 && rowOfQueen <= BOARD_SIZE && colOfQueen >= 0 && colOfQueen <= BOARD_SIZE);
			if (rowOfQueen == rowOfQueenConsidered && colOfQueen == colOfQueenConsidered)
			{
				isAttacked = true;
				queenConsidered = nullptr; //eliminate dangling pointer
				return isAttacked; // exit loop if queen is attacked
			}
		}
	}
	queenConsidered = nullptr; //eliminate dangling pointer
	return isAttacked;
}

bool Queen::aboveAndToRight() const
{
	bool isAttacked = false;
	int numQueens = boardPtr->getNumQueens();
	Queen* queenConsidered = nullptr; //need to check for all the queens
	for (int queenIndex = 0; queenIndex < numQueens; queenIndex++)
	{
		queenConsidered = boardPtr->getQueen(queenIndex);
		int rowOfQueenConsidered = queenConsidered->getRow(); // get row of queen in question
		int colOfQueenConsidered = queenConsidered->getCol(); // get column of queen in question
		//initialize row/col to check
		int colOfQueen = col;
		int rowOfQueen = row;
		//check the diagonal below and to the right
		bool withinBounds = (rowOfQueen >= 0 && rowOfQueen <= BOARD_SIZE && colOfQueen >= 0 && colOfQueen <= BOARD_SIZE);
		while (!isAttacked && withinBounds)
		{
			rowOfQueen--;
			colOfQueen++;
			withinBounds = (rowOfQueen >= 0 && rowOfQueen <= BOARD_SIZE && colOfQueen >= 0 && colOfQueen <= BOARD_SIZE);
			if (rowOfQueen == rowOfQueenConsidered && colOfQueen == colOfQueenConsidered)
			{
				isAttacked = true;
				queenConsidered = nullptr; //eliminate dangling pointer
				return isAttacked; // exit loop if queen is attacked
			}
		}
	}
	queenConsidered = nullptr; //eliminate dangling pointer
	return isAttacked;
}

bool Queen::aboveAndToLeft() const
{
	bool isAttacked = false;
	int numQueens = boardPtr->getNumQueens();
	Queen* queenConsidered = nullptr; //need to check for all the queens
	for (int queenIndex = 0; queenIndex < numQueens; queenIndex++)
	{
		queenConsidered = boardPtr->getQueen(queenIndex);
		int rowOfQueenConsidered = queenConsidered->getRow(); // get row of queen in question
		int colOfQueenConsidered = queenConsidered->getCol(); // get column of queen in question
		//initialize row/col to check
		int colOfQueen = col;
		int rowOfQueen = row;
		//check the diagonal below and to the right
		bool withinBounds = (rowOfQueen >= 0 && rowOfQueen <= BOARD_SIZE && colOfQueen >= 0 && colOfQueen <= BOARD_SIZE);
		while (!isAttacked && withinBounds)
		{
			rowOfQueen--;
			colOfQueen--;
			withinBounds = (rowOfQueen >= 0 && rowOfQueen <= BOARD_SIZE && colOfQueen >= 0 && colOfQueen <= BOARD_SIZE);
			if (rowOfQueen == rowOfQueenConsidered && colOfQueen == colOfQueenConsidered)
			{
				isAttacked = true;
				queenConsidered = nullptr; //eliminate dangling pointer
				return isAttacked; // exit loop if queen is attacked
			}
		}
	}
	queenConsidered = nullptr; //eliminate dangling pointer
	return isAttacked;
}

bool Queen::isDiagonallyAttacked() const
{ //checks if queen resides in any square below and to the right diagonally
	bool attackedBottomRight = belowAndToRight();
	if (attackedBottomRight)
	{
		return true;
	}
	//checks if queen resides in any square below and to the left diagonally
	bool attackedBottomLeft = belowAndToLeft();
	if (attackedBottomLeft)
	{
		return true;
	}
	bool attackedTopRight = aboveAndToRight();
	if (attackedTopRight)
	{
		return true;
	}
	bool attackedTopLeft = aboveAndToLeft();
	if (attackedTopLeft)
	{
		return true;
	}
	else return false;
}

bool Queen::isUnderAttack() const {
	if (isDiagonallyAttacked()) //check if diagonally attacked first
	{
		return true;
	}
	int numQueens = boardPtr->getNumQueens();
	int loopVar = 0;
	bool underAttack = false;
	const Queen* queenConsidered = nullptr;
	while (loopVar < numQueens && !underAttack)
	{
		queenConsidered = boardPtr->getQueen(loopVar);
		// if the another queen is in the same column or row, the queen is under attack
		if (queenConsidered->getCol() == col || queenConsidered->getRow() == row)
		{
			underAttack = true;
			queenConsidered = nullptr;
			return underAttack;
		}
		queenConsidered = nullptr; // eliminate dangling pointer
		loopVar++;
	}
	return false;
}

void Queen::setBoard(const Board* bPtr)
{
	boardPtr = bPtr;
} // end setBoard

const Board* Queen::getBoard()
{
	return boardPtr;
}