#MAKEFILE FOR BANKING EVENT-SIMULATION


objects := $(patsubst %.cpp,%.o,$(wildcard *.cpp))

cc=g++

bankSim.o: $(objects)
	$(cc) -std=c++0x -o bankSim $(objects)

Event.o: Event.h
	$(cc) -std=c++0x -c Event.cpp

EventBuilder.o: EventBuilder.h
	$(cc) -std=c++11 -c EventBuilder.cpp

EventType.o: EventType.h

Time.o: Time.h

Statistics.o: Statistics.h
	$(cc) -std=c++0x -c Statistics.cpp

Simulation.o: Simulation.h
	$(cc) -std=c++0x -c Simulation.cpp

Driver.o: Driver.cpp
	$(cc) -std=c++0x -c Driver.cpp

.PHONY: clean
clean:
	rm $(objects) bankSim

install:
	cp bankSim ~/cppPrograms

