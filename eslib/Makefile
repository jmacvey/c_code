#Makefile to compile static library for exit Script
#used by other programs

#------------------Variables------------------#

CC = g++ -std=c++11
TARGET = test
#------------------Recipes------------------#

$(TARGET): main.o libeslib.a
	$(CC) $^ -o $@

main.o: main.cpp
	$(CC) -c $< -o $@

libeslib.a: eslib.o
	ar rcs $@ $^

eslib.o: eslib.cpp eslib.h
	$(CC) -c -o $@ $<

.PHONY: clean
clean:
	 rm -f *.o *a

