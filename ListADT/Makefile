#---------------------VARIABLES--------------------#

CC := g++ -std=c++11
template_code := ListInterface.h LinkedList.h LinkedListImpl.h LinkedIterator.h \
	ArrayList.h ArrayListImpl.h ListNode.h ListNodeImpl.h  
TARGET := ListTester
LIB_PATH := -L ../exceplib/ -l exceplib
INCLUDES := -I ../exceplib/
#---------------------RECIPES---------------------#

$(TARGET): main.o
	$(CC) main.o $(LIB_PATH) -o $(TARGET)

main.o: main.cpp $(template_code)
	$(CC) -c main.cpp $(INCLUDES)

.PHONY: clean
clean:
	rm -f *.o ListTester 
