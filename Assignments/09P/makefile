CXX=g++ -DDEBUG

all: maptest

maptest: map.h map.cpp maptest0.cpp
	$(CXX)  maptest0.cpp -o maptest

mapTest: mapTest.cpp map.h
	$(CXX) mapTest.cpp -lgtest -lpthread -o mapTest

clean:
	rm -f *.o  maptest mapTest


