CC = g++
DEBUG = -g
EXECUTABLE = mynetwork
SOURCES = mynetwork.cpp PQueue.h DisjointSet.h


all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CC) $(DEBUG) $< -o $@ 
	
clean:
	rm -f $(EXECUTABLE)
	