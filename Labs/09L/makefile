CXX=g++ -g

all: settest0 btreetest0 

settest0: set.h set.cpp settest0.cpp
	$(CXX)  settest0.cpp -o settest0

settest4: set.h set.cpp settest4.cpp
	$(CXX)  settest4.cpp -o settest4

btreetest0:  btree.h btree.cpp btreetest0.cpp
	$(CXX)  btree.cpp btreetest0.cpp -o btreetest0

clean:
	rm -f *.o  settest0 settest4 btreetest0