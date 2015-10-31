#-------------------------Makefile for MusicPlayer Program-------------------#

#------------------------VARIABLES-------------------------------------------#

CC := g++ -std=c++11
LIB_PATH := -L ../eslib -L ../exceplib -l eslib -l exceplib
INCLUDES := -I ../eslib/ -I ../exceplib/

TEMPLATE_CODE := LinkedSortedList.h LinkedSortedListImpl.h ListNode.h \
	ListNodeImpl.h 

OBJECTS := Track.o Disc.o DiscList.o
TARGET := MusicX

#-----------------------RECIPES--------------------------#

$(TARGET) : main.o $(OBJECTS)
	$(CC) $^ $(LIB_PATH) -o $(TARGET)

main.o: main.cpp $(OBJECTS)
	$(CC) -c $< $(INCLUDES)


Track.o: Track.h $(TEMPLATE_CODE)
	$(CC) -c Track.cpp $(INCLUDES) 

Disc.o: Disc.h $(TEMPLATE_CODE)
	$(CC) -c Disc.cpp $(INCLUDES)

DiscList.o: DiscList.h $(TEMPLATE_CODE)
	$(CC) -c DiscList.cpp $(INCLUDES)

.PHONY: clean
clean:
	rm *.o MusicX
