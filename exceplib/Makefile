# Makefile for PrecondViolatedExcep Library

#-----------------VARIABLES-----------------#

CC = g++ -std=c++11
TARGET := exceplib.o

#-----------------RECIPES-------------------#


libexceplib.a: $(TARGET)
	ar rcs $@ $^

$(TARGET): exceplib.cpp exceplib.h
	$(CC) -c -o $@ $<

