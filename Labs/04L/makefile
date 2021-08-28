CXX=g++

all: queue.o

queue.o: queue.cpp queue.h
	$(CXX) -c queue.cpp -o queue.o

queueTest: queueTest.cpp queue.cpp queue.h
	$(CXX) -g queueTest.cpp queue.cpp -lgtest -lpthread -o queueTest

clean: 
	rm -f queueTest queue.o 

queueTestRun: queueTest queue.cpp queue.h
	./queueTest