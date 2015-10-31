# MAKE FILE FOR RECURSIVELY-SOLVED MAZE

#define the objects
objects := $(patsubst %.cpp,%.o,$(wildcard *.cpp))

#default target

Maze: $(objects)
	g++ -std=c++11 -o Maze $(objects)

Maze.o: Maze.h
	g++ -std=c++11 -c Maze.cpp

MazeSolver.o: MazeSolver.h
	g++ -std=c++11 -c MazeSolver.cpp

Creature.o: Creature.h
	g++ -std=c++11 -c Creature.cpp

main.o: main.cpp
	g++ -std=c++11 -c main.cpp
#install program
Install:
	mv Maze ~/cppPrograms

#clean the directory
.PHONY: clean
clean:
	rm *.o Maze

