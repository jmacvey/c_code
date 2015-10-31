#------------------------QUEUEADT MAKE FILE----------------------------#

#------------------------VARIABLES----------------------------#

CC := g++ -std=c++11
template_code := LinkedQueue.h LinkedQueueImpl.h QueueInterface.h \
	CircularArrayQueue.h CircularArrayQueueImpl.h \
	ListNode.h ListNodeImpl.h 
LIB_PATH := -L ../eslib/ -l eslib
INCLUDES := -I ../eslib/
TARGET := QueueTester

#------------------------RECIPES----------------------------#


$(TARGET) : Driver.o
	$(CC) Driver.o $(LIB_PATH) -o $(TARGET)

Driver.o: Driver.cpp $(template_code)
	$(CC) -c Driver.cpp $(INCLUDES)

.PHONY: clean
clean:
	rm -f *.o QueueTester
