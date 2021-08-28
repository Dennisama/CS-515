CXX=g++ -g

all: maptest0

maptest0: map.h map.cpp maptest0.cpp
	$(CXX)  maptest0.cpp -o maptest0

mapTest: mapTest.cpp map.h
	$(CXX) mapTest.cpp -lgtest -lpthread -o mapTest

clean:
	rm -f *.o  maptest0 mapTest


