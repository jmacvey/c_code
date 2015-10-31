#ifndef MAZE_H
#define MAZE_H

#include "Creature.h"
#include <iostream>
#include <string>
#include <cassert>
#include <vector>
using namespace std;

/** Example Text File data for maze class

20 7  width and height of the maze in squares
0 18  row and column coordinate of maze exit
6 12  row and column coordinate of maze entrance
xxxxxxxxxxxxxxxxxx x
x x xxxx x
x xxxxx xxxxx xx x
x xxxxx xxxxxxx xx x
x x xx xx x
x xxxxxxxxxx xx x
xxxxxxxxxxxx xxxxxxx			*/

// structure for individual square data
struct SquareData
{
	int Col;
	int Row;
	char State;
	void setCol(const int& col)
	{
		Col = col;
	}
	void setRow(const int& row)
	{
		Row = row;
	}
	void setState(const char& state)
	{
		State = state;
	}
};

class Maze {
private:
	// vector of squares with corresponding data
	vector<SquareData*> squares;
	/** mazeWidth and mazeLength to be determined via
		txt file. */
	int mazeWidth;
	int mazeLength;
	int exitRow;
	int exitCol;
	int entRow;
	int entCol;
	/** various markers for States of the Squares*/
	const char pathMarker = 'p';
	const char visitMarker = 'v';
	const char wallMarker = 'x'; 
	const char clearMarker = ' ';
	int getIndexOfSquare(const int& squareRow, const int& squareCol) const;
public:
	/** Default Constructor */
	Maze();
	/** Constructor with input file parameter of type specified above */
	Maze(std::ifstream& inputFile);
	/** Copy Constructor */
	Maze(const Maze& myMaze);
	/** Destructor */
	virtual ~Maze();
	/** clears the maze of its contents*/
	void clear();
	/** displays the maze */
	void display() const;
	/** SQUARE STATE CHECKS */
	/** Determines if particular square is part of the maze wall*/
	bool isWall(const int& squareRow, const int& squareCol) const;
	/** Determines if particular square is clear*/
	bool isClear(const int& squareRow, const int& squareCol) const;
	/** Determines if particular square is on the path to exit */
	bool isOnPath(const int& squareRow, const int& squareCol) const;
	/** Determines if a particular square has been visited */
	bool visited(const int& squareRow, const int& squareCol) const;
	/** SQUARE ACCESSOR METHODS */
	/** Returns pointer to square with the given column and row */
	SquareData* getSquare(const int& squareRow, const int& squareCol) const;
	/** returns the state of a square at a given index */
	char getSquareState(const int& squareRow, const int& squareCol) const;
	/** SQUARE MUTATOR METHODS */
	/** marks a square at a given index as part of the path */
	bool markSquareAsPath(const int& squareRow, const int& squareCol);
	/** marks a square at a given index as visited */
	bool markSquareAsVisited(const int& squareRow, const int& squareCol);
	/** marks a square at a given index as clear */
	bool markSquareAsClear(const int& squareRow, const int& squareCol);
	/** returns the number of squares in the maze */
	int numSquares() const;
	/** accessor for entRow */
	int getEntRow() const;
	/** accessor for entCol */
	int getEntCol() const;
	/** accessor for exitRow */
	int getExitRow() const;
	/** accessor for exitCol */
	int getExitCol() const;
	/** accessor for mazeWidth */
	int getMazeWidth() const;
	/** accessor for mazeLength */
	int getMazeLength() const;
	/** accessor for clearSymbol */
	char getClearSymbol() const;
	/** vector display */
	void vectorDisplay() const;
	/** accessor for path symbol */
	char getPathSymbol() const;
};

#endif