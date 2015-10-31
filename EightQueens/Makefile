# MAKEFILE FOR EIGHT QUEENS PROJECT


#create objects variable
objects := $(patsubst %.cpp,%.o,$(wildcard *.cpp))

CC = g++ -std=c++11


#compile the program
eightQueens : $(objects)
	$(CC) -o eightQueens $(objects) 

Queen.o: Queen.h
	$(CC) -c Queen.cpp

Board.o: Board.h
	$(CC) -c Board.cpp

main.o: Board.h Queen.h main.cpp
	$(CC) -c main.cpp
 
#install the program
install:
	mv eightQueens ~/cppPrograms

#clean the directory
.PHONY: clean
clean:
	rm *.o eightQueens
