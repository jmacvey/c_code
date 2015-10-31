#makefile for sorting algorithm driver

#-----------------------VARIABLES-----------------------#

template_code := SortingAlgorithms.h
CC = g++ -std=c++11
LIB_PATH = -L ~/Tarballs/t_balls/eslib/ -leslib
TARGET = Sorter
OBJECTS = main.o
SRC = $(OBJECTS:.o=.cpp)
INCLUDES = -I ~/Tarballs/t_balls/eslib/
#-----------------------RECIPES-----------------------#

$(TARGET): $(OBJECTS) 
	$(CC) $^ $(LIB_PATH) -o $(TARGET)

$(OBJECTS): $(SRC) $(template_code)
	$(CC) -c $(SRC) $(INCLUDES)

.PHONY: clean

clean:
	rm -f *.o Sorter

