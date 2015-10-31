#makefile for hpAir solution

#------------------------VARIABLES--------------------------#
OBJS := main.o FlightMap.o GetData.o
template_code := FlightNode.h
CC := g++ -std=c++11
LIB_PATH := -L ~/Tarballs/t_balls/eslib -l eslib
INCLUDES := -I ~/Tarballs/t_balls/eslib

#------------------------RECIPES--------------------------#
TakeFlight.o: $(OBJS)
	$(CC) $(OBJS) $(LIB_PATH) -o TakeFlight

GetData.o: GetData.h
	$(CC) -c GetData.cpp

FlightMap.o: FlightMap.h $(template_code)
	$(CC) -c FlightMap.cpp

main.o: main.cpp FlightMap.o GetData.o $(template_code)
	$(CC) -c main.cpp $(INCLUDES)

clean: 
	rm *.o TakeFlight
