#Makefile for TreeADT

#variables
CC := g++ -std=c++11
TEMPLATE_CODE := BinaryTreeInterface.h LinkedTree.h LinkedTreeImpl.h LinkedTreeNode.h \
	BinarySearchTree.h BinarySearchTreeImpl.h 
LIB_PATH := -L ../eslib -L ../exceplib -l eslib -l exceplib
INCLUDES := -I ../eslib/ -I ../exceplib/
TARGET := TreeTest

#Receipts

$(TARGET) : Driver.o
	$(CC) $^ $(LIB_PATH) -o $(TARGET)

Driver.o: Driver.cpp $(TEMPLATE_CODE)
	$(CC) -c $< $(INCLUDES)

.PHONY: clean
clean:
	rm -rf *.o TreeTest
