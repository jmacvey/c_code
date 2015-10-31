#Makefile for Calculators Programs

#---------------------VARIABLES-----------------------#

CC := g++ -std=c++11
template_code := StackInterface.h OurStack.h OurStackImpl.h
objects := InfixCalc.h InfixCalcImpl.h PostFixCalculator.h PostFixImpl.h
LIB_PATH := -L ../eslib -l eslib
INCLUDES := -I ../eslib

#---------------------VARIABLES-----------------------#

CalcTester.o:  main.o
	$(CC) main.o $(LIB_PATH) -o CalcTester
	
main.o: main.cpp $(template_code) $(objects)
	$(CC) -c main.cpp $(INCLUDES)

.PHONY: clean
clean:
	rm -f *.o  CalcTester;

