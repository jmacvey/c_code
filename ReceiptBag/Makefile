#Makefile for BagWithReceipts Project

objects := $(patsubst %.o, %.h, $(wildcard *.h))

CC = g++ -std=c++11

ReceiptBag.o: main.o ExitScript.o
	$(CC) -o ReceiptBag ExitScript.o main.o

ExitScript.o: ExitScript.h
	$(CC) -c ExitScript.cpp

main.o: main.cpp $(objects)
	$(CC) -c main.cpp

.PHONY: clean
clean:
	rm *.o ReceiptBag
